#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"

using namespace std;

double integrand(double x){
	return (M_PI*0.5)*cos(M_PI*x*0.5);
}


double error (double av, double av2, int n){

   if (n==0) return 0;
   else return sqrt(double((av2-av*av)/n));
}

double prob (double x) {
	float N = 1. - M_PI/12.; //normalizzazione
	return N*(1.-(M_PI/4.)*x*x);
}

int main() {

// Define random generator
Random rnd;

int seed[4];
   int p1, p2;
   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   //Il seed è uno stato a 48 bit salvato in 4 interi, che sono scritti nel file seed.in

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();

   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

//1.1 Calcolo integrale con metodo della media

int N=100000; // numero di punti generati
int N_blocks= 1000; 
int n= N/N_blocks; // num elementi in ogni blocco

vector <double> block_ave(N_blocks,0);
vector <double> block_ave_squared(N_blocks,0);

ofstream out, out1;
out.open("integral.txt");
out1.open("errors.txt");
for(int i=0; i<N_blocks; i++){
	double sum=0;
	for (int j=0; j<n; j++) {
		double x= rnd.Rannyu();	
		double f= integrand(x);
		sum+= f;
	}


	block_ave[i]= sum/double(n);
	block_ave_squared[i]=block_ave[i]*block_ave[i];

	
}

double I= 0;
double ave2=0;
vector <double> errors(N_blocks,0);

for(int i=0; i<N_blocks; i++){
	I+=block_ave[i];
	ave2 += block_ave_squared[i];
	double err = error(I/double(i+1),ave2/double(i+1),i+1);
	out<<I/(i+1)<<endl;
	out1<<err<<endl;
	
}
cout<<"Integral: "<<I/double(N_blocks)<<endl;


//ESERCIZIO 1.1.2
return 0;
}
