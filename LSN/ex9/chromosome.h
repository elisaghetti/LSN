#ifndef __Chromosome__
#define __Chromosome__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <armadillo>
#include <stdlib.h> 

using namespace std;
using namespace arma;

class Chromosome { 

private:
	int _Ngenes;
	int _Nalleles;
	vec _chromosome;


public:
	void size(int N) {
		_Ngenes=N; 
		_chromosome.set_size(_Ngenes);
	}


};

#endif