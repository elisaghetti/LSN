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
		double get_x(){return position[0];};
		double get_y(){return position[1];};
	};

class chromosome { 

    private: 

    int _ngenes;
    vector <gene> _chromosome;
	//vec _position;
	int _simtype;
	double _cost; //total distance


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
	vector <gene> get_genevector(){return _chromosome;};
	void set_genevector(vector <gene> ch){_chromosome=ch;};
   void initialize(int n,int sim_type) {
        _ngenes=n;
		_simtype=sim_type;
		_cost=0.;
       _chromosome.resize(_ngenes+1);
		for (int i=0;i<_ngenes;i++){
			_chromosome[i].index = i;
		
		}
		_chromosome[_ngenes].index = 0;
		if (_simtype==0) cout<<"simulating "<<_ngenes<<" cities on a circle"<<endl;
	};
	void assign_positions(Random &rnd);
    void permutation(Random &rnd);
    void check_bonds();
	bool check_bonds1();
	//vec get_indices_vector();
	 double get_distance(int i1,int i2);
	 void compute_cost();
	 double  get_cost() {return _cost;};
	void print_configuration();
	 void shift_cities(Random &rnd);
	 void inversion(Random &rnd);
	 void block_permutation(Random &rnd);
	 void mutation (Random &rnd);
	void cut(int start);
	 void paste(vector <gene> block);
	 void crossover(int cut_pos,chromosome genitore2);

 };

#endif