//ESERCIZIO 1.1.2
//RANDOM WALK

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"
#include "RandomWalk.h"

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

int main (int argc, char *argv[]) {
	// Define random generator



int N_steps=100; //number of steps in one RW
int N_RW =10000; //number of RWs
int N_blocks =100;
int N_el =N_RW/N_blocks;
double a=1.; //lenght of step


bool save_positions=false;
bool save_distance = true;
ofstream out_data,out1,out_dist,out1_dist;
if(save_positions){
out_data.open("./OUTPUT/RW_latt.csv");
out_data<<"walk_id\tstep\tx\ty\tz"<<endl;
out1.open("./OUTPUT/RW_cont.csv");
out1<<"walk_id\tstep\tx\ty\tz"<<endl;
}
if(save_distance){
out_dist.open("./OUTPUT/latt_distance.csv");
out_dist<<"step\tblock_ave\terr"<<endl;
out1_dist.open("./OUTPUT/cont_distance.csv");
out1_dist<<"step\tblock_ave\terr"<<endl;
}
vector <RandomWalk> lattice;
vector <RandomWalk> cont;
//sample points
for (int i =0; i<N_RW; i++){
	RandomWalk rw_l(i,a,0,0,0);
	lattice.push_back(rw_l);

	RandomWalk rw_c(i,a,0,0,0);
	cont.push_back(rw_c);
}

for (int i=0; i<N_steps; i++){	

statistics dist_lattice;

statistics dist_cont;

for (int j=0; j<N_blocks; j++){
dist_lattice.reset();
dist_cont.reset();
for (int k=0;k<N_el;k++){
	int rw_index =j*N_el+k;
	if(save_positions) {
		out_data<<rw_index<<"\t"<<i<<"\t"<<lattice[rw_index].Get_x()<<"\t"<<lattice[rw_index].Get_y()<<"\t"<<lattice[rw_index].Get_z()<<endl;
		out1<<rw_index<<"\t"<<i<<"\t"<<cont[rw_index].Get_x()<<"\t"<<cont[rw_index].Get_y()<<"\t"<<cont[rw_index].Get_z()<<endl;
	}
	lattice[rw_index].Step_Lattice();
	cont[rw_index].Step_3D();
	dist_lattice.ave+=lattice[rw_index].GetDistance();
	dist_cont.ave+=cont[rw_index].GetDistance();

}
dist_lattice.increment_block(N_el);
dist_lattice.compute_err(j+1);

dist_cont.increment_block(N_el);
dist_cont.compute_err(j+1);

	}
	if(save_distance){
out_dist<<i<<"\t"<<dist_lattice.block_ave/double(N_blocks)<<"\t"<<dist_lattice.err<<endl;
out1_dist<<i<<"\t"<<dist_cont.block_ave/double(N_blocks)<<"\t"<<dist_cont.err<<endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//UNIFORM RW

/*
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
*/
return 0;
}