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
double l= 0.7; //needle length
double D = 1;
Random rnd;
rnd.RandomSetup();
int N_throws = 100000;
int Nblocks=100;
  ofstream out("./OUTPUT/needle_positions.csv");
out<<"hit\txmin\txmax\tymin\tymax"<<endl;
  ofstream out1("./OUTPUT/pi_ave.csv");
out1<<"block\tave\tblock_ave\terr"<<endl;
int N_steps=1;
statistics pi;

for (int j=0;j<Nblocks;j++){
   pi.reset();
for (int k=0;k<N_steps;k++){
int N_hit =0;
   for(int i=0; i<N_throws; i++){
      //genero punto medio della barretta
  // double x_1 = rnd.Rannyu();
   double y1 = rnd.Rannyu();
   
   //genero angolo tra 0 e pi senza usare pi

   double sintheta;
   do{
   double Rsintheta = rnd.Rannyu(-1,1);
   double Rcostheta = rnd.Rannyu(-1,1);
   double R = sqrt(Rsintheta*Rsintheta+Rcostheta*Rcostheta);
   sintheta = Rsintheta/double(R);
   } while (fabs(sintheta)>1.);
   double y2= y1 +l*(sintheta);

      //double inf = double(int(y_m*10)/10.);
   //double sup = double(int(y_m*10)+1)/10.;
   int hit =0;
   if (y1==0. || y2<=0. || y2>=1.){
     N_hit++;

   }

   //out<<hit<<"\t"<<xmin<<"\t"<<xmax<<"\t"<<ymin<<"\t"<<ymax<<endl;
}
   //out<<hit<<"\t"<<xmin<<"\t"<<xmax<<"\t"<<ymin<<"\t"<<ymax<<endl;

pi.ave+=(2*l*N_throws)/double(N_hit*D);
}
pi.increment_block(N_steps);
pi.compute_err(j+1);
out1<<j<<"\t"<<pi.ave<<"\t"<<pi.block_ave/(double(j+1))<<"\t"<<pi.err<<endl;
}


return 0;

}