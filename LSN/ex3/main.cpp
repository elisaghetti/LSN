#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"


using namespace std;

struct statistics {
   double ave=0.;
   double ave2=0.;
   double block_ave=0.;
   double block_ave2=0;
   double err=0.;
   
   void reset(){
      ave=0;
      ave2=0;
      err=0;
   }
   void compute_err(int n){
      if (n==1) err=0;
      else err=sqrt((block_ave2/(n)-pow(block_ave/n,2))/double(n-1));
   }

   void increment_block(int N){
      ave/=N;
      ave2=ave*ave;
      block_ave+=ave;
      block_ave2+=ave2;
   }
};



double GBM(double t0, double t, double S0, double r, double sigma, double Z){
	return S0 * exp((r-0.5*sigma*sigma)*(t-t0)+sigma*Z*sqrt(t-t0));
}

double call_price (double t,double T, double K, double S, double r){
	if(S-K >0) return exp(-r*T)*(S-K);
	else return 0;
}

double put_price(double t,double T, double K, double S, double r){
	if(K-S >0) return exp(-r*T)*(K-S);
	else return 0;
}

int main(){

Random rnd;

rnd.RandomSetup();

statistics call;
statistics put;

double S0 = 100.; //intial price
double T=1.; //final time
double K =100.; //strike price
double r =0.1;
double sigma = 0.25;

int N_tot =1; //number of asset prices at time T;
int N_blocks=1;
int n = N_tot /N_blocks;


//direct sampling 

/*
ofstream out("./OUTPUT/call_direct.csv");
out<<"block\tave\tblock_ave\terr"<<endl;


ofstream out1("./OUTPUT/put_direct.csv");
out1<<"block\tave\tblock_ave\terr"<<endl;
*/
ofstream out2("./OUTPUT/S_sampling.csv");
out2<<"t\tS"<<endl;

for(int i=0; i<N_blocks; i++){
	call.reset();
	put.reset();
	for(int j=0;j<n;j++){
		double Z=rnd.Gauss(0,1);
		double S =GBM(0.,T,S0,r,sigma,Z);
		out2<<T<<"\t"<<S<<endl;
		double C_i = call_price(0.,T,K,S,r);
		call.ave+=C_i;
		double P_i=put_price(0.,T,K,S,r);
		put.ave+=P_i;
	}	
	call.increment_block(n);
	call.compute_err(i+1);
	//out<<i<<"\t"<<call.ave<<"\t"<<call.block_ave/double(i+1)<<"\t"<<call.err<<endl;

	put.increment_block(n);
	put.compute_err(i+1);
	//out1<<i<<"\t"<<put.ave<<"\t"<<put.block_ave/double(i+1)<<"\t"<<put.err<<endl;
}
//out.close();
//out1.close();
//discretized sampling
/*
ofstream out2c("./OUTPUT/call_discretized.csv");
out2c<<"block\tave\tblock_ave\terr"<<endl;


ofstream out2p("./OUTPUT/put_discretized.csv");
out2p<<"block\tave\tblock_ave\terr"<<endl;
*/

statistics call1;
statistics put1;

for(int i=0; i<N_blocks; i++){
	call1.reset();
	put1.reset();
	for(int j=0;j<n;j++){
		double t0=0;
		double C_i=0;
		double P_i=0;
		double S;
		double S_in =S0;
		while (t0<T){
			double Z=rnd.Gauss(0,1);
			double t=t0 + T/100.;
			S = GBM(t0,t,S_in,r,sigma,Z);
			out2<<t<<"\t"<<S<<endl;
			t0 = t;
			S_in=S;
			
		}
		C_i = call_price(0,T,K,S,r);
		P_i=put_price(0,T,K,S,r);
			
		call1.ave+=C_i;
		put1.ave+=P_i;
	}	
	call1.increment_block(n);
	call1.compute_err(i+1);
	//out2c<<i<<"\t"<<call1.ave<<"\t"<<call1.block_ave/double(i+1)<<"\t"<<call1.err<<endl;

	put1.increment_block(n);
	put1.compute_err(i+1);
	//out2p<<i<<"\t"<<put1.ave<<"\t"<<put1.block_ave/double(i+1)<<"\t"<<put1.err<<endl;
}
/*

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
*/
	return 0;
}
