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

double H_2p (double a_0, double r, double z){
	double theta = acos(z/double(r));
	return pow((1./8.)*sqrt(2./(M_PI*pow(a_0,5)))*r*exp(-r/(2.*a_0))*cos(theta),2.);
}

double Metropolis_Acceptance(double p_new,double p_old,double T_fwd, double T_bkw){ //y:old move, x:new move
	double q = (T_fwd*p_new)/(T_bkw* p_old);
	if (q>=1.) return 1.;
	else return q;
}


void Metropolis_Step(Random &rnd,RandomWalk &RW, double &acc_rate, bool ground){

		vec old_pos = RW.Get_position();
		double r_old = RW.GetDistance();
double a_0=1;
		RW.Step_unif();
		double r_new = RW.GetDistance();

		double p_old,p_new;
		if(ground== true){
		p_old=H_1s(a_0,r_old);
		p_new = H_1s(a_0,r_new);
	
		}
		else {
	    p_old = H_2p(a_0,r_old,old_pos[2]);
		p_new = H_2p(a_0,r_new,RW.Get_position()[2]);
		}
		double T_bkw=1.;
		double T_fwd =1.;

		double A=Metropolis_Acceptance(p_new,p_old,T_fwd,T_bkw);

		double x=rnd.Rannyu();

		if(x>A) {
			RW.SetPosition(old_pos);
		}

		else acc_rate ++;
}

int main(){

vec step_length={0.7,2.3};


int Nblocks= 1;

int Nsteps=100000;
ofstream outa ("acceptance1s.csv");
outa<<"step_length\tacceptance"<<endl;

ofstream outa2 ("acceptance2p.csv");
outa2<<"step_length\tacceptance"<<endl;


for (int k = 0; k<10;k++){
Random rnd;
rnd.RandomSetup();

ofstream out("1s.csv");
ofstream outr("r_ave.csv");
outr<<"block\tave\tprog_ave\terr"<<endl;
out<<"x\ty\tz\tr"<<endl;

ofstream outp("2p.csv");

outp<<"x\ty\tz\tr"<<endl;
statistics stat;
vec acc_rate= zeros(2);

double r_ave =0;
double r_ave2 =0;
//for (int j=0; j<Nblocks;j++){
	double block_ave =0;
	vec start = zeros(3);
	for (int i=0;i<3;i++){start[i]=20.;}
	
	RandomWalk RW1s(rnd,start,step_length[0]);
	RandomWalk RW2p(rnd,start,step_length[1]);
	
	for (int i=0; i<Nsteps; i++){ //steps of RW
		
		Metropolis_Step(rnd,RW1s,acc_rate[0],1);
		Metropolis_Step(rnd,RW2p,acc_rate[1],0);
		for (int k=0;k<3;k++) {
			out<<RW1s.Get_position()[k]<<"\t";
			outp<<RW2p.Get_position()[k]<<"\t";
		}
		out<<RW1s.GetDistance()<<endl;
		outp<<RW2p.GetDistance()<<endl;
		//block_ave =+ RW.GetDistance();

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
acc_rate /=Nsteps*Nblocks;

cout<<"acceptance rate 1s: "<<acc_rate[0]<<endl;
cout<<"acceptance rate 2p: "<<acc_rate[1]<<endl;
outa<<step_length[0]<<"\t"<<acc_rate[0]<<endl;
outa2<<step_length[1]<<"\t"<<acc_rate[1]<<endl;
step_length+=0.1;

}

return 0;
}
/*

double x_start=0.;
double y_start =0.;
double z_start=0.;

double pos_x=0.;
double pos_y=0.;
double pos_z=0.;


const double a_0=1.;

const double N_bins=20;
const double bin_size= 2.*a_0/N_bins;


ofstream out("Orbital_1s.csv");
ofstream outh ("Distances.csv");
ofstream outa ("Acceptance.csv");
vec histx(N_bins);
	histx.zeros();
vec histy(N_bins);
	histy.zeros();
vec histz(N_bins);
	histz.zeros();

double acc_rate = 0;

nblocks = 100;
nsteps = 100;

for (int i=0;i<nblocks;i++){
	Random rnd;

	RandomWalk RW(step_length,x_start,y_start,z_start);
}
/*
for (int j=0; j<2; j++){ //Number of random walks
	vec countx(N_bins);
	countx.zeros();
	vec county(N_bins);
	vec countz(N_bins);
 
		/*
		for (int k=0; k<N_bins; k++){
			//if ((RW.Get_x()) >(k*bin_size) && RW.GetD_x()<(k*bin_size+bin_size)) count(k)++;
			//if (RW.GetDistance()>(k*bin_size) && RW.GetDistance()<(k*bin_size+bin_size)) count(k)++;
		out<<RW.Get_x()<<"\t"<<RW.Get_y()<<"\t"<<RW.Get_z()<<endl;
		}
	}
	for(int k=0; k<N_bins;k++) {
		//out<<count(k)<<"\t";
		//out<<endl;
	//	hist(k)+= count(k);
	}
*/

/*
for (int k=0; k<N_bins;k++){
	out<<k<<"\t"<<hist(k)<<endl;
}

*/


//cout<<"Acceptance rate: "<<acc_rate/double(Nsteps)<<endl;

