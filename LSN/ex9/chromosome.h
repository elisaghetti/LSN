#ifndef __chromosome__
#define __chromosome__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <armadillo>
#include <stdlib.h> 
#include <random.h>

using namespace std;
using namespace arma;

	struct gene {
		int index;
		vec position=zeros(2);
	};

class chromosome { 

    private: 

    int _ngenes;
    field <gene> _chromosome;
	//vec _position;
	int _simtype;
	double _fitness;


    public:

		chromosome (){};
  // Destructor
        ~chromosome(){};
	
	vec get_position(int i){
		return _chromosome(i).position;
	}

	void set_position(int i, vec r){
		_chromosome(i).position=r;
	}
	gene get_gene(int i){
		return _chromosome(i);
	}
   void initialize(int n,int sim_type) {
        _ngenes=n;
		_simtype=sim_type;
		_fitness=0.;
        _chromosome.set_size(_ngenes+1);
		for (int i=0;i<_ngenes;i++){
			_chromosome(i).index = i;
		
		}
		_chromosome(_ngenes).index = 0;
		if (_simtype==0) cout<<"simulating "<<_ngenes<<" cities on a circle"<<endl;
	};
	void assign_positions();
	int get_index(int i){ return _chromosome(i).index;}

	

	void set_element(int index,gene val);

    void permutation(Random &rnd);
    void check_bonds();
	
	 double get_distance(int i1,int i2);
	 void compute_fitness();
	 double get_fitness(){return _fitness;};

 };
#endif