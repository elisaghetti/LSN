
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
	vector <chromosome> _population;
	vector <double> _fitness_values;


public:
	GeneticOptimizer(){};
	 ~GeneticOptimizer(){};
	void initialize(int sim_type,int ngenes, int size){
		_Ngenes=ngenes;
		_population_size=size;
		_simtype=sim_type;

	
		
	};
	
	void create_starting_population(Random &rnd);
	void print_configuration();
	void sort_population();
	void check_order();
	int selection (Random &rnd);
	void select_parents(Random &rnd);


};
#endif 
