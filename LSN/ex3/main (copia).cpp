#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"

using namespace std;

double error (double av, double av2, int n){

   if (n==0) return 0;
   else return sqrt(double((av2-av*av)/n));
}

double GBM(double t0, double t, double S0, double r, double sigma, double Z){
	return S0 * exp((r-0.5*sigma*sigma)*(t-t0)+sigma*Z*sqrt(t-t0));
}

double call (double t,double T, double K, double S0, double r, double sigma, double Z){
	double S = GBM(t,T,S0,r,sigma,Z);
	if(S-K >0) return exp(-r*T)*(S-K);
	else return 0;
}

double put(double t,double T, double K, double S0, double r, double sigma, double Z){
	double S = GBM(t,T,S0,r,sigma,Z);
	if(K-S >0) return exp(-r*T)*(K-S);
	else return 0;
}

int main(){

Random rnd;

rnd.RandomSetup();

rnd.SaveSeed();

double S0 = 100.; //intial price
double T=1.; //final time
double K =100.; //strike price
double r =0.1;
double sigma = 0.25;

int N_tot =10000; //number of asset prices at time T;
int N_blocks=100;
int n = N_tot /N_blocks;


//direct sampling 

double C=0;
double P=0;
ofstream out("prices.csv");

vector <double> block_aveC(N_blocks,0);
vector <double> block_aveP(N_blocks,0);

vector <double>block_aveC2(N_blocks,0);
vector <double>block_aveP2(N_blocks,0);


for(int i=0; i<N_blocks; i++){
	double sumC=0;
	double sumC2=0;

	double sumP=0;
	double sumP2=0;
	for(int j=0; j<n;j++){
		double Z=rnd.Gauss(0,1);
		double S =GBM(0.,T,S0,r,sigma,Z);

		double C_i = call(0.,T,K,S0,r,sigma,Z);

		double P_i=put(0.,T,K,S0,r,sigma,Z);
		C+=C_i;
		P+= P_i;
		sumC +=C_i;
		sumC2 += C_i*C_i;

		sumP += P_i;
		sumP2 += P_i * P_i;
	}
	block_aveC[i]=sumC/double(n);
	block_aveC2[i]=block_aveC[i]*block_aveC[i]; //vettore di medie dei quadrati per ogni blocco

	
	block_aveP[i]=sumP/double(n);
	block_aveP2[i] = block_aveP[i]* block_aveP[i];

}
cout<<"Call: "<<C/double(N_tot)<<"\tPut: "<<P/double(N_tot)<<endl;
double meanC=0;
double meanC2=0;

double meanP =0;
double meanP2=0;
for (int i=0; i<N_blocks;i++){
	meanP += block_aveP[i];
	meanC+=block_aveC[i];

	meanC2 += block_aveC2[i];
	meanP2+= block_aveP2[i];

	double errC = error(meanC/double(i+1), meanC2/double(i+1),i+1);
	double errP = error(meanP/double(i+1), meanP2/double(i+1),i+1);

out<<i<<"\t"<<meanC/double(i+1)<<"\t"<<errC<<"\t"<<meanP/double(i+1)<<"\t"<<errP<<endl;
}


//GBM sampling
double C1=0;
double P1=0;
ofstream out1("prices1.csv");

vector <double> block_aveC_1(N_blocks,0);
vector <double> block_aveP_1(N_blocks,0);

vector <double>block_aveC2_1(N_blocks,0);
vector <double>block_aveP2_1(N_blocks,0);

for(int i=0; i<N_blocks; i++){
	double sumC=0;
	double sumC2=0;

	double sumP=0;
	double sumP2=0;
	for(int j=0; j<n;j++){

		double t0=0;
		double S=S0;
		double C_i=0;
		double P_i=0;
		int Nsteps=0;

		//double S_sum=0;
		while (t0<T){
			double Z=rnd.Gauss(0,1);
			//S_sum +=S;
			//cout<<S_sum<<endl;
			double t=t0 + T/100.;

			
			C_i = call(t0,t,K,S,r,sigma,Z);
			P_i=put(t0,t,K,S,r,sigma,Z);
			S = GBM(t0,t,S,r,sigma,Z);
			//cout<<S<<endl;
			t0 = t;

		}


			C1+=C_i;
			P1+= P_i;
			sumC +=C_i;
			sumC2 += C_i*C_i;

			sumP += P_i;
			sumP2 += P_i * P_i;
		}	
	
	
	block_aveC_1[i]=sumC/(double(n));
	block_aveC2_1[i]=block_aveC_1[i]*block_aveC_1[i]; //vettore di medie dei quadrati per ogni blocco

	
	block_aveP_1[i]=sumP/double(n);
	block_aveP2_1[i] = block_aveP_1[i]* block_aveP_1[i];


}
cout<<"Call: "<<C1/double(N_tot)<<"\t"<<"Put: "<<P1/double(N_tot)<<endl;


double meanC1=0;
double meanC2_1=0;

double meanP_1 =0;
double meanP2_1=0;

for (int i=0; i<N_blocks;i++){
	meanP_1 += block_aveP_1[i];
	meanC1+=block_aveC_1[i];

	meanC2_1 += block_aveC2_1[i];
	meanP2_1+= block_aveP2_1[i];

	double errC1 = error(meanC1/double(i+1), meanC2_1/double(i+1),i+1);
	double errP1 = error(meanP_1/double(i+1), meanP2_1/double(i+1),i+1);

out1<<i<<"\t"<<meanC1/double(i+1)<<"\t"<<errC1<<"\t"<<meanP_1/double(i+1)<<"\t"<<errP1<<endl;
}

	return 0;
}
