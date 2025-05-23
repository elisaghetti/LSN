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



 
int main (int argc, char *argv[]){


int M=10000; //NUMBER OF THROWS            
int N=100;               //number of blocks
int L=M/N;                //number of throes in each block

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

//1.1: calculation of average
vector <double> block_ave; // vector of averages for each block
vector <double> block_ave_squared;

//1.2 calculation of variance
vector <double> block_variance;
vector <double> block_variance_squared;


for(int i=0; i<N; i++){

   double sum1=0;
   double sum2=0;

   for(int j=0; j<L; j++){

      double r=rnd.Rannyu();

      sum1 = sum1 + r;
      sum2 = sum2 + pow((r-0.5),2);
   }

   block_ave.push_back(double(sum1/L));
   block_ave_squared.push_back(block_ave[i]*block_ave[i]);

   block_variance.push_back(double(sum2/L));
   block_variance_squared.push_back(block_variance[i]*block_variance[i]);
}
/*
for(int i=0; i< M; i++){

   double sum1=0;
   double sum2=0;

   for(int j=0; j<L; j++){

      double r=rnd.Rannyu();

      sum1 = sum1 + r;
      sum2 = sum2 + pow((r-0.5),2);
   }

   block_ave.push_back(double(sum1/L));
   block_ave_squared.push_back(block_ave[i]*block_ave[i]);

   block_variance.push_back(double(sum2/L));
   block_variance_squared.push_back(block_variance[i]*block_variance[i]);
}
*/
double sum_prog = 0;
double sum_prog_squared=0;

double sum1_prog = 0;
double sum1_prog_squared=0;

vector <double> cumulative_ave;
vector <double> cumulative_ave_squared;
vector <double> ave_errors;

vector <double> cumulative_var;
vector <double> cumulative_var_squared;
vector <double> var_errors;

ofstream out, out1,out2,out3;
out.open("average.txt");
out1.open("errors.txt");
out2.open("variance.txt");
out3.open("var_errors.txt");

// Prova a condensarli in un unico file 

for (int i=0; i<N; i++){
   sum_prog= sum_prog+ block_ave[i];
   sum_prog_squared = sum_prog_squared + block_ave_squared[i];

   sum1_prog= sum1_prog+ block_variance[i];
   sum1_prog_squared = sum1_prog_squared + block_variance_squared[i];

   cumulative_ave.push_back(double(sum_prog/(i+1)));
   cumulative_ave_squared.push_back(double(sum_prog_squared/(i+1)));
   ave_errors.push_back(error(cumulative_ave[i],cumulative_ave_squared[i], i));

   cumulative_var.push_back(double(sum1_prog/(i+1)));
   cumulative_var_squared.push_back(double(sum1_prog_squared/(i+1)));
   var_errors.push_back(error(cumulative_var[i],cumulative_var_squared[i], i+1));

   out<<cumulative_ave[i]<<endl;
   out1<<ave_errors[i]<<endl;
   out2<<cumulative_var[i]<<endl;
   out3<<cumulative_var_squared[i]<<endl;


}

out.close();
out1.close();

ofstream out4;
out4.open("Chi.txt");

double a=0.;
int n=10000;

vector<double> chi_squared;
double chi;

for (int i=0; i<N; i++){
a = a + 0.001;
int obs=0;

   for(int j=0; j<n; j++){
         double r=rnd.Rannyu();
         //out4<<r<<endl;
         if(r>(a-0.001) && r<a) {
            obs++;
           //out4<<r<<" "<<obs<<endl;
          }
    }

chi = double(pow(obs- double(n/N),2)/(n/N));
out4<<chi<<endl;
chi_squared.push_back(chi);

}
/*
double chi_tot=0;

for(int i=0; i<100; i++){
   chi_tot = chi_tot + chi_squared[i];
}

*/


//ESERCIZIO 1.2
//exponential distrib
/*
ofstream out5;
out5.open("expo.txt");

vector <double> prog_SN;

int steps[4]={1,2,10,100}; //number of steps in block

for (int j=0; j<4;j++){
   int t = steps[j]; 
   int n_blocks= M/t;

   for (int i=0; i<n_blocks; i++){   
      double SN=0;

   for(int k=0; k<t; k++){
   double r=rnd.Exp(1);
   SN += r;
   }
prog_SN.push_back(double(SN)/t);
//sistemare questa cosa per produrre grafici separati
if(j==3) out5<<prog_SN[i]<<endl;
  
}
}
*/
//questo funziona:

ofstream out5;
out5.open("expo.txt");
for (int i=0; i<M; i++){
   double r=rnd.Cauchy(0,1);
   out5<<r<<endl;
}

return 0;

}


