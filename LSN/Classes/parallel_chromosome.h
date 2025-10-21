#ifndef __parallel_chromosome__
#define __parallel_chromosome__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <random.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include "mpi.h"

using namespace std;
/*
	struct parallel_gene {
		int index;
		vector<double> position;

		int get_index(){return index;};
		void set_index(int i){index=i;};
		vector <double> get_position (){return position;};
		void set_position (vector <double> pos) {position=pos;};
		double get_x(){return position[0];};
		double get_y(){return position[1];};
	};
*/
struct gene {
    int index;
    double x;
    double y;
};

class parallel_chromosome { 

    private: 

    int _ngenes;

    vector <gene> _chromosome;
	//vec _position;
	int _simtype;
	double _cost; //total distance
	MPI_Datatype MPI_gene;

    public:

		parallel_chromosome (){};
  // Destructor
        ~parallel_chromosome(){};
	

   void initialize(int n,int sim_type) {
        _ngenes=n;
		_simtype=sim_type;
		_cost=0.;
	
       _chromosome.resize(_ngenes+1);
		for (int i=0;i<_ngenes;i++){
			_chromosome[i].index = i;
		
		}
		_chromosome[_ngenes].index = 0;
		     const int nitems=3;
    int blocklengths[3] = {1,1,1};
    MPI_Datatype types[3] = {MPI_INT, MPI_DOUBLE, MPI_DOUBLE};
    MPI_Aint offsets[3];

    offsets[0] = offsetof(gene, index);
    offsets[1] = offsetof(gene, x);
    offsets[2] = offsetof(gene,y);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &MPI_gene);
    MPI_Type_commit(&MPI_gene);
	};
	   void initialize(int sim_type) {
		_simtype=sim_type;
		_cost=0.;
 MPI_Datatype types[3] = {MPI_INT, MPI_DOUBLE, MPI_DOUBLE};
    MPI_Aint offsets[3];

    offsets[0] = offsetof(gene, index);
    offsets[1] = offsetof(gene, x);
    offsets[2] = offsetof(gene,y);
int blocklengths[3] = {1,1,1};
    MPI_Type_create_struct(3, blocklengths, offsets, types, &MPI_gene);
    MPI_Type_commit(&MPI_gene);
	};
	int get_ngenes(){return _ngenes;};
	void set_ngenes(int n){_ngenes=n;};
	
	void set_cost(double cost){_cost=cost;};
	vector <double> get_position(int i);

	void set_position(int i, vector <double> r);
	gene get_gene(int i);

	
	vector <gene> get_genevector(){return _chromosome;};
	void set_genevector(vector <gene> ch){_chromosome=ch;};
	void assign_positions(Random &rnd);
    void permutation(Random &rnd);
    void check_bonds();
	bool check_bonds1();
	void send(int recv);
	void receive(int sender);
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
	 void crossover(int cut_pos,parallel_chromosome genitore2);

 };

#endif