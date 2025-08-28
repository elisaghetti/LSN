
#ifndef __GeneticOptimizer__
#define __GeneticOptimizer__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <armadillo>
#include <stdlib.h> 
#include <vector>
#include "chromosome.h"
#include <random.h>


using namespace std;
using namespace arma;

class GeneticOptimizer { 

private:
	int _population_size;
	int _Ngenes;
	//mat _population;
	field <chromosome> _population;



public:
	GeneticOptimizer(){};
	 ~GeneticOptimizer(){};
	void initialize(int ngenes, int size){
		_Ngenes=ngenes;
		_population_size=size;

		_population = zeros(_population_size);
	};

	//void create_starting_population(Random &rnd,int sim_type);
};
#endif 
