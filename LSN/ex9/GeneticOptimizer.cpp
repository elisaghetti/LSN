#include <cmath>
#include <cstdlib>
#include <string>
#include <armadillo>
#include "GeneticOptimizer.h"
#include "chromosome.h"

using namespace std;
using namespace arma;



void GeneticOptimizer::create_starting_population(Random &rnd){
  chromosome ch;

		ch.initialize(_Ngenes,_simtype);
		ch.assign_positions();
		for (int i=0; i<_population_size;i++){
		int n_perm = int(rnd.Rannyu(0,_Ngenes+1));//number of permutations
		
		chromosome new_ch = ch;
		for(int j=0;j<n_perm;j++) new_ch.permutation(rnd);
		_population(i)=new_ch;
		new_ch.check_bonds();
	}


	}

	void GeneticOptimizer::print_configuration(){
		ofstream out("./OUTPUT/positions.csv");
	out<<"ch_index\tindex\tx\ty"<<endl;
	for (int i=0; i<_population_size;i++){
		for (int j=0; j<_Ngenes+1;j++){
			out<<i<<"\t"<<_population(i).get_gene(j).index<<"\t"<<_population(i).get_gene(j).position[0]<<"\t"<<_population(i).get_gene(j).position[1]<<endl;
		}

	}
	out.close();
}

void GeneticOptimizer::sort_population(){
	vec fitness_values = zeros(_population_size);
	for (int i=0;i<_population_size;i++){
		_population(i).compute_fitness();
		fitness_values[i]= _population(i).get_fitness();
	}

	uvec sorted_indices = sort_index(fitness_values,"descend");

		field <chromosome> sorted_population = _population;
		for (int i=0;i<_population_size;i++){
			int index = sorted_indices[i];
			sorted_population(i)=_population(index);
	}
	_population= sorted_population;
}

void GeneticOptimizer::check_order(){
	vec fitness_values = zeros(_population_size);
	for (int i=0;i<_population_size;i++){
		_population(i).compute_fitness();
		fitness_values[i]= _population(i).get_fitness();
	}

	if (fitness_values.is_sorted("descend")) cout<<"population sorted succesfully"<<endl;
	else cerr<<"sorting error"<<endl;

}

int GeneticOptimizer::selection(){
	
}