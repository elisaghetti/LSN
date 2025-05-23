#include <cmath>
#include <cstdlib>
#include <string>
#include <armadillo>
#include "GeneticOptimizer.h"

using namespace std;
using namespace arma;

void GeneticOptimizer::Initialize(){
ifstream input("../INPUT/input.dat"); // Start reading ../INPUT/input.dat : variabili che servono x inizializzare la simulazione
string property;

  while ( !input.eof() ){
    input >> property;
    if( property == "POPULATION SIZE" ) {
    	input>>_PopulationSize;
    	_Population.set_size(_PopulationSize);
    }
    else if (property== "N CITIES"){
    	input>> _Ngenes;
    	for (int i =0; i<_PopulationSize; i++){
    		_Population(i).size(_Ngenes);
    	}
    }

    }

}