#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <armadillo>
#include <random.h>

using namespace std;
using namespace arma;

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

void Equilibration(Random& rnd, double &position,double step_length,double &acc_rate, double mu, double sigma,int eq_steps){
ofstream out("../OUTPUT/acceptance.csv");
out<<"step\tacc_rate"<<endl;
for (int i =0;i<eq_steps;i++){
	
	Metropolis_Step(rnd,position,step_length,acc_rate,mu,sigma);
	out<<i<<"\t"<<acc_rate/double(i)<<endl;
}
out.close();

cout<<"Equilibrium reached with acceptance rate "<<acc_rate/double(eq_steps)<<" after "<<eq_steps<<" steps"<<endl;
out.close();
}

int main(){


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

return 0;
}
