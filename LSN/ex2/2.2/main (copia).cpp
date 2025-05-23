//ESERCIZIO 1.1.2
//RANDOM WALK

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"

using namespace std;


int main () {
	// Define random generator
Random rnd;

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


int N_steps=100; //number of steps in one RW
int N_RW =10000; //number of RWs
int N_blocks =100;
int N_el =N_RW/N_blocks;
double a=1.; //lenght of step


ofstream out5,out6;
out5.open("RandomWalk.csv");
out6.open("Distance.csv");


vector <double> ave (N_RW,0);

	vector <double> pos_x (N_RW,0);
	vector <double> pos_y (N_RW,0);
	vector <double> pos_z (N_RW,0);
for (int i=0; i<N_steps; i++){ //creo 3 vettori in cui ogni elemento contiene la coordinata per ognuno dei RW 
vector <double> block_ave(N_blocks,0);
for (int k=0; k<N_blocks;k++){
	double sum =0; //somma delle distanze percorse dai RW di 1 blocco allo step i

	for (int j=0; j<N_el;j++) { //valore di r per ogni RW allo step i fissato
		int RW_id = k*N_el +j;
		out5<<i<<"\t"<<RW_id<<"\t"<<pos_x[RW_id]<<"\t"<<pos_y[RW_id]<<"\t"<<pos_z[RW_id]<<endl;

		bool direction = true;
	 //numero di passi
	double r1=rnd.Rannyu();

	if (r1 <=0.5) direction = false;

	double r2=rnd.Rannyu();
	

	if(r2<= 1./3. ) {
		if (direction==true) pos_x[RW_id] += a;
		else pos_x[RW_id] += -a;
	}
	if(1./3. < r2 && r2<= 2./3.) {
				if (direction==true) pos_y[RW_id] += a;
				else pos_y[RW_id] += -a;
	}

	if(2./3. <=r2) {
				if (direction==true) pos_z[RW_id] += a;
				else pos_z[RW_id] += -a;
	}

	double x=pos_x[RW_id];
	double y=pos_y[RW_id];
	double z =pos_z[RW_id];

		sum += x*x +y*y+z*z; 
	}

	block_ave[k] = sum/double(N_el); //media delle distanze di 1 blocco 
	//out1<<k<<"\t"<<block_ave[k]<<endl;
	//r_N_mean[i] += block_ave[k]/double(k+1); //media cumulativa dei blocchi
}
//dist+=r_N_mean[i];
//out1<<i<<"\t"<<sqrt(dist)<<endl;
}

/*

for (int j=0; j<N_RW; j++){ 
	double r_N_squared=0;
	vector <double> position(3,0);
for (int i=0; i<N_steps; i++){ 
	out5<<j<<"\t"<<position[0]<<"\t"<<position[1]<<"\t"<<position[2]<<endl;
	bool direction = true;
	 //numero di passi
	double r1=rnd.Rannyu();

	if (r1 <=0.5) direction = false;

	double r2=rnd.Rannyu();
	

	if(r2<= 1./3. ) {
		if (direction==true) position[0] += a;
		else position[0] += -a;
	}
	if(1./3. < r2 && r2<= 2./3.) {
				if (direction==true) position[1] += a;
				else position[1] += -a;
	}

	if(2./3. <=r2) {
				if (direction==true) position[2] += a;
				else position[2] += -a;
	}

	
	r_N_squared += (pow(position[0],2)+pow(position[1],2)+pow(position[2],2));
	
	}

ave[j]= sqrt(r_N_squared/(j*100.));
out6<<ave[j]<<endl;
}


//continuum random walk

ofstream out("RW_continuum.csv");
ofstream out1("distance.csv");

	vector <double> pos_x (N_RW,0);
	vector <double> pos_y (N_RW,0);
	vector <double> pos_z (N_RW,0);

 vector <double> r_N_mean(N_steps,0); 
 double dist =0;
 //vettore delgli RN ad ogni passo i	
for (int i=0; i<N_steps; i++){ //creo 3 vettori in cui ogni elemento contiene la coordinata per ognuno dei RW 
vector <double> block_ave(N_blocks,0);
for (int k=0; k<N_blocks;k++){
	double sum =0; //somma delle distanze percorse dai RW di 1 blocco allo step i

	for (int j=0; j<N_el;j++) { //valore di r per ogni RW allo step i fissato
		int RW_id = k*N_el +j;
		out<<i<<"\t"<<RW_id<<"\t"<<pos_x[RW_id]<<"\t"<<pos_y[RW_id]<<"\t"<<pos_z[RW_id]<<endl;
		double theta=rnd.Rannyu(0,M_PI);
		double phi = rnd.Rannyu(0,2*M_PI);

		double x= a*sin(theta)*cos(phi);
		double y=a*sin(theta)*sin(phi);
		double z= a*cos(theta);

		pos_x[RW_id] += x;
		pos_y[RW_id] += y;
		pos_z[RW_id] += z;

		sum += x*x +y*y+z*z; 
	}

	block_ave[k] = sum/double(N_el); //media delle distanze di 1 blocco 
	//out1<<k<<"\t"<<block_ave[k]<<endl;
	r_N_mean[i] += block_ave[k]/double(k+1); //media cumulativa dei blocchi
}
dist+=r_N_mean[i];
out1<<i<<"\t"<<sqrt(dist)<<endl;
}


/*
	vector <double> r_N(N_RW,0);
for (int i=0; i<N_steps; i++){ //creo 3 vettori in cui ogni elemento contiene la coordinata per ognuno dei RW 
 //vettore delle distanze percorse da ogni RW allo step i
for (int j=0; j<N_RW;j++){
	out<<i<<"\t"<<j<<"\t"<<pos_x[j]<<"\t"<<pos_y[j]<<"\t"<<pos_z[j]<<"\t"<<r_N[j]<<endl;
	double theta=rnd.Rannyu(0,M_PI);
	double phi = rnd.Rannyu(0,2*M_PI);

	double x= a*sin(theta)*cos(phi);
	double y=a*sin(theta)*sin(phi);
	double z= a*cos(theta);

	pos_x[j] += x;
	pos_y[j] += y;
	pos_z[j] += z;

	r_N [j] += x*x +y*y+z*z;
}

}
*/
//calcolo distanza percorsa nel singolo RW -> faccio la media delle distanze percorse in un blocco di 100 RW
/*
for (int j=0; j<N_RW;j++){
	vector <double> pos_cont (3,0);
	double r2=0;
for (int i=0; i<N_steps; i++){

	out<<j<<"\t"<<pos_cont[0]<<"\t"<<pos_cont[1]<<"\t"<<pos_cont[2]<<endl;
	double theta=rnd.Rannyu(0,M_PI);
	double phi = rnd.Rannyu(0,2*M_PI);

	double x= a*sin(theta)*cos(phi);
	double y=a*sin(theta)*sin(phi);
	double z= a*cos(theta);

	pos_cont[0]+=x;
	pos_cont[1]+= y;
	pos_cont[2]+=z;

	r2 += x*x + y*y + z*z;
}

}
*/




return 0;
}