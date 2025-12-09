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

int main (int argc, char *argv[]){
//
if (argc != 3) {
   cerr<<"Please input number of throws M and number of blocks N, with M a multiple of N"<<endl;
   return 1;
}
int nblocks=atoi(argv[1]); //NUMBER OF blocks           
int nthrows=atoi(argv[2]);               //number of throws in each block
                //number of throes in each block

statistics stat_int;
statistics stat_var;

Random rnd;

rnd.RandomSetup();

ofstream out("./OUTPUT/integral.csv");
out<<"block\tave\tblock_ave\terr"<<endl;

ofstream outv("./OUTPUT/variance.csv");
outv<<"block\tave\tblock_ave\terr"<<endl;

for(int i=0; i<nblocks; i++){ //iterazione sui blocch
   stat_int.reset();
   stat_var.reset();

   for (int j=0;j<nthrows;j++){
      double r=rnd.Rannyu();
      stat_int.ave += r;
      stat_var.ave += pow(r-0.5,2);
  
   }
   
   stat_int.increment_block(nthrows);
   stat_int.compute_err(i+1);

   stat_var.increment_block(nthrows);
   stat_var.compute_err(i+1);
   
   out<<i<<"\t"<<stat_int.ave<<"\t"<<stat_int.block_ave/(i+1)<<"\t"<<stat_int.err<<endl;
   outv<<i<<"\t"<<stat_var.ave<<"\t"<<stat_var.block_ave/(i+1)<<"\t"<<stat_var.err<<endl;
   }
/*
ofstream out4;
out4.open("Chi.csv");

int n_int=100;
int nthr=10000;

vector<double> chi_squared;
for (int j=0; j<n_int; j++){ //intervalli in cui ho diviso (0,1): per ognuno calcolo chi quadro con la sommatoria
   double chi_j=0; //for every  interval I generate 10^4 random numbers 
   
   for (int i=0; i<nthr; i++){ 
   int in_interval=0;
   int expected =nthr
   for(int k=0; k<nthr; k++){  
      double r= rnd.Rannyu();
      if (r*nthr>=i && r*nthr <i+1) in_interval++;
      }
      chi_j += pow(in_interv-double(M)/N,2)/(double(M)/N);
}
 
  out4<<chi_j<<endl;
}
out4.close();*/
return 0;

}


