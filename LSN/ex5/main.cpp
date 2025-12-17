#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "random.h"
#include "RandomWalk.h"

#include <armadillo>

using namespace std;
using namespace arma;

/*
 1s probability density (squared wavefunction)
 */
double H_1s(double a_0, double r) {
    return exp(-2 * r / (a_0));
}

/*
 2p probability density (squared wavefunction)

 */
double H_2p(double a_0, double r, double z) {
    double theta = acos(z / double(r));
    return pow((1. / 8.) * sqrt(2. / (M_PI * pow(a_0, 5))) *
               r * exp(-r / (2. * a_0)) * cos(theta), 2.);
}

/*
 * Metropolis acceptance probability

 */
double Metropolis_Acceptance(double p_new, double p_old,
                             double T_fwd, double T_bkw) {
    double q = (T_fwd * p_new) / (T_bkw * p_old);
    if (q >= 1.) return 1.;
    else return q;
}

/*
 * Perform one Metropolis step on a RandomWalk
 */
void Metropolis_Step(Random &rnd, RandomWalk &RW,
                     double &acc_rate, bool ground,
                     string prob_type) {

    // Store old position and distance
    vec old_pos = RW.Get_position();
    double r_old = RW.GetDistance();
    double a_0 = 1;

    // Propose new move
    if (prob_type == "gauss")
        RW.Step_gauss();
    else
        RW.Step_unif();

    double r_new = RW.GetDistance();

    // Compute probabilities
    double p_old, p_new;

    if (ground == true) {
        p_old = H_1s(a_0, r_old);
        p_new = H_1s(a_0, r_new);
    } else {
        p_old = H_2p(a_0, r_old, old_pos[2]);
        p_new = H_2p(a_0, r_new, RW.Get_position()[2]);
    }

    // Symmetric proposal probabilities
    double T_bkw = 1.;
    double T_fwd = 1.;

    // Metropolis acceptance
    double A = Metropolis_Acceptance(p_new, p_old, T_fwd, T_bkw);
    double x = rnd.Rannyu();

    // Accept or reject move
    if (x > A) {
        RW.SetPosition(old_pos);
    } else {
        acc_rate++;
    }
}

int main() {

	bool acceptance_analysis=false;
	bool save_positions=false;
	

	int Nblocks,Nsteps;
    if (save_positions){
		Nblocks = 1;
		Nsteps = 2000;
	}
	else{ //for energy measurements
    	Nblocks = 100;
    	Nsteps = 1000000;
	}



    string prob_type = "unif";

    string output_folder = "./OUTPUT/";
	vec step_length;
	ofstream outa,outa2;
	int nmax;
	
    if (acceptance_analysis) {
		step_length = {0.5, 1.5}; //starting values for acceptance analysis
		outa.open(output_folder + prob_type + "acceptance1s.csv");
    	outa << "step_length\tacceptance" << endl;

    	outa2.open(output_folder + prob_type + "acceptance2p.csv");
    	outa2 << "step_length\tacceptance" << endl;
		nmax=20;
	}
	else{
		nmax=1;
		if (prob_type=="unif") step_length={1.2,2.9}; // for uniform
        else step_length={0.85,1.75}; // for gauss
	}
    // acceptance trial values
    
    // Output files for acceptance rates


    // Loop over step length values

    for (int n = 0; n < nmax; n++) {

        Random rnd;
        rnd.RandomSetup();

		ofstream out,outp,outr1,outr2;
		if(acceptance_analysis==false){
			if(save_positions){
			out.open(output_folder + prob_type + "1s.csv");
			out << "x\ty\tz\tr" << endl;

			outp.open(output_folder + prob_type + "2p.csv");
			outp << "x\ty\tz\tr" << endl;
			}
			else{
			outr1.open(output_folder + prob_type + "_ave1s.csv");
			outr1 << "block\tave\tprog_ave\terr" << endl;

			outr2.open(output_folder + prob_type + "_ave2p.csv");
			outr2 << "block\tave\tprog_ave\terr" << endl;
			}
	}
        vec acc_rate = zeros(2);

        vec r_ave = zeros(2);
        vec r_ave2 = zeros(2);

        // Starting position at the origin
        vec start = zeros(3);
        for (int i = 0; i < 3; i++) {
            start[i] = 0.;
        }

        // Initialize random walks
        RandomWalk RW1s(rnd, start, step_length[0]);
        RandomWalk RW2p(rnd, start, step_length[1]);

        // Block averaging
        for (int j = 0; j < Nblocks; j++) {

            vec block_ave = zeros(2);

            for (int i = 0; i < Nsteps; i++) {

                // Metropolis steps
                Metropolis_Step(rnd, RW1s, acc_rate[0], 1, prob_type);
                Metropolis_Step(rnd, RW2p, acc_rate[1], 0, prob_type);

                if(save_positions && acceptance_analysis==false){
					for (int k = 0; k < 3; k++) {
						out << RW1s.Get_position()[k] << "\t";
						outp << RW2p.Get_position()[k] << "\t";
					}
				
					out << RW1s.GetDistance() << endl;
					outp << RW2p.GetDistance() << endl;
			}

                block_ave[0] += RW1s.GetDistance();
                block_ave[1] += RW2p.GetDistance();
            }

            cout << "Block " << j << "completed" << endl;

            vec err = zeros(2);
            for (int l = 0; l < 2; l++) {
                double ave = block_ave[l] / double(Nsteps);
                r_ave[l] += ave;
                r_ave2[l] += ave * ave;
                err[l] = sqrt((r_ave2[l] / double(j + 1)
                              - pow(r_ave[l] / double(j + 1), 2))
                              / double(j + 1));
            }
			if(save_positions==false && acceptance_analysis==false){
				outr1 << j << "\t" << block_ave[0]/double(Nsteps)
					<< "\t" << r_ave[0]/double(j+1)
					<< "\t" << err[0] << endl;

				outr2 << j << "\t" << block_ave[1]/double(Nsteps)
					<< "\t" << r_ave[1]/double(j+1)
					<< "\t" << err[1] << endl;
        }

        // Normalize acceptance rates
        acc_rate[0] /= Nsteps * Nblocks;
        acc_rate[1] /= Nsteps * Nblocks;

		if(acceptance_analysis){
        outa << step_length[0] << "\t" << acc_rate[0] << endl;
        outa2 << step_length[1] << "\t" << acc_rate[1] << endl;
		 step_length += 0.1;
		}
		

        // Increase step length
	} 

        cout << "Average distance 1s: " << r_ave[0] / double(Nblocks) << endl;
        cout << "Average distance 2p: " << r_ave[1] / double(Nblocks) << endl;
    }

    return 0;
}
