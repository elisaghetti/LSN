#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"
#include "statistics.h"

using namespace std;

double error (double av, double av2, int n){

   if (n==0) return 0;
   else return sqrt(double((av2-av*av)/n));
}

void RandomSetup (Random &rnd){
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

  
}
 
int main (int argc, char *argv[]){
//
if (argc != 3) {
   cerr<<"Please input number of throws M and number of blocks N, with M a multiple of N"<<endl;
   return 1;
}
int M=atoi(argv[1]); //NUMBER OF THROWS            
int N=atoi(argv[2]);               //number of blocks
int L=M/N;                //number of throes in each block

statistics S;
//Fix random seed

Random rnd;

RandomSetup(rnd);

rnd.SaveSeed();

//1.1: calculation of average
vector <double> block_ave (N,0); // vector of averages for each block
vector <double> block_ave_squared(N,0);

//1.2 calculation of variance
vector <double> block_variance(N,0);
vector <double> block_variance_squared(N,0);

//ottengo delle stime della media(A_i) e della varianza 
for(int i=0; i<N; i++){ //iterazione sui blocchi

   double sum1=0;
   double sum2=0;

   for(int j=0; j<L; j++){ //iterazione sugli elementidel blocco

      double r=rnd.Rannyu();

      sum1 = sum1 + r;
      sum2 = sum2 + pow((r-0.5),2);
   }

   block_ave[i]=(double(sum1/L)); //media sul singolo blocco
   block_ave_squared[i]=(block_ave[i]*block_ave[i]); // quadrato della media sul singolo blocco

   block_variance[i]=(double(sum2/L));
   block_variance_squared[i]=(block_variance[i]*block_variance[i]);
}

//Calcolo della media e varianza cumulative (sommando progressivamente sui blocchi)
double sum_prog = 0;
double sum_prog_squared=0;

double sum1_prog = 0;
double sum1_prog_squared=0;

vector <double> cumulative_ave(N,0);
vector <double> cumulative_ave_squared(N,0);
vector <double> ave_errors(N,0);

vector <double> cumulative_var(N,0);
vector <double> cumulative_var_squared(N,0);
vector <double> var_errors(N,0);

ofstream out;
out.open("statistics.csv");

 

for (int i=0; i<N; i++){
   sum_prog= sum_prog+ block_ave[i]; //sommo sugli ai 
   sum_prog_squared = sum_prog_squared + block_ave_squared[i]; //sommatoria sugli Ai^2

   sum1_prog= sum1_prog+ block_variance[i];
   sum1_prog_squared = sum1_prog_squared + block_variance_squared[i];

   cumulative_ave[i]=(double(sum_prog/(i+1)));
   cumulative_ave_squared[i]=(double(sum_prog_squared/(i+1)));
   ave_errors[i]=(error(cumulative_ave[i],cumulative_ave_squared[i], i));

   cumulative_var[i]=(double(sum1_prog/(i+1)));
   cumulative_var_squared[i]=(double(sum1_prog_squared/(i+1)));
   var_errors[i]=(error(cumulative_var[i],cumulative_var_squared[i], i));

   out<<cumulative_ave[i]<<"\t"<<ave_errors[i]<<"\t"<<cumulative_var[i]<<"\t"<<var_errors[i]<<endl;
  
}

out.close();


ofstream out4;
out4.open("Chi.txt");

//N=100;
//int T=10000;

vector<double> chi_squared;
for (int j=0; j<N; j++){ //intervalli in cui ho diviso (0,1): per ognuno calcolo chi quadro con la sommatoria
   double chi_j=0;
   
   for (int i=0; i<N; i++){ //genero 100 blocchi da 100 numeri casuali e controllo in quale intervallo sono
   double n_i=0;
   for(int k=0; k<M; k++){  
      double r= rnd.Rannyu();
      if (r*N>=i && r*N <i+1) n_i++;
      }
      chi_j += pow(n_i-double(M)/N,2)/(double(M)/N);
}
 
  out4<<chi_j<<endl;
}


return 0;

}


