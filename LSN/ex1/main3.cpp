//ESERCIZIO 1.3

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"
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

using namespace std;
int main() {
double l= 0.6; //needle length
double D = 1;
Random rnd;
rnd.RandomSetup();
int N_throws = 10000;
int Nblocks=100;

  //ofstream out("./OUTPUT/positions.csv");
//out<<"hit\txmin\txmax\tymin\tymax"<<endl;
  ofstream out1("./OUTPUT/pi_ave.csv");
out1<<"block\tave\tblock_ave\terr"<<endl;
int N_steps=1;
statistics pi;

for (int j=0;j<Nblocks;j++){
   pi.reset();

int N_hit =0;
   for(int i=0; i<N_throws; i++){
      int hit =0;
      //genero punto medio della barretta
  double x1 = rnd.Rannyu(-1,1); //just for visualization purposes
   double y1 = rnd.Rannyu(0,D);
   if (y1==0. or y1==D ){
     N_hit++;
     hit=1;
     continue;

   }
   //genero angolo tra 0 e pi senza usare pi

   double R,Rsintheta;
   do{
   Rsintheta = rnd.Rannyu(-1,1);
   double Rcostheta = rnd.Rannyu(-1,1);
   R = sqrt(Rsintheta*Rsintheta+Rcostheta*Rcostheta);
   } while (R>1);
   double sintheta = Rsintheta/double(R);
   double y2= y1 +l*(sintheta);
   int x_sign=1;
   if(rnd.Rannyu(-1,1)<0) x_sign=-1;
   double x2=x1+x_sign*sqrt(l*l-(y2-y1)*(y2-y1));
   
   if (y2<=0. or y2>=D ){
     N_hit++;
     hit=1;
   }
  // out<<hit<<"\t"<<x1<<"\t"<<x2<<"\t"<<y1<<"\t"<<y2<<endl;

   }
pi.ave=(2*l*N_throws)/double(N_hit*D);
pi.increment_block(1);
pi.compute_err(j+1);
out1<<j<<"\t"<<pi.ave<<"\t"<<pi.block_ave/(double(j+1))<<"\t"<<pi.err<<endl;
}


return 0;

}