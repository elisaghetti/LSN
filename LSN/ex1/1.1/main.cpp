#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"
#include "statistics.h"

using namespace std;


int main (int argc, char *argv[]){
//
if (argc != 3) {
   cerr<<"Please input number of throws M and number of blocks N, with M a multiple of N"<<endl;
   return 1;
}
int M=atoi(argv[1]); //NUMBER OF THROWS            
int N=atoi(argv[2]);               //number of blocks
int L=M/N;                //number of throes in each block

statistics stat;

stat.SetN(N,L);
//Fix random seed

Random rnd;

rnd.RandomSetup();

string file = "data.csv";

ofstream output(file);




for(int i=0; i<M; i++){ //iterazione sui blocch

      double r=rnd.Rannyu();
      output <<r<<endl; 
   }
//1.1: calculation of average and variance

vector <double> block_ave; // vector of averages for each block
vector <double> block_ave_squared;

string type="AVE";
string file_results="statistics.csv";
ofstream out (file_results);
out<<"TYPE"<<"\t"<<"VALUE"<<"\t"<<"ERROR"<<endl;
stat.block_average_err(file,file_results,type);
stat.block_variance_err(file,file_results,type);


ofstream out4;
out4.open("Chi.txt");

//N=100;
//int T=10000;s

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


