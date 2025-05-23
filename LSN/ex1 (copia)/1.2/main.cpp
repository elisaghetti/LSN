#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"
#include "statistics.h"

using namespace std;



 
int main (int argc, char *argv[]){



Random rnd;

rnd.RandomSetup();

statistics stats;

int N_throws=10000;

ofstream out("SN_exp.csv");
ofstream out1("SN_unif.csv");
ofstream out2("SN_cauchy.csv");

int N_steps [4]= {1,2,10,100};

for(int j=0; j<4;j++){

   int N= N_steps[j];
   stats.SetN(N_throws,N);

   string data_exp="data_exp.csv";
   string data_unif ="data_unif.csv";
   string data_cauchy = "data_cauchy.csv";

  ofstream out_exp(data_exp);
  ofstream out_unif(data_unif);
  ofstream out_cauchy(data_cauchy);


   for (int i=0; i<N*N_throws; i++){

         double r_exp=rnd.Exp(1);
         double r_unif= rnd.Rannyu();
         double r_cauchy = rnd.Cauchy(0,1);

         out_exp<<r_exp<<endl;
         out_unif<<r_unif<<endl;
         out_cauchy<<r_cauchy<<endl;
      }

      vector<double> SN_exp;
      vector <double> SN_unif;
      vector <double > SN_cauchy;

      stats.block_average(data_exp,SN_exp);
      stats.block_average(data_unif,SN_unif);
      stats.block_average(data_cauchy,SN_cauchy);


      for(int i=0; i<N_throws; i++){
         out<<N<<"\t"<<SN_exp[i]<<endl;
         out1<<N<<"\t"<<SN_unif[i]<<endl;
         out2<<N<<"\t"<<SN_cauchy[i]<<endl;
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


