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
    double meanH;
    double mu;
    double sigma;
};
struct metro { //metropolis algorithm parameters
	Random rand;
	double step_length;
	double acc_rate=0.;
	double position=0.;
};

struct p_distr{
    int Ndim =1;
    int Nparams =0;
    vec par =zeros(Nparams);
    vec pos = zeros(Ndim);
    double val =0.;
};

//probability distributions
double psi_T(double mu,double sigma,double x);
double dpsi2 (double mu, double sigma, double x);
double pot(double x);
double Hpsi (double mu, double sigma, double x);

//metropolis methods
double Metropolis_Acceptance(double p_new,double p_old,double T_fwd, double T_bkw);

void Metropolis_Step(Random& rnd, double &position,double step_length,double &acc_rate, double mu, double sigma);
//void Metropolis_Step(metro &eval, double mu, double sigma);
void Equilibration(metro eval, double mu, double sigma,int eq_steps);
void compute_mean_H(Random &rnd, int Nsteps, SApar &par);
void simulated_annealing(double beta_start,int ann_steps,int Nsteps,int Nblocks,Random &rnd);
