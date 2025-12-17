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

ofstream out("./OUTPUT/SN_Exponential.csv");
out<<"N\treal_index\tSN"<<endl;
ofstream out1("./OUTPUT/SN_Uniform.csv");
out1<<"N\treal_index\tSN"<<endl;
ofstream out2("./OUTPUT/SN_Cauchy-Lorentz.csv");
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


