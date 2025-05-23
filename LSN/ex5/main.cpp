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
	return exp(-r/(a_0));
}

double H_2p (double a_0, double r, double theta){
	return (1./8.)*sqrt(2./(M_PI*pow(a_0,5)))*r*exp(-r/(2.*a_0))*cos(theta);
}

double Metropolis_Acceptance(double p_new,double p_old,double T_fwd, double T_bkw){ //y:old move, x:new move
	double q = (T_fwd*p_new)/(T_bkw* p_old);
	if (q>=1.) return 1.;
	else return q;
}
/*
void Metropolis_Step(Random rnd, RandomWalk &RW, const double a_0){
	double x_old=RW.Get_x();
		double y_old=RW.Get_y();
		double z_old=RW.Get_z();
		//double r_old = RW.GetDistance();
		double r_old = sqrt(x_old*x_old+y_old*y_old+z_old*z_old);

		RW.Step_3D();
		double x_new=RW.Get_x();
		double y_new=RW.Get_y();
		double z_new=RW.Get_z();
		//double r_old = RW.GetDistance();
		double r_new = sqrt(x_new*x_new+y_new*y_new+z_new*z_new);
		//double r_new =RW.GetDistance();

		double p_old = pow(H_1s(a_0,r_old),2);
		double p_new = pow(H_1s(a_0,r_new),2);
		double T_bkw=1.;
		double T_fwd =1.;

		double A=Metropolis_Acceptance(p_new,p_old,T_fwd,T_bkw);
		cout<<A<<endl;
		

		double x=rnd.Rannyu();

		if(x>A) {
			RW.SetPosition(x_old,y_old,z_old);
			//cout<<"check";
		}
		//if(A==1) RW.SetStart(xn,yn,zn);
		//else acc_rate ++;
}
*/
int main(){

double step_length=0.5;
double x_start=0.;
double y_start =0.;
double z_start=0.;

double pos_x=0.;
double pos_y=0.;
double pos_z=0.;
Random rnd;
RandomWalk RW(step_length,x_start,y_start,z_start);

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

int Nsteps=1000;
/*
for (int j=0; j<2; j++){ //Number of random walks
	vec countx(N_bins);
	countx.zeros();
	vec county(N_bins);
	vec countz(N_bins);
*/
for (int i=0; i<Nsteps; i++){ //steps of RW
		

double r_old = sqrt(pos_x*pos_x+pos_y*pos_y+pos_z*pos_z);


double theta=rnd.Rannyu(0,M_PI);
		double phi = rnd.Rannyu(0,2*M_PI);

		double x= step_length*sin(theta)*cos(phi);
		double y=step_length*sin(theta)*sin(phi);
		double z= step_length*cos(theta);

		pos_x += x;
		pos_y += y;
		pos_z += z;

		double r_new = sqrt(pos_x*pos_x+pos_y*pos_y+pos_z*pos_z);
		

		double p_old = pow(H_1s(a_0,r_old),2);
		double p_new = pow(H_1s(a_0,r_new),2);
		double T_bkw=1.;
		double T_fwd =1.;

		double A=Metropolis_Acceptance(p_new,p_old,T_fwd,T_bkw);
		cout<<A<<endl;
		

		double n=rnd.Rannyu();

		if(n>A) {
			pos_x += -x;
		pos_y += -y;
		pos_z += -z;
					//cout<<"check";
		}
		out<<pos_x<<"\t"<<pos_y<<"\t"<<pos_z<<endl;
	}
		//if(A==1) RW.SetStart(xn,yn,zn);
		//else acc_rate ++;

	//Metropolis_Step(rnd,RW,a_0);
		   
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
return 0;
}