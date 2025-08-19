#include "lib.h"

using namespace arma;
using namespace std;


double psi_T(double mu,double sigma,double x){
	return exp(-pow(x-mu,2)/(2*sigma*sigma)) +exp(-pow(x+mu,2)/(2*sigma*sigma));
}

double dpsi2 (double mu, double sigma, double x){
	double a = pow((x-mu)/sigma,2);
	double b = pow((x+mu)/sigma,2);
	return (pow(sigma,-2)*a-pow(sigma,-2))*exp(-0.5*a)+(pow(sigma,-2)*b-pow(sigma,-2))*exp(-0.5*b);
}

double pot(double x){
	return pow(x,4)-(5./2.)*x*x;
}

double Hpsi (double mu, double sigma, double x){
	return -0.5*dpsi2(mu,sigma,x)+pot(x)*psi_T(mu,sigma,x);
}

double Metropolis_Acceptance(double p_new,double p_old,double T_fwd, double T_bkw){ //y:old move, x:new move
	double q = (T_fwd*p_new)/(T_bkw* p_old);
	if (q>=1.) return 1.;
	else return q;
}
/*
void Metropolis_Step(metro &eval, double mu,double sigma){
	Random rnd = eval.rand;
    double normalization = 2.*sigma*sqrt(M_PI)*(1+exp(-mu*mu/(sigma*sigma)));
	double old_pos = eval.position;
	double new_pos=old_pos+eval.step_length*rnd.Rannyu(-1,1);
	double p_old = pow(psi_T(mu,sigma,old_pos),2)/double(normalization);
	double p_new = pow(psi_T(mu,sigma,new_pos),2)/double(normalization);
	double T_bkw=1.;
	double T_fwd =1.;

	double A=Metropolis_Acceptance(p_new,p_old,T_fwd,T_bkw);
	
	double x = rnd.Rannyu();
	if (x<A){
		eval.acc_rate++;
		eval.position = new_pos;
}
else eval.position = old_pos;
}
*/
void Metropolis_Step(Random& rnd, double &position,double step_length,double &acc_rate, double mu, double sigma){
	
	double old_pos = position;
double normalization = 2.*sigma*sqrt(M_PI)*(1+exp(-mu*mu/(sigma*sigma)));
	double new_pos=old_pos+step_length*rnd.Rannyu(-1,1);
	double p_old = pow(psi_T(mu,sigma,old_pos),2)/double(normalization);
	double p_new = pow(psi_T(mu,sigma,new_pos),2)/double(normalization);
	double T_bkw=1.;
	double T_fwd =1.;

	double A=Metropolis_Acceptance(p_new,p_old,T_fwd,T_bkw);
	
	double x = rnd.Rannyu();
	if (x<A){
		acc_rate++;
		position = new_pos;
}
else position = old_pos;
}
/*
void Equilibration(metro eval, double mu, double sigma,int eq_steps){
ofstream out("../OUTPUT/acceptance.csv");
out<<"step\tacc_rate"<<endl;
for (int i =0;i<eq_steps;i++){
	
	Metropolis_Step(eval,mu,sigma);
	out<<i<<"\t"<<eval.acc_rate/double(i)<<endl;
}
out.close();

cout<<"Equilibrium reached with acceptance rate "<<eval.acc_rate/double(eq_steps)<<" after "<<eq_steps<<" steps"<<endl;
out.close();
}
*/
/*
double compute_mean_H(Random &rnd, int Nsteps, double mu,double sigma){
	metro H_eval;
	H_eval.rand =rnd;
	H_eval.step_length=2.75;
	double integral =0.;
	//Equilibration(H_eval,mu,sigma,2000);
	for (int i=0;i<Nsteps;i++){
	Metropolis_Step(H_eval,mu,sigma);
	integral+= Hpsi(mu,sigma,H_eval.position)/psi_T(mu,sigma,H_eval.position);
	}
	return integral/double(Nsteps);

}
	*/
void compute_mean_H(Random &rnd, int Nsteps, SApar &par){
	double position =0.;
	double integral =0.;
	double acc_rate=0.;
	double step_length=2.75;
	for (int i=1; i<Nsteps; i++){ //steps of RW
		double old_pos = position;
		//out<<i<<"\t"<<position<<endl;
		Metropolis_Step(rnd,position,step_length,acc_rate,par.mu,par.sigma);
		integral+= Hpsi(par.mu,par.sigma,position)/psi_T(par.mu,par.sigma,position);	
	}
	acc_rate/=( Nsteps);
	//cout<<"acc_rate: "<<acc_rate<<endl;
	par.meanH= integral/double(Nsteps);
}

/*ANNEALING:
	ciclo su beta che aumenta(T diminuisce):
		ciclo su N step a beta fissata:
			propongo un nuovo valore di mu e sigma
			valuto <H> con nuovi mu e sigma (metropolis)
			se new_<H> < old_<H> accetto la mossa (più vicino al GS)
			in caso contrario, valuto peso di Boltzmann e accetto il valore solo se rnd<BW
			-> più T si abbassa più la prob di accettare anche mosse sbagliate diminuisce
*/
void simulated_annealing(double beta_start,int ann_steps,int Nsteps,int Nblocks,Random &rnd){
    //initial guessesfor mu and sigma
    ofstream out ("SAenergy.csv");
	ofstream out1 ("SApars.csv");
	out<<"beta\tmeanH\terr"<<endl;
	out1<<"beta\tmu\tsigma"<<endl;

	
	int NHsteps=10000;

	SApar old_par;
	double beta=beta_start;

	old_par.mu =1.; 
    old_par.sigma= 1.;
	compute_mean_H(rnd,NHsteps,old_par);

    double dmu_max =0.5*(1./beta); //mu può essere negativo
	double dsigma_max = 0.5*(1./beta); 
	
	
    for (int k =0; k<ann_steps;k++){ //change beta value: for e
		double block_ave=0.;
		double block_ave2=0.;
		for (int j=0;j<Nblocks;j++){	
			double ave=0;
			
			for (int i = 0;i<Nsteps;i++){ //steps at fixed T
				SApar new_par;
				do {
				new_par.mu = fabs(rnd.Gauss(old_par.mu,dmu_max));
				new_par.sigma = fabs(rnd.Gauss(old_par.sigma, dsigma_max));
				} while (new_par.sigma <= 0.1 or new_par.sigma >3. or new_par.mu >3.);
				
				compute_mean_H(rnd,NHsteps,new_par);

				if (new_par.meanH<old_par.meanH) {
					old_par = new_par;
				}

				else{
					double boltz_w = exp(-beta*(new_par.meanH-old_par.meanH));
					double r = rnd.Rannyu();
					if (r<boltz_w) old_par=new_par;
				}
				ave += old_par.meanH;
				//ave[1]+=old_par.sigma;
				//ave[2]+=old_par.meanH;
			} //fine step a temperaturs fix: ho valori 
			ave/=double (Nsteps);
			block_ave += ave;
			block_ave2 += ave*ave;
			out1<<beta<<"\t"<<old_par.mu<<"\t"<<old_par.sigma<<endl;
		}
	
	cout<<"Final guess for T="<<1./beta<<" : "<<endl;
	cout<<"<H>: "<<block_ave/(double(Nblocks))<<endl;
	double err =sqrt((block_ave2/double(Nblocks)-pow(block_ave/double(Nblocks),2))/double(Nblocks));
	out<<beta<<"\t"<<block_ave/(double(Nblocks))<<"\t"<<err<<endl;
	beta*=1.2;
}
out.close();
out1.close();
}