
#ifndef __parallel_GeneticOptimizer__
#define __parallel_GeneticOptimizer__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <vector>
#include "parallel_chromosome.h"
#include <random.h>
#include <algorithm>
#include <numeric>


using namespace std;

class parallel_GeneticOptimizer { 

private:
	int _population_size;
	int _Ngenes;
	int _simtype;
	vector <parallel_chromosome> _population;
	vector <double> _cost_values;


public:
	parallel_GeneticOptimizer(){};
	 ~parallel_GeneticOptimizer(){};

	void initialize(int sim_type,int ngenes, int size){
		_Ngenes=ngenes;
		_population_size=size;
		_simtype=sim_type;
	};
	int get_population_size(){return _population_size;};
	
	parallel_chromosome get_chromosome(int i){return _population[i];};
	void create_starting_population(Random &rnd);
	void print_configuration();
	void sort_population();
	void check_order();
	int selection (Random &rnd);
	void select_parents(Random &rnd);
	void send_population(int recv,int nmin,int nmax);
	void receive_population(int sender,int nmin,int nmax);
	void random_search(Random &rnd, int ngen);
	void crossover_g (Random &rnd,int p1,int p2);
	parallel_chromosome optimize (Random &rnd, int ngen);
};
#endif 
