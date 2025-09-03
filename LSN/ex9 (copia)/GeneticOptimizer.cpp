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
		ch.compute_fitness();
		//_fitness_values.push_back(ch.get_fitness());

		for (int i=0; i<_population_size;i++){
		int n_perm = int(rnd.Rannyu(1,_Ngenes));//number of permutations
		
		chromosome new_ch = ch;
		for(int j=0;j<n_perm;j++) new_ch.permutation(rnd);
		new_ch.compute_fitness();
		_population.push_back(new_ch);
		new_ch.check_bonds();
		
		_fitness_values.push_back(new_ch.get_fitness());
	
	}


	}

	void GeneticOptimizer::print_configuration(){
		ofstream out("./OUTPUT/positions.csv");
	out<<"ch_index\tindex\tx\ty"<<endl;
	for (int i=0; i<_population_size;i++){
		for (int j=0; j<_Ngenes+1;j++){
			out<<i<<"\t"<<_population[i].get_gene(j).index<<"\t"<<_population[i].get_gene(j).position[0]<<"\t"<<_population[i].get_gene(j).position[1]<<endl;
		}

	}
	out.close();
}

void GeneticOptimizer::sort_population(){
	

	sort (_population.begin(),_population.end(), [](chromosome a, chromosome b) {
              return a.get_fitness() > b.get_fitness();
          });

	   for (int i = 0; i < _population_size; i++) {
        _fitness_values[i]=_population[i].get_fitness();
    }

	

}

void GeneticOptimizer::check_order(){
	vec fitness_values = zeros(_population_size);
	for (int i=0;i<_population_size;i++){
		_population[i].compute_fitness();
		fitness_values[i]= _population[i].get_fitness();
	}

	if (fitness_values.is_sorted("descend")) cout<<"population sorted succesfully"<<endl;
	else cerr<<"sorting error"<<endl;

}

int GeneticOptimizer::selection(Random &rnd){
	bool accept = false;
	int result =0;
	while(accept==false){
	double normalization = accumulate(_fitness_values.begin(),_fitness_values.end(),0);
	int cand = int(rnd.Rannyu(0,_population_size));
	double norm = *max_element(_fitness_values.begin(),_fitness_values.end());
	double normalized_fitness=_population[cand].get_fitness()/norm;
	double r = rnd.Rannyu();
	if (r<normalized_fitness) {
		result = cand;
		accept = true;
	}
	}
	return result;
}

void GeneticOptimizer::select_parents(Random &rnd){
	ofstream out("./OUTPUT/selection.csv");
	int p1,p2;
	for (int i = 0; i<5000; i++){
	int p1 = selection(rnd);
	int p2 = selection (rnd);
	out<<p1<<endl;
	out<<p2<<endl;
	}
	out.close();
}

