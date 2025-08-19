#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <armadillo>
#include <random.h>
#include "lib.h"
using namespace std;
using namespace arma;


int main(){

double beta_start =0.2; //starting temperature

int ann_steps =30;
int Nsteps = 100;
int Nblocks = 10;
Random rnd;
rnd.RandomSetup();

simulated_annealing(beta_start,ann_steps,Nsteps,Nblocks,rnd);



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
