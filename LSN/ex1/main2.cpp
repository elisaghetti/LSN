#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"


using namespace std;


int main (int argc, char *argv[]){



Random rnd;

rnd.RandomSetup();



int nthrows=10000;

ofstream out("./OUTPUT/SN_exp.csv");
out<<"N\treal_index\tSN"<<endl;
ofstream out1("./OUTPUT/SN_unif.csv");
out1<<"N\treal_index\tSN"<<endl;
ofstream out2("./OUTPUT/SN_cauchy.csv");
out2<<"N\treal_index\tSN"<<endl;

int N_steps [4]= {1,2,10,100};

for(int j=0; j<4;j++){

   int N= N_steps[j];

for (int n=0;n<nthrows;n++){
   double exp=0;
   double unif=0.;
   double cauchy = 0.;
   
   for (int i=0; i<N; i++){

         exp+=rnd.Exp(1);
         unif+= rnd.Rannyu();
         cauchy += rnd.Cauchy(0,1);
      }
      exp/=N;
      unif/=N;
      cauchy/=N;

     
      out<<N<<"\t"<<n<<"\t"<<exp<<endl;
      out1<<N<<"\t"<<n<<"\t"<<unif<<endl;
      out2<<N<<"\t"<<n<<"\t"<<cauchy<<endl;
      

}

}
return 0;

}














 //number of steps in block
/*

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


