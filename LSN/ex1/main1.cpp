#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"

using namespace std;

/*
 Struct to perform block averaging with error estimation
 */
struct statistics {
    double ave = 0.0;        // average of current block
    double ave2 = 0.0;       // square of the average
    double block_ave = 0.0;  // cumulative average over blocks
    double block_ave2 = 0.0; // cumulative square average over blocks
    double err = 0.0;        // statistical error

    // Reset quantities for a new block
    void reset() {
        ave = 0.0;
        ave2 = 0.0;
        err = 0.0;
    }

    // Compute statistical error using progressive averages
    void compute_err(int n) {
        if (n == 1)
            err = 0.0;
        else
            err = sqrt((block_ave2 / n - pow(block_ave / n, 2)) / double(n - 1));
    }

    // Normalize block average and update cumulative quantities
    void increment_block(int N) {
        ave /= N;
        ave2 = ave * ave;
        block_ave += ave;
        block_ave2 += ave2;
    }
};

int main(int argc, char *argv[]) {

    // Check input arguments
    if (argc != 3) {
        cerr << "Please input number of blocks N and number of throws M per block" << endl;
        return 1;
    }

    int nblocks = atoi(argv[1]);  // number of blocks
    int nthrows = atoi(argv[2]);  // number of throws per block

    statistics stat_int;  // statistics for integral (mean)
    statistics stat_var;  // statistics for variance

    Random rnd;
    rnd.RandomSetup();

    // Output files
    ofstream out("./OUTPUT/integral.csv");
    out << "block\tave\tblock_ave\terr" << endl;

    ofstream outv("./OUTPUT/variance.csv");
    outv << "block\tave\tblock_ave\terr" << endl;

    // Block averaging loop
    for (int i = 0; i < nblocks; i++) {

        stat_int.reset();
        stat_var.reset();

        // Monte Carlo sampling
        for (int j = 0; j < nthrows; j++) {
            double r = rnd.Rannyu();
            stat_int.ave += r;
            stat_var.ave += pow(r - 0.5, 2);
        }

        // Update block statistics and compute error
        stat_int.increment_block(nthrows);
        stat_int.compute_err(i + 1);

        stat_var.increment_block(nthrows);
        stat_var.compute_err(i + 1);

        // Write results
        out  << i << "\t"
             << stat_int.ave << "\t"
             << stat_int.block_ave / (i + 1) << "\t"
             << stat_int.err << endl;

        outv << i << "\t"
             << stat_var.ave << "\t"
             << stat_var.block_ave / (i + 1) << "\t"
             << stat_var.err << endl;
    }

    // Chi-square test
    ofstream outc("./OUTPUT/Chi.csv");
    outc << "j\tchi_j" << endl;

    int N = 100;    // number of intervals
    int M = 10000;  // number of random numbers per test

    for (int j = 0; j < N; j++) {
        double chi_j = 0.0;

        // Count numbers in each interval
        for (int i = 0; i < N; i++) {//j=1...100 generations of chi
            double n_i = 0.0;

            for (int k = 0; k < M; k++) {//intervals of [0,1)
                double r = rnd.Rannyu();
                if (r * N >= i && r * N < i + 1)
                    n_i++;
            }

            // Chi-square contribution
            chi_j += pow(n_i - double(M) / N, 2) / (double(M) / N);
        }

        outc << j << "\t" << chi_j << endl;
    }

    outc.close();
    return 0;
}
