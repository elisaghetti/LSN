
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
	int _simtype;
	field <chromosome> _population;


public:
	GeneticOptimizer(){};
	 ~GeneticOptimizer(){};
	void initialize(int sim_type,int ngenes, int size){
		_Ngenes=ngenes;
		_population_size=size;
		_simtype=sim_type;
		_population.set_size(_population_size);
		
	};
	
	void create_starting_population(Random &rnd);
	void print_configuration();
	void sort_population();
	void check_order();

};
#endif 
