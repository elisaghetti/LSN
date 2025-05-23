#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"

using namespace std;



 
int main (int argc, char *argv[]){


//Fix random seed

Random rnd;

//Perchè non funziona se lo metto in una funzione?

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

   rnd.SaveSeed();


//ESERCIZIO 1.2
//exponential distrib
//int N=1; //2,10,100
int N_throws=10000;
ofstream out5,out6,out7;

out5.open("expo.csv");
out6.open("unif.txt");
out7.open("cauchy.txt");

vector <double> prog_SN_exp;
vector <double> prog_SN_unif;
vector <double> prog_SN_cauchy;
int steps[4]={1,2,10,100}; //number of steps in block

for (int j=0; j<4;j++){
   int N = steps[j];
   for(int i=0; i<N_throws; i++){ 
   //int n_blocks= N_throws/N; 
      double SN_exp=0;
      double SN_unif=0;
      double SN_cauchy=0;

      for(int k=0; k<N; k++){
         double r_exp=rnd.Exp(1);
         double r_unif= rnd.Rannyu();
         double r_cauchy = rnd.Cauchy(0,1);

         SN_exp += r_exp;
         SN_unif += r_unif;
         SN_cauchy += r_cauchy;

      }
   prog_SN_exp.push_back(double(SN_exp)/N);
   prog_SN_unif.push_back(double(SN_unif)/N);
   prog_SN_cauchy.push_back(double(SN_cauchy)/N);


   out5<<j<<"\t"<<prog_SN_exp[i]<<endl;
   out6<<j<<"\t"<<prog_SN_unif[i]<<endl;
   out7<<j<<"\t"<<prog_SN_cauchy[i]<<endl;
}

}


//questo funziona per exp, non per cauchy
/*
ofstream out5;
out5.open("expo.txt");
for (int i=0; i<M; i++){
   double r=rnd.Exp(0,1);
   out5<<r<<endl;
}
*/


return 0;

}


