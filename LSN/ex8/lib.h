#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <armadillo>
#include <random.h>

using namespace std;
using namespace arma;

struct SApar {
    double meanH=0.;
    double mu;
    double sigma;
    double norm;
    void set_norm (){ 
        norm =2.*sigma*sqrt(M_PI)*(1+exp(-mu*mu/(sigma*sigma)));
    }

};
struct metro { //metropolis algorithm parameters

	double step_length=2.75;
	double acc_rate=0.;
	double position=0.;

    void reset (){
        position =0.;
        acc_rate=0.;
    }
};

struct data_blocking {
    int Nblocks;
    int Nsteps;
    double ave;
    double block_ave=0.;
    double block_ave2=0.;
    double err=0.;
    void reset (){
        ave =0.;
        block_ave=0.;
        block_ave2=0.;
        err=0.;
    }
        void increment(int j){
        block_ave+= ave;
        block_ave2 += ave*ave;
        err = sqrt((block_ave2/double(j+1)-pow(block_ave/double(j+1),2))/double(j+1));

    }
};



//metropolis methods
double Metropolis_Acceptance(double p_new,double p_old,double T_fwd, double T_bkw);
void Metropolis_Step(Random &rnd,metro &eval, SApar par);
void Equilibration(Random &rnd,metro &eval, SApar &par,int eq_steps);
void Equilibration(Random &rnd,metro &eval, SApar &par,int eq_steps,string file);

void compute_mean_H(Random &rnd, metro &H_eval, data_blocking &H_blocks, SApar par);
void compute_mean_H(Random &rnd, metro &H_eval, data_blocking &H_blocks, SApar &par,string filename);

void sample_psi(Random &rnd, metro &pos_sampler,SApar par,int Nsteps,string file);
vec annealing_step (Random &rnd,int Nsteps,metro&H_eval,double beta,SApar &old_par, data_blocking &ann_blocks);