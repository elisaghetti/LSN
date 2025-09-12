#include <iostream>
#include <armadillo>
#include "GeneticOptimizer.h"
#include <random.h>

using namespace std;
using namespace arma;


int main (int argc,char **argv) {
	if (argc!=2) cerr<<"Input simulation type: 0 for cities on a circle, 1 for cities in a square"<<endl;
	int sim_type=atoi(argv[1]);
	Random rnd;
	rnd.RandomSetup();
	int N_cities = 34;
	int population_size=300;
	int ngen = 300;
	

	GeneticOptimizer gen;
	gen.initialize(sim_type,N_cities,population_size);
	cout<<"initialization"<<endl;
	gen.create_starting_population(rnd);
	cout<<"created population"<<endl;
	//gen.print_configuration();
	//gen.random_search(rnd,ngen);
	//gen.select_parents(rnd); //uncomment to create selection histogram
	
	chromosome best_result = gen.optimize(rnd,ngen);
	cout<<"finished optimization"<<endl;
	ofstream out;
	if (sim_type==0) out.open("./OUTPUT/best_path_circle.csv");
	if (sim_type==1) out.open("./OUTPUT/best_path_square.csv");
	out<<"n\tindex\tx\ty"<<endl;

	for (int i=0;i<N_cities+1;i++){
		out<<i<<"\t"<<best_result.get_gene(i).get_index()<<"\t"<<best_result.get_gene(i).get_x()<<"\t"<<best_result.get_gene(i).get_y()<<endl;
	}
	out.close();

	return 0;
}