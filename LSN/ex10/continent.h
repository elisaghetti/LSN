
#ifndef __continent__
#define __continent__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <vector>
#include "chromosome.h"
#include "GeneticOptimizer.h"
#include "mpi.h"
#include <random.h>
#include <algorithm>
#include <numeric>

using namespace std;

class continent {
    private: 
        int population_size;
        int _ngenes;
        GeneticOptimizer _gen;
        vector <chromosome> _best_path;
        Random _rnd;

    public:
        continent(){};
	    ~continent(){};

	void initialize(Random rnd,int ngenes, int population_size){
        _rnd = rnd;
		_Ngenes=ngenes;
		_population_size=size;
		_gen.initialize(2,_ngenes,_population_size);
        _gen.create_starting_population(_rnd);
        MPI dat
	};
}

