#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <armadillo>
#include <random.h>
#include "lib.h"

using namespace std;
using namespace arma;


int main(int argc, char **argv){

	
	if (argc != 2 or atof(argv[1])>2) cerr <<"input from command line: 1 fpr 8.1, 2 for 8.2"<<endl;
//EXERCISE 8.1////////////////////////////////////////////////////////////////////////
	if (atof(argv[1])==1) {
		cout<<"Input initial guess for mu and sigma parameters: "<<endl;
		SApar init_par;
		cin>>init_par.mu>>init_par.sigma;
		init_par.set_norm();
		Random rnd;
		rnd.RandomSetup();

		//acceptance study during equilibration
		metro trial;
	
		metro pos_sampler;
			/*
		string eq_file = "./OUTPUT/acceptance.csv";
		Equilibration(rnd,trial,init_par,2000,eq_file);
		*/

		//sampling
		int sampling_nsteps=10000;
		
	
		string sampling_file ="./OUTPUT/psi_sampling_prova.csv";
		
		sample_psi(rnd,pos_sampler,init_par,sampling_nsteps,sampling_file);
	
	//EVALUATION OF <H>
		data_blocking H_blocks;
		H_blocks.Nblocks= 50;
		H_blocks.Nsteps= 100000;

		metro H_eval;

		string ave_file = "./OUTPUT/ave_prova.csv";
		
		compute_mean_H(rnd,H_eval,H_blocks,init_par,ave_file);

return 0;
	}

	
//EXERCISE 8.2//////////////////////////////////////////////////////////////////////////////////////////
if (atof(argv[1])==2){
double beta_start =0.2; //starting temperature
double beta_max =50.;

Random rnd;
rnd.RandomSetup(); 



//int temp_steps =50;
int temp_step =0.;

SApar old_par;
old_par.mu =1.;
old_par.sigma=1.;
old_par.set_norm();

metro H_eval;

	data_blocking H_blocks; //data blocking struct for H evaluation, members are resetted every time <H> is computed
	H_blocks.Nblocks = 20;
	H_blocks.Nsteps = 5000;

compute_mean_H(rnd,H_eval,H_blocks,old_par);
old_par.meanH=H_blocks.block_ave/double(H_blocks.Nblocks);

	ofstream out ("./OUTPUT/SAenergy_lin.csv");
	out<<"beta\tmeanH_ave\tstd_dev\tmeanH_best\tbest_err\tmeanH_last\tlast_err"<<endl;

	ofstream out1 ("./OUTPUT/SApars_lin.csv");
	out1<<"beta\tmu\tsigma"<<endl;
cout<<"begin temp cycle"<<endl;

int Nsteps=1000;
//for(int i=0;i<temp_steps;i++) {//H evaluation blocks
while(beta_start<beta_max){
	temp_step++;
	//SA_blocks.Nblocks*=(beta_start
	
	vec results =annealing_step(rnd,Nsteps,H_eval,beta_start,old_par,H_blocks);
	//SA_blocks.increment(SA_blocks.Nblocks-1);
	
	//cout<<SA_blocks.Nblocks<<" "<<" "<<SA_blocks.block_ave/SA_blocks.Nblocks<<" "<<SA_blocks.err<<endl;
	out<<beta_start<<"\t"<<results[0]<<"\t"<<results[1]<<"\t"<<results[2]<<"\t"<<results[3]<<"\t"<<old_par.meanH<<"\t"<<H_blocks.err<<endl;
	out1<<beta_start<<"\t"<<old_par.mu<<"\t"<<old_par.sigma<<endl;
	cout<<"step "<<temp_step<<"beta: "<<beta_start<<" ave meanH: "<<results[0]<<" bets meanH"<<results[2]<<endl;

	beta_start+=0.8;
}
	




//SApar fin_par = simulated_annealing(beta_start,temp_steps,Nsteps,Nblocks,rnd);

cout<<"Final result: "<<endl;
cout<<"<H>: "<<old_par.meanH<<" error: "<<H_blocks.err<<endl;
cout<<"mu: "<<old_par.mu<<endl;
cout<<"sigma: "<<old_par.sigma<<endl;
old_par.set_norm();
string file= "./OUTPUT/final_guess_ave_lin.csv";

metro final_Heval;
data_blocking final_Hblocks;
final_Hblocks.Nblocks=50;
final_Hblocks.Nsteps=10000;

compute_mean_H(rnd,final_Heval,final_Hblocks,old_par,file);

string sampling_file = "./OUTPUT/final_sampling_lin.csv";

metro pos_sampler;
sample_psi(rnd,pos_sampler,old_par,10000,sampling_file);


}
return 0;
}

