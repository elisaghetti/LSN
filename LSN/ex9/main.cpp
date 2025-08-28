#include <iostream>
#include <armadillo>
#include "GeneticOptimizer.h"
#include <random.h>

using namespace std;
using namespace arma;

void permutation(Random &rnd,vec &chromosome){
	int rand_index1,rand_index2;
	do{
	rand_index1 = int(rnd.Rannyu(1,chromosome.size()-1));
	rand_index2 = int(rnd.Rannyu(1,chromosome.size()-1));
	} while(rand_index1==rand_index2);
	int val = chromosome[rand_index1];
	//do{ rand_value = int(rnd.Rannyu(1,chromosome.size()-1));}
	//while (rand_value==chromosome[rand_index]);
		chromosome[rand_index1]=chromosome[rand_index2];
		chromosome[rand_index2]=val;

}

void check_bonds(vec chromosome){
	if (chromosome[0]!=0 or chromosome[chromosome.size()-1]!=0) cerr<<"chromosome error: first and last city must have both index 0"<<endl;
	vec count_el = zeros(chromosome.size()-1);
	for (int i=0;i<chromosome.size()-1;i++){
		for (int j=0;j<chromosome.size()-1;j++){
			if(chromosome[j]==i)count_el[i]++;
		}
	if (count_el[i]>1) cerr<<"chromosome error: city "<<i<<"is repeated "<<count_el[i]<<" times"<<endl;
	}

}
int main () {
	Random rnd;
	rnd.RandomSetup();
	int N_cities = 7;
	int population_size=5;

	GeneticOptimizer gen;
	gen.initialize(0,N_cities,7);
	gen.create_starting_population(rnd);
	gen.print_configuration();
	gen.sort_population();
	gen.check_order();

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