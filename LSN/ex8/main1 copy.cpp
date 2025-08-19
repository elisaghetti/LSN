#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <armadillo>
#include <random.h>

using namespace std;
using namespace arma;

struct metro { //metropolis algorithm parameters
	Random rand;
	double step_length;
	double acc_rate=0.;
	double position=0.;
};
double H_1s(double a_0, double r){
	return exp(-2*r/(a_0));
}

double H_2p (double a_0, double r, double theta){
	return (1./8.)*sqrt(2./(M_PI*pow(a_0,5)))*r*exp(-r/(2.*a_0))*cos(theta);
}
double psi_T(double mu,double sigma,double x){
	
	return exp(-pow(x-mu,2)/(2*sigma*sigma)) +exp(-pow(x+mu,2)/(2*sigma*sigma));

}

double dpsi2 (double mu, double sigma, double x){
	double a = pow((x-mu)/sigma,2);
	double b = pow((x+mu)/sigma,2);
	return (pow(sigma,-2)*a-pow(sigma,-2))*exp(-0.5*a)+(pow(sigma,-2)*b-pow(sigma,-2))*exp(-0.5*b);
}

double Metropolis_Acceptance(double p_new,double p_old,double T_fwd, double T_bkw){ //y:old move, x:new move
	double q = (T_fwd*p_new)/(T_bkw* p_old);
	if (q>=1.) return 1.;
	else return q;
}


double pot(double x){
	return pow(x,4)-(5./2.)*x*x;
}
double Hpsi (double mu, double sigma, double x){
	return -0.5*dpsi2(mu,sigma,x)+pot(x)*psi_T(mu,sigma,x);
}
void Metropolis_Step(metro &eval, double mu, double sigma){
	Random rnd = eval.rand;
	double old_pos = eval.position;
double normalization = 2.*sigma*sqrt(M_PI)*(1+exp(-mu*mu/(sigma*sigma)));
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
/*
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
*/
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


int main(){

double beta =0.1; //starting temperature
double mu =1.; //initial guessesfor mu and sigma
double sigma= 1.;
int ann_steps =1000;
int Nsteps = 100;
Random rnd;
		double position = 0;
			double acc_rate =0;	double step_length=2.75;
	//Equilibration(rnd,position,step_length,acc_rate,mu,sigma,2000);
rnd.RandomSetup();
for (int k =0; k<ann_steps;k++){
	//cout<<"begin T="<<1./beta<<endl;

	double ann_step_length=1.5;
	double mean_H=0;


double ann_acc_rate =0;
	for (int j=0; j<Nsteps;j++){//steps at a fixed temperature, at each step I need to evaluate <H>
	
   

	double integral =0.;
	double p_old = exp(-beta*mean_H); //Boltzmann weight evaluation
 	//Metropolis evaluation of <H> at each step with a fixed T:for high beta accept a lot of wrong moves, for low beta converge to good value
	
	
	double new_mean_H = compute_mean_H(rnd,Nsteps,mu,sigma);
	double p_new = exp(-beta*new_mean_H);
	double A = Metropolis_Acceptance(p_new,p_old,1.,1.);
	double r = rnd.Rannyu();
	if (r<A) {
		ann_acc_rate++;
		mean_H=new_mean_H;
	}	
	
}
if (k%100==0)cout<<"acc rate: "<<ann_acc_rate/double(Nsteps)<<endl;
if (k%100==0)cout<<"<H> estimate at beta="<<double(beta)<<": "<<mean_H<<endl;
beta+=0.05;
}

////8.1
/*
double step_length=2.75;

int Nblocks= 50;

int Nsteps=10000;

ofstream outa ("..OUTPUT/acceptance.csv");
outa<<"step_length\tacceptance"<<endl;
//for (int k = 0; k<10;k++){
Random rnd;
rnd.RandomSetup();
double mu =0.85;
double sigma =0.65;



ofstream outr("../OUTPUT/ave.csv");
outr<<"block\tintegral\tprog_ave\terr"<<endl;
//!!!!!KEEP COMMENTED WHEN DOING BLOCK SIMULATIONS!!!!!!!!!!!!!!!!!!!!
//ofstream out ("../OUTPUT/psi_sampling.csv");
//out<<"step\tx"<<endl;

double position = 0;
double block_ave =0;
double block_ave2 =0;
double acc_rate=0;
Equilibration(rnd,position,step_length,acc_rate,mu,sigma,2000);

for (int j=0; j<Nblocks;j++){
	
	
	double integral =0.;

	for (int i=1; i<Nsteps; i++){ //steps of RW
		double old_pos = position;
		//out<<i<<"\t"<<position<<endl;
		Metropolis_Step(rnd,position,step_length,acc_rate,mu,sigma);
		integral+= Hpsi(mu,sigma,position)/psi_T(mu,sigma,position);	
	}
	
	double ave = integral/double(Nsteps);
	block_ave += ave;
	block_ave2 += ave*ave;
	double err = sqrt((block_ave2/double(j+1)-pow(block_ave/double(j+1),2))/double(j+1));

	outr<<j<<"\t"<<integral/double(Nsteps)<<"\t"<<block_ave/double(j+1)<<"\t"<<err<<endl;

}
	acc_rate/=( Nsteps*Nblocks);
cout<<"acceptance rate: "<<acc_rate<<endl;
*/
return 0;
}
