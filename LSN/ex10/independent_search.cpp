#include "mpi.h"
#include <iostream>
#include <random>
#include "parallel_chromosome.h"
#include "parallel_GeneticOptimizer.h"
#include "continent.h"

using namespace std;

int main(int argc, char* argv[])
{

int size,rank;

MPI_Init(&argc,&argv);

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
if (size%2 != 0) cerr<<"need even number of cores for algorithm to work"<<endl;
Random rnd;
rnd.RandomSetup(rank);


int ngen =50;
int N_cities = 110;
int population_size=100;
int sim_type=2;
int n_migr =200;
ofstream out ("./OUTPUT/indep_costs.csv");
out<<"migr\trank0\trank1\trank2\trank3\t"<<endl;

parallel_GeneticOptimizer gen;
gen.initialize(sim_type,N_cities,population_size);
gen.create_starting_population(rnd);
cout<<"Population for process "<<rank<<"created, population size "<<population_size<<endl;
parallel_chromosome best_ch;

for (int i=0;i<n_migr;i++){
 best_ch = gen.optimize(rnd,ngen);
//cout<<"process "<<rank<<" finished optimization"<<endl;
if (rank>0) best_ch.send(0);
if (rank==0){
	vector<parallel_chromosome> best_results(size);
	best_results[0]=best_ch;
	for (int i=1;i<size;i++) best_results[i].receive(i);
	out<<i<<"\t";
	for (parallel_chromosome x: best_results) {
	//x.print_configuration();
	out<<x.get_cost()<<"\t";
	}
	out<<endl;
	//write costs to file
}	
}
out.close();

string filename = "./OUTPUT/indep_best_path_" + to_string(rank) + ".csv";

			
ofstream out_path(filename);
out_path<<"n\tindex\tx\ty"<<endl;

	for (int i=0;i<N_cities+1;i++){
		out_path<<i<<"\t"<<best_ch.get_gene(i).index<<"\t"<<best_ch.get_gene(i).x<<"\t"<<best_ch.get_gene(i).y<<endl;
	}
out_path.close();
	

MPI_Finalize();
return 0;
}


