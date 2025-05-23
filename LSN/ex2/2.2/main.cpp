//ESERCIZIO 1.1.2
//RANDOM WALK

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"
#include "RandomWalk.h"
#include "statistics.h"

using namespace std;


int main (int argc, char *argv[]) {
	// Define random generator



int N_steps=100; //number of steps in one RW
int N_RW =10000; //number of RWs
int N_blocks =100;
int N_el =N_RW/N_blocks;
double a=1.; //lenght of step

statistics stat;
stat.SetN(N_blocks,N_el);

ofstream out_data("RW_latt.csv");
ofstream out_dist("latt_distance.csv");


vector <RandomWalk> lattice;

for (int i =0; i<N_RW; i++){
	RandomWalk rw(i,a,0,0,0);
	lattice.push_back(rw);
}

for (int i=0; i<N_steps; i++){	

vector <double> distances(N_RW,0);
double mean ;
double err;

for (int j=0; j<N_RW; j++){


	out_data<<j<<"\t"<<lattice[j].Get_x()<<"\t"<<lattice[j].Get_y()<<"\t"<<lattice[j].Get_z()<<endl;

	lattice[j].Step_Lattice();
	double r_N = lattice[j].GetDistance();
	
	distances[j]=r_N;
	}

stat.block_average_err_total(distances,mean,err);

out_dist<<i<<"\t"<<mean<<"\t"<<err<<endl;

}

/////////////////////////////////////////////////////////////////////////////////
//UNIFORM RW


ofstream out1("RW_cont.csv");
ofstream out("distances.csv");


vector <RandomWalk> RW;

for (int i =0; i<N_RW; i++){
	RandomWalk rw(i,a,0,0,0);
	RW.push_back(rw);
}
RW[4].Get_seed(); 
for (int i=0; i<N_steps; i++){	

vector <double> distances(N_RW,0);
double mean ;
double err;

for (int j=0; j<N_RW; j++){


	out1<<j<<"\t"<<RW[j].Get_x()<<"\t"<<RW[j].Get_y()<<"\t"<<RW[j].Get_z()<<endl;

	RW[j].Step_3D();
	double r_N = RW[j].GetDistance();
	
	distances[j]=r_N;
	}

stat.block_average_err_total(distances,mean,err);

out<<i<<"\t"<<mean<<"\t"<<err<<endl;

}

return 0;
}