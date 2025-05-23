#ifndef __GeneticOptimizer__
#define __GeneticOptimizer__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <armadillo>
#include <stdlib.h> 
#include "chromosome.h"


using namespace std;
using namespace arma;

class GeneticOptimizer { 

private:
	int _Ngenes;
	int _PopulationSize;

	field <Chromosome> _Population;


public:
	void Initialize();
};
#endif