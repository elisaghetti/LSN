#ifndef __chromosome__
#define __chromosome__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <armadillo>
#include <stdlib.h> 
#include <random.h>
#include <vector>

using namespace std;
using namespace arma;

	struct gene {
		int index;
		vector<double> position;

		int get_index(){return index;};
		void set_index(int i){index=i;};
		vector <double> get_position (){return position;};
		void set_position (vector <double> pos) {position=pos;};
	};

class chromosome { 

    private: 

    int _ngenes;
    vector <gene> _chromosome;
	//vec _position;
	int _simtype;
	double _fitness;


    public:

		chromosome (){};
  // Destructor
        ~chromosome(){};
	
	vector <double> get_position(int i){
		return _chromosome[i].get_position();
	}

	void set_position(int i, vector <double> r){
		_chromosome[i].set_position(r);
	}
	gene get_gene(int i){
		return _chromosome[i];
	}
   void initialize(int n,int sim_type) {
        _ngenes=n;
		_simtype=sim_type;
		_fitness=0.;
       _chromosome.resize(_ngenes+1);
		for (int i=0;i<_ngenes;i++){
			_chromosome[i].index = i;
		
		}
		_chromosome[_ngenes].index = 0;
		if (_simtype==0) cout<<"simulating "<<_ngenes<<" cities on a circle"<<endl;
	};
	void assign_positions();
    void permutation(Random &rnd);
    void check_bonds();
	//vec get_indices_vector();
	 double get_distance(int i1,int i2);
	 void compute_fitness();
	 double  get_fitness() {return _fitness;};
	void print_configuration();
	 void shift_cities(Random &rnd);
	 void inversion(Random &rnd);
	 void block_permutation(Random &rnd);
	 void mutation (Random &rnd);

 };

#endif