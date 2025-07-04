#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"
#include "statistics.h"
#include "RandomWalk.h"
#include <armadillo>

using namespace std;
using namespace arma;

double H_1s(double a_0, double r){
	return exp(-2*r/(a_0));
}

double H_2p (double a_0, double r, double theta){
	return (1./8.)*sqrt(2./(M_PI*pow(a_0,5)))*r*exp(-r/(2.*a_0))*cos(theta);
}

double Metropolis_Acceptance(double p_new,double p_old,double T_fwd, double T_bkw){ //y:old move, x:new move
	double q = (T_fwd*p_new)/(T_bkw* p_old);
	if (q>=1.) return 1.;
	else return q;
}

void Metropolis_Step(Random& rnd, vec &position,double step_length,double &acc_rate){
	if (position.size()!=3) cerr<<"Input 3 dimensional postion vector"<<endl;
	double a_0 = 1.;


	vec old_pos = position;
		double r_old = norm(old_pos);

	vec new_pos = zeros(3);
	for (int i=0;i<3;i++) new_pos[i]=old_pos[i]+step_length*rnd.Rannyu(-1,1);
double r_new = norm(new_pos);
	

	double p_old = H_1s(a_0,r_old);
	double p_new = H_1s(a_0,r_new);

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

int main(){


double step_length=1.2;

int Nblocks= 10000;

int Nsteps=100000;
ofstream outa ("acceptance.csv");
outa<<"step_length\tacceptance"<<endl;
//for (int k = 0; k<10;k++){
Random rnd;
rnd.RandomSetup();

ofstream out("1s.csv");
ofstream outr("r_ave.csv");
outr<<"block\tave\tprog_ave\terr"<<endl;
out<<"x\ty\tz\tr"<<endl;
statistics stat;
double acc_rate=0;
double r_ave =0;
double r_ave2 =0;
//for (int j=0; j<Nblocks;j++){
	double block_ave =0;
	vec position = zeros(3);
	for (int i=0;i<3;i++){position[i]=100.;}

	for (int i=0; i<Nsteps; i++){ //steps of RW

		for (int k=0;k<3;k++) out<<position[k]<<"\t";
		out<<norm(position)<<endl;

		Metropolis_Step(rnd,position,step_length,acc_rate);
	

//block_ave+=position;
}
r_ave =+ block_ave/Nsteps;
r_ave2 =+ block_ave*block_ave;
double err = stat.error(r_ave, r_ave2,Nsteps);
//outr<<j<<"\t"<<block_ave<<"\t"<<r_ave<<"\t"<<err<<endl;
//out<<position[0]<<"\t"<<position[1]<<"\t"<<position[2]<<"\t"<<sqrt(dot(position,position))<<endl;
//global_ave += block_ave/Nsteps;
//out<<global_ave[0]<<'\t'<<global_ave[1]<<'\t'<<global_ave[2]<<'\t'<<norm(global_ave)<<endl;
//}
acc_rate/= Nsteps;
cout<<"acceptance rate: "<<acc_rate<<endl;
//outa<<step_length<<"\t"<<acc_rate<<endl;
//step_length+=0.1;
//}

return 0;
}
