
#ifndef __GeneticOptimizer__
#define __GeneticOptimizer__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <vector>
#include "chromosome.h"
#include <random.h>
#include <algorithm>
#include <numeric>


using namespace std;

class GeneticOptimizer { 

private:
	int _population_size;
	int _Ngenes;
	int _simtype;
	vector <chromosome> _population;
	vector <double> _cost_values;


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

	void random_search(Random &rnd, int ngen);
	void crossover_g (Random &rnd,int p1,int p2);
	chromosome optimize (Random &rnd, int ngen);
};
#endif 
