#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"
#include "statistics.h"

using namespace std;

double integrand(double x){
	return (M_PI*0.5)*cos(M_PI*x*0.5);
}

double imp_sampling (double x) {
	return integrand(x)/(double(2*x));
}




int main() {

// Define random generator
Random rnd;
rnd.RandomSetup();


int N=10000; // numero di punti generati
int N_blocks= 100; 
int n= N/N_blocks; // num elementi in ogni blocco

statistics stat;
stat.SetN(N_blocks,n);

//1.1 Calcolo integrale con metodo della media


//generate data

string data = "data.csv";
ofstream out(data);
for (int i=0; i<N;i++){
	double r =rnd.Rannyu();
	double f=integrand(r);
	out<<f<<endl;
}

out.close();

string output="integral.csv";
ofstream out1(output);

out1<<"TYPE"<<"\t"<<"VALUE"<<"\t"<<"ERROR"<<endl;

string type = "MM";
stat.block_average_err(data,output,type);

string dataIS = "dataIS.csv";

ofstream out2(dataIS);
for (int i=0; i<N;i++){
	double r =rnd.Cosine();
	double f=imp_sampling(r);
	out2<<f<<endl;
}

out2.close();


string type1 ="IS";
stat.block_average_err(dataIS,output,type1);




/*

vector <double> block_ave(N_blocks,0);
vector <double> block_ave_squared(N_blocks,0);

ofstream out;
out.open("integral.csv");
//out1.open("errors.txt");
for(int i=0; i<N_blocks; i++){
	double sum=0;
	for (int j=0; j<n; j++) {
		double x= rnd.Rannyu();	
		double f= integrand(x);
		sum+= f;
	}


	block_ave[i]= sum/double(n);
	block_ave_squared[i]=block_ave[i]*block_ave[i];


}

double I= 0;
double ave2=0;
vector <double> errors(N_blocks,0);

for(int i=0; i<N_blocks; i++){
	I+=block_ave[i];
	ave2 += block_ave_squared[i];
	double err = error(I/double(i+1),ave2/double(i+1),i+1);
	out<<I/(i+1)<<"\t"<<err<<endl;
	//out1<<err<<endl;
	
}
cout<<"Integral: "<<I/double(N_blocks)<<endl;

// calcolo integrale con importance sampling: p(x)=2x

vector <double> block_ave_IS(N_blocks,0);
vector <double> block_ave_squared_IS(N_blocks,0);

ofstream out1;
out1.open("integralIS.csv");

for(int i=0; i<N_blocks; i++){
	double sum=0;
	for (int j=0; j<n; j++) {
		double x= rnd.Cosine();	
		double f= imp_sampling(x);
		sum+= f;
	}


	block_ave_IS[i]= sum/double(n);
	block_ave_squared_IS[i]=block_ave_IS[i]*block_ave_IS[i];

	
}

double I_IS= 0;
double ave2_IS=0;
vector <double> errors_IS(N_blocks,0);

for(int i=0; i<N_blocks; i++){
	I_IS+=block_ave_IS[i];
	ave2_IS += block_ave_squared_IS[i];
	double err_IS = error(I_IS/double(i+1),ave2_IS/double(i+1),i+1);
	out1<<I_IS/(i+1)<<"\t"<<err_IS<<endl;
	//out1<<err<<endl;
	
}
cout<<"Integral with IS: "<<I_IS/double(N_blocks)<<endl;
*/
return 0;
}
