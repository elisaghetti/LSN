#include <iostream>
#include <armadillo>
#include "GeneticOptimizer.h"
#include <random.h>

using namespace std;
using namespace arma;


int main () {
	Random rnd;
	rnd.RandomSetup();
	int N_cities = 7;
	int population_size=10;
/*
	GeneticOptimizer gen;
	gen.initialize(0,N_cities,population_size);
	cout<<"initialization"<<endl;
	gen.create_starting_population(rnd);
	cout<<"created population"<<endl;
	//gen.print_configuration();
	gen.sort_population();
	//gen.print_configuration(); //uncomment to save paths to a file
	cout<<"sorted population"<<endl;
	gen.check_order();

	gen.select_parents(rnd);
	cout<<"selected parents"<<endl;
	*/
	chromosome ch;
	ch.initialize(10,0);
	ch.print_configuration();
	for (int i=0;i<6;i++){
		//ch.shift_cities(rnd);
		//ch.inversion(rnd);
		ch.block_permutation(rnd);
	}
	//ch.print_configuration();*/
	//}

	/*
	vec chromosome = zeros (N_cities+1);

	for (int i=1;i<N_cities;i++) chromosome[i]=i;

	int population_size=5;
	mat population=zeros(N_cities+1,population_size);
	
	for (int i=0; i<population_size;i++){
		int n_perm = int(rnd.Rannyu(0,N_cities+1));//number of permutations
		//cout<<n_perm;
		vec new_chr=chromosome;
		for(int j=0;j<n_perm;j++) permutation(rnd,new_chr);
		population.col(i)=new_chr;
		check_bonds(new_chr);
		
	}
	
	cout<<chromosome<<endl;
	cout<<population<<endl;
*/
	return 0;
}