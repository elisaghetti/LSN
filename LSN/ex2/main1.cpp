#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"

using namespace std;

double integrand(double x){
	return (M_PI*0.5)*cos(M_PI*x*0.5);
}

double ar_d(double x){
   return (3./2.)*(1-x*x);
}

double inv_imp_sampling(double x){
   double a = 1.0 + M_PI/4.0;
    double b = M_PI/2.0;
    return (a - sqrt(a*a - 2.0*b*x)) / b;
}
double inv_d(double x){
   return 1-M_PI*0.5*(x-0.5);
}
double ar_imp_sampling (Random &rnd) {
   double pmax= ar_d(0.);
 
	double r1,r2;
   do{
   r1=rnd.Rannyu();
    r2= rnd.Rannyu();
   } while(r2>ar_d(r1)/pmax);
   return r1;

}



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


int main() {

// Define random generator
Random rnd;
rnd.RandomSetup();



int N_blocks= 100; 
int N_steps=10000; // num elementi in ogni blocco


//1.1 Calcolo integrale con metodo della media


//generate data


ofstream out("./OUTPUT/integral_uniform.csv");
out<<"block\tave\tblock_ave\terr"<<endl;

ofstream outis("./OUTPUT/integral_IS_ar.csv");
outis<<"block\tave\tblock_ave\terr"<<endl;

ofstream outis1("./OUTPUT/integral_IS_inv.csv");
outis1<<"block\tave\tblock_ave\terr"<<endl;
statistics unif_integral;
statistics is_integral;
statistics is_inv_integral;
for (int j=0;j<N_blocks;j++){
	unif_integral.reset();
	for (int i=0; i<N_steps;i++){
		//uniform
		double r =rnd.Rannyu();
		double f=integrand(r);
		unif_integral.ave+=f;
		//importance sampling
		double r_is_ar = ar_imp_sampling(rnd);
		double f_is= integrand(r_is_ar)/ar_d(r_is_ar);
		is_integral.ave += f_is;

      double r_is_inv = inv_imp_sampling(r);
		double f_is_inv= integrand(r_is_inv)/inv_d(r_is_inv);
		is_inv_integral.ave += f_is_inv;


}
	unif_integral.increment_block(N_steps);
	unif_integral.compute_err(j+1);
	out<<j<<"\t"<<unif_integral.ave<<"\t"<<unif_integral.block_ave/double(j+1)<<"\t"<<unif_integral.err<<endl;

	is_integral.increment_block(N_steps);
	is_integral.compute_err(j+1);
	outis<<j<<"\t"<<is_integral.ave<<"\t"<<is_integral.block_ave/double(j+1)<<"\t"<<is_integral.err<<endl;

   is_inv_integral.increment_block(N_steps);
	is_inv_integral.compute_err(j+1);
	outis1<<j<<"\t"<<is_inv_integral.ave<<"\t"<<is_inv_integral.block_ave/double(j+1)<<"\t"<<is_inv_integral.err<<endl;
}
out.close();
outis.close();

return 0;
}
