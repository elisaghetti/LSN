#ifndef __continent__
#define __continent__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <vector>
#include "parallel_chromosome.h"
#include "parallel_GeneticOptimizer.h"
#include "mpi.h"
#include <random.h>
#include <algorithm>
#include <numeric>

using namespace std;

class continent {
    private: 
        int _population_size;
        int _ngenes;
        parallel_GeneticOptimizer _gen;
        parallel_chromosome _best_path;
        Random _rnd;
        int _rank;

    public:
        continent(){};
	    ~continent(){};

	void initialize(int ngenes, int population_size,int rank){
        
		_ngenes=ngenes;
		_population_size=population_size;
        _rank=rank;
        _rnd.RandomSetup(_rank);
		_gen.initialize(2,_ngenes,_population_size);
        _gen.create_starting_population(_rnd);

	};

    void optimize(int ngen);
    parallel_chromosome get_best();
    void migration(int receiver);
};

#endif

