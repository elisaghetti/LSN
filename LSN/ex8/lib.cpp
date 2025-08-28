#include "lib.h"

using namespace arma;
using namespace std;

double psi_T(SApar par,double x){
	return exp(-pow(x-par.mu,2)/(2*par.sigma*par.sigma)) +exp(-pow(x+par.mu,2)/(2*par.sigma*par.sigma));
}

double dpsi2 (SApar par, double x){
	double a = pow((x-par.mu)/par.sigma,2);
	double b = pow((x+par.mu)/par.sigma,2);
	return (pow(par.sigma,-2)*a-pow(par.sigma,-2))*exp(-0.5*a)+(pow(par.sigma,-2)*b-pow(par.sigma,-2))*exp(-0.5*b);
}

double pot(double x){
	return pow(x,4)-(5./2.)*x*x;
}

double Hpsi (SApar par, double x){
	return -0.5*dpsi2(par,x)+pot(x)*psi_T(par,x);
}

double Metropolis_Acceptance(double p_new,double p_old,double T_fwd, double T_bkw){ //y:old move, x:new move
	double q = (T_fwd*p_new)/(T_bkw* p_old);
	if (q>=1.) return 1.;
	else return q;
}

void Metropolis_Step(Random &rnd, metro &eval, SApar par){
	
    //double normalization = 2.*par.sigma*sqrt(M_PI)*(1+exp(-par.mu*par.mu/(par.sigma*par.sigma)));
	double old_pos = eval.position;
	double new_pos=old_pos+eval.step_length*rnd.Rannyu(-1,1);
	double p_old = pow(psi_T(par,old_pos),2)/double(par.norm);
	double p_new = pow(psi_T(par,new_pos),2)/double(par.norm);
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

void Equilibration(Random &rnd, metro &eval, SApar &par,int eq_steps){
for (int i =0;i<eq_steps;i++){
	Metropolis_Step(rnd,eval,par);
}
}

void Equilibration(Random &rnd, metro &eval, SApar &par,int eq_steps,string file){
ofstream out(file);
out<<"step\tacc_rate"<<endl;
for (int i =0;i<eq_steps;i++){
	Metropolis_Step(rnd,eval,par);
	out<<i<<"\t"<<eval.acc_rate/double(i)<<endl;
	
}
out.close();

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

//overloading of compute mean
void compute_mean_H(Random &rnd, metro &H_eval,data_blocking &H_blocks, SApar par){
	H_blocks.reset();

	Equilibration(rnd,H_eval,par,2000);

for (int j=0; j<H_blocks.Nblocks; j++){
	double integral =0.;
	H_blocks.ave=0.;
	for (int i=0; i<H_blocks.Nsteps; i++){ //steps of RW
		Metropolis_Step(rnd,H_eval,par);
		integral+= Hpsi(par,H_eval.position)/psi_T(par,H_eval.position);	
	}
	
	H_blocks.ave = integral/double(H_blocks.Nsteps);
	H_blocks.increment(j);
}

}

void compute_mean_H(Random &rnd,metro &H_eval, data_blocking &H_blocks, SApar &par,string filename){
	H_blocks.reset();

	Equilibration(rnd,H_eval,par,2000);
	ofstream out(filename);
	out<<"block\tintegral\tprog_ave\terr"<<endl;

for (int j=0; j<H_blocks.Nblocks; j++){
	double integral =0.;
	H_blocks.ave=0.;
	for (int i=0; i<H_blocks.Nsteps; i++){ //steps of RW
		Metropolis_Step(rnd,H_eval,par);
		integral+= Hpsi(par,H_eval.position)/psi_T(par,H_eval.position);
	}

	H_blocks.ave = integral/double(H_blocks.Nsteps);
	
	H_blocks.increment(j);
	out<<j<<"\t"<<H_blocks.ave<<"\t"<<H_blocks.block_ave/double(j+1)<<"\t"<<H_blocks.err<<endl;
}
out.close();
}

void sample_psi(Random &rnd, metro &pos_sampler,SApar par,int Nsteps,string file){
		ofstream out (file);
		out<<"step\tx"<<endl;
		Equilibration(rnd,pos_sampler,par,2000);

		for (int i=1; i<Nsteps; i++){ //steps of RW
		
		out<<i<<"\t"<<pos_sampler.position<<endl;
		Metropolis_Step(rnd,pos_sampler,par);
	}
	out.close();
}

vec annealing_step (Random &rnd, int Nsteps, metro &H_eval,double beta,SApar &old_par, data_blocking &H_blocks){

	double dmu_max =0.5*(1./beta); 
	double dsigma_max = 0.5*(1./beta); 

 //fa più step a T alta in modo  da esplorare meglio lo spazio dei parametri
	//cout<<"steps "<<Nsteps<<endl;
	double acc_rate=0.;
	double err=0.;
	double best_err =0.;
	SApar best_par;
	double ave=0.;
	double ave2=0.;

	vec results = zeros(4); //vector that contains average and best mean H values with their respective errors in each temp block
			for (int i = 0;i<Nsteps;i++){ //steps at fixed T
			
				SApar new_par;
				
				do {
				new_par.mu = fabs(rnd.Gauss(old_par.mu,dmu_max));
				new_par.sigma = fabs(rnd.Gauss(old_par.sigma, dsigma_max));
				} while (new_par.sigma <= 0.1 or new_par.sigma >3. or new_par.mu >3.);

				new_par.set_norm();
				compute_mean_H(rnd,H_eval,H_blocks,new_par);
				new_par.meanH = H_blocks.block_ave/double(H_blocks.Nblocks);
				
				

				if (new_par.meanH<old_par.meanH) {
					old_par = new_par;
					err=H_blocks.err;
					acc_rate++;
				}
				
				else{
					double boltz_w = exp(-beta*(new_par.meanH-old_par.meanH));
					double r = rnd.Rannyu();
					if (r<boltz_w) {
						old_par=new_par;
						err=H_blocks.err;
						acc_rate++;
					}
					//update best parameter
					if (old_par.meanH<best_par.meanH){
						best_par=old_par;
						best_err=err;
					}
					//update averae estimated value
					ave+=old_par.meanH;
					ave2+= old_par.meanH*old_par.meanH;
				}
			}
			

//old_par = final_par;
ave/=double(Nsteps);
ave2/=double(Nsteps);
double std_dev = sqrt((ave2-ave*ave)/(Nsteps-1.));
results[0]=ave; //mean value of H estimates at each T
results[1]=std_dev;
results[2]=best_par.meanH;
results[3]=best_err;
cout<<"acc rate for beta= "<<beta<<" : "<<acc_rate/double(Nsteps)<<endl;
return results;
			}
			//ann_blocks.ave/=ann_blocks.Nsteps;
		

/*
SApar annealing_step (Random &rnd, metro &H_eval,double beta,SApar old_par, data_blocking &ann_blocks){
	//define metropolis and data locking executors for evaluation of mean H

//	metro H_eval;

	data_blocking H_blocks;
	H_blocks.Nblocks = 10;
	H_blocks.Nsteps = 2000;

	double dmu_max =0.5*(1./beta); 
	double dsigma_max = 0.5*(1./beta); 
	SApar final_par;
	double precision;
	int j =0;

	
	cout<<"steps "<<ann_blocks.Nsteps<<endl;
	//do{
	//for (int j=0;j<ann_blocks.Nblocks;j++){	
		//j++;
		//ann_blocks.Nblocks=j;
		
		//double ave=0;
			
			for (int i = 0;i<ann_blocks.Nsteps;i++){ //steps at fixed T
				SApar new_par;
				
				do {
				new_par.mu = fabs(rnd.Gauss(old_par.mu,dmu_max));
				new_par.sigma = fabs(rnd.Gauss(old_par.sigma, dsigma_max));
				} while (new_par.sigma <= 0.1 or new_par.sigma >3. or new_par.mu >3.);

				new_par.set_norm();
				new_par.meanH = compute_mean_H(rnd,H_eval,H_blocks,new_par,beta);

				if (new_par.meanH<old_par.meanH) {
					final_par = new_par;
				}
				
				else{
					double boltz_w = exp(-beta*(new_par.meanH-old_par.meanH));
					double r = rnd.Rannyu();
					if (r<boltz_w) final_par=new_par;
					else final_par=old_par;
				}
ave += final_par.meanH;
old_par = final_par;
			}
ave/=double (ann_blocks.Nsteps);

ann_blocks.increment(ave,j);
double prec = precision_from_H(ann_blocks.block_ave/ann_blocks.Nblocks);
	cout<<precision<<endl;
cout<<j<<" "<<" "<<ann_blocks.block_ave/ann_blocks.Nblocks<<" "<<ann_blocks.err<<endl;
		} while (j==0 or ann_blocks.err>prec);
return final_par;
}
*/
/*
SApar simulated_annealing(double beta_start,int ann_steps,data_blocking block_ave,Random &rnd){
    //initial guessesfor mu and sigma
    //ofstream out ("./OUTPUT/SAenergy_lin.csv");
	//ofstream out1 ("./OUTPUT/SApars_lin.csv");
	ofstream out ("./OUTPUT/SAenergy.csv");
	ofstream out1 ("./OUTPUT/SApars.csv");
	out<<"beta\tmeanH\terr"<<endl;
	out1<<"beta\tmu\tsigma"<<endl;

	
	double beta=beta_start;

	metro H_eval;
	
	SApar old_par;
	old_par.mu =1.; 
    old_par.sigma= 1.;

	data_blocking H_blocks;
	H_blocks.Nblocks = 1;
	H_blocks.Nsteps = 10000;

	old_par.meanH = compute_mean_H(rnd,H_blocks,old_par);
	cout<<old_par.meanH<<endl;

    double dmu_max =0.5*(1./beta); //mu può essere negativo
	double dsigma_max = 0.5*(1./beta); 
	
	
    for (int k =0; k<ann_steps;k++){ //change beta value: for e
	
		data_blocking ann_blocks;
		ann_blocks.Nblocks=Nblocks;
		ann_blocks.Nsteps=Nsteps;

		for (int j=0;j<ann_blocks.Nblocks;j++){	
			double ave=0;
			
			for (int i = 0;i<ann_blocks.Nsteps;i++){ //steps at fixed T
				SApar new_par;
				//cout<<"begin while"<<endl;
				do {
				new_par.mu = fabs(rnd.Gauss(old_par.mu,dmu_max));
				new_par.sigma = fabs(rnd.Gauss(old_par.sigma, dsigma_max));
				} while (new_par.sigma <= 0.1 or new_par.sigma >3. or new_par.mu >3.);

				//cout<<"compute meanH"<<endl;
				new_par.meanH = compute_mean_H(rnd,H_blocks,new_par);

				if (new_par.meanH<old_par.meanH) {
					old_par = new_par;
				}
				
				else{//cout<<"boltz weight"<<endl;
					double boltz_w = exp(-beta*(new_par.meanH-old_par.meanH));
					double r = rnd.Rannyu();
					if (r<boltz_w) old_par=new_par;
				}
				ave += old_par.meanH;
			
	out<<"beta\tmeanH\terr"<<endl;		} //fine step a temperaturs fix: ho valori 
			ave/=double (Nsteps);
			//cout<<"increment"<<endl;
			ann_blocks.increment(ave,j);
			out1<<beta<<"\t"<<old_par.mu<<"\t"<<old_par.sigma<<endl;
		}
	
	cout<<"Final guess for T="<<1./beta<<" : "<<endl;
	cout<<"<H>: "<<ann_blocks.block_ave/(double(ann_blocks.Nblocks))<<endl;
	
	//out<<beta<<"\t"<<ann_blocks.block_ave/(double(ann_blocks.Nblocks))<<"\t"<<ann_blocks.err<<endl;
	beta*=1.1;
	//beta += 0.1;
}
out.close();
out1.close();

return old_par;
}
*/
/*
void Equilibration(Random &rnd, double &position, double step_length, double &acc_rate, double mu, double sigma,int eq_steps){
ofstream out("./OUTPUT/acceptance.csv");
out<<"step\tacc_rate"<<endl;
for (int i =0;i<eq_steps;i++){
	
	//Metropolis_Step(eval,mu,sigma);
	Metropolis_Step(rnd,position,step_length,acc_rate,mu,sigma);
	out<<i<<"\t"<<acc_rate/double(i)<<endl;
}
out.close();

cout<<"Equilibrium reached with acceptance rate "<<acc_rate/double(eq_steps)<<" after "<<eq_steps<<" steps"<<endl;

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
	/*
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
*/
/*ANNEALING:
	ciclo su beta che aumenta(T diminuisce):
		ciclo su N step a beta fissata:
			propongo un nuovo valore di mu e sigma
			valuto <H> con nuovi mu e sigma (metropolis)
			se new_<H> < old_<H> accetto la mossa (più vicino al GS)
			in caso contrario, valuto peso di Boltzmann e accetto il valore solo se rnd<BW
			-> più T si abbassa più la prob di accettare anche mosse sbagliate diminuisce
*/
/*
SApar simulated_annealing(double beta_start,int ann_steps,int Nsteps,int Nblocks,Random &rnd){
    //initial guessesfor mu and sigma
    //ofstream out ("./OUTPUT/SAenergy_lin.csv");
	//ofstream out1 ("./OUTPUT/SApars_lin.csv");
	ofstream out ("./OUTPUT/SAenergy.csv");
	ofstream out1 ("./OUTPUT/SApars.csv");
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
	//beta += 0.1;
}
out.close();
out1.close();

return old_par;
}

vec meanH_blockave (Random &rnd,int Nblocks,int Nsteps,SApar par){
	double position = 0;
	double block_ave =0;
	double block_ave2 =0;
	double err=0;
	double acc_rate=0;
	double step_length = 2.75;
	vec stats = zeros(2);
	Equilibration(rnd,position,step_length,acc_rate,par.mu,par.sigma,2000);
	for (int j=0; j<Nblocks;j++){
	
	
	double integral =0.;

	for (int i=1; i<Nsteps; i++){ //steps of RW
		double old_pos = position;
		Metropolis_Step(rnd,position,step_length,acc_rate,par.mu,par.sigma);
		integral+= Hpsi(par.mu,par.sigma,position)/psi_T(par.mu,par.sigma,position);	
	}
	
	double ave = integral/double(Nsteps);
	block_ave += ave;
	block_ave2 += ave*ave;
	err = sqrt((block_ave2/double(j+1)-pow(block_ave/double(j+1),2))/double(j+1));

	}
	stats[0]= block_ave/double(Nblocks);
	stats[1]=err;
	return stats;
}*/