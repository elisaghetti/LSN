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
		

		//sampling
		int sampling_nsteps=10000;
		
	
		string sampling_file ="./OUTPUT/psi_sampling_"+to_string(init_par.mu)+"_"+to_string(init_par.sigma)+".csv";
		
		sample_psi(rnd,pos_sampler,init_par,sampling_nsteps,sampling_file);
	
	//EVALUATION OF <H>
		data_blocking H_blocks;
		H_blocks.Nblocks= 50;
		H_blocks.Nsteps= 100000;

		metro H_eval;

		string ave_file = "./OUTPUT/ave_"+to_string(init_par.mu)+"_"+to_string(init_par.sigma)+".csv";
		
		compute_mean_H(rnd,H_eval,H_blocks,init_par,ave_file);

return 0;
	}

	
//EXERCISE 8.2//////////////////////////////////////////////////////////////////////////////////////////
if (atof(argv[1])==2){
double beta_start =0.2; //starting temperature
double beta_max =50.;
cout<<"Input beta scaling law (linear or power) and scaling value"<<endl;
string scaling;
double scaling_val;
cin>>scaling>>scaling_val;
Random rnd;
rnd.RandomSetup(); 

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
	string filename="./OUTPUT/SAenergy_"+scaling+to_string(scaling_val)+".csv";
	ofstream out (filename);
	out<<"beta\tmeanH_ave\tstd_dev\tmeanH_best\tbest_err\tmeanH_last\tlast_err"<<endl;
	string pars_filename="./OUTPUT/SApars_"+scaling+to_string(scaling_val)+".csv";
	ofstream out1 (pars_filename);
	out1<<"beta\tmu\tsigma"<<endl;
cout<<"begin temp cycle"<<endl;

int Nsteps=1000;

while(beta_start<beta_max){
	temp_step++;

	
	vec results =annealing_step(rnd,Nsteps,H_eval,beta_start,old_par,H_blocks);

	out<<beta_start<<"\t"<<results[0]<<"\t"<<results[1]<<"\t"<<results[2]<<"\t"<<results[3]<<"\t"<<old_par.meanH<<"\t"<<H_blocks.err<<endl;
	out1<<beta_start<<"\t"<<old_par.mu<<"\t"<<old_par.sigma<<endl;
	cout<<"step "<<temp_step<<"beta: "<<beta_start<<" ave meanH: "<<results[0]<<" bets meanH"<<results[2]<<endl;

	if (scaling =="linear")beta_start+=scaling_val;
	else beta_start*=scaling_val;
}
	





cout<<"Final result: "<<endl;
cout<<"<H>: "<<old_par.meanH<<" error: "<<H_blocks.err<<endl;
cout<<"mu: "<<old_par.mu<<endl;
cout<<"sigma: "<<old_par.sigma<<endl;
old_par.set_norm();
string fin_file= "./OUTPUT/finalguess_ave_"+scaling+std::to_string(scaling_val)+".csv";

metro final_Heval;
data_blocking final_Hblocks;
final_Hblocks.Nblocks=50;
final_Hblocks.Nsteps=10000;

compute_mean_H(rnd,final_Heval,final_Hblocks,old_par,fin_file);

string sampling_file = "./OUTPUT/finalguess_sampling_"+scaling+to_string(scaling_val)+".csv";

metro pos_sampler;
sample_psi(rnd,pos_sampler,old_par,10000,sampling_file);


}
return 0;
}

