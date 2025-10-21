#include "mpi.h"
#include <iostream>
#include <random>
#include "parallel_chromosome.h"
#include "parallel_GeneticOptimizer.h"
#include "parallel_tools.h"

using namespace std;

int main(int argc, char* argv[])
{

int size,rank;
MPI_Init(&argc,&argv);

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if(size > 8) cerr<<"PC only has 8 cores"<<endl;
int N_cities = 110;
int population_size=5;
int sim_type=2;
Random rnd;
rnd.RandomSetup();
/*
if (rank ==0){ //main process sends info to others
	for (int i =1; i< size;i++){

		/*
		parallel_GeneticOptimizer gen;
		gen.initialize(sim_type,N_cities,population_size);
		cout<<"initialization"<<endl;
		gen.create_starting_population(rnd);
		for (int j=0;j<population_size;j++){
			gen.get_chromosome(j).send(i);
		}
		//gen.send_population(i,0,population_size);
		/*
		parallel_chromosome ch;
		ch.initialize(N_cities,2);
		ch.assign_positions(rnd);
		ch.send(i);
		cout<<"sent chromosome  to process"<<i<<endl;	*

		}

		//process.initialize(rnd,N_cities,population_size);
		//world_proc.push_back(process);

	}

*/
//else{
for (int i =0;i<size;i++){
	
	if(rank==i){
		Random rnd;
	rnd.RandomSetup(i);
	cout<<"Beginning process "<<i<<endl;
	parallel_GeneticOptimizer gen;
	gen.initialize(sim_type,N_cities,population_size);
	gen.create_starting_population(rnd);
	cout<<"Population for process "<<i<<"created"<<endl;
	for (int j=0;j<population_size;j++) gen.get_chromosome(j).print_configuration();
	}
	//gen.receive_population(0,0,population_size);
	/*
	parallel_chromosome ch;

	ch.initialize(N_cities,2);
	cout<<"number of genes: "<<ch.get_ngenes()<<endl;
	ch.receive(0);
	cout<<"process "<<rank<<"received chromosome"<<endl;
	ch.print_configuration();
	ch.check_bonds();
	*/
}

	


/*
	if (argc!=2) cerr<<"Input simulation type: 0 for cities on a circle, 1 for cities in a square"<<endl;
	int sim_type=atoi(argv[1]);


	int population_size=500;
	int ngen = 1000;
	
	//idea
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
	if (sim_type==2) out.open("./OUTPUT/best_path_ita.csv");
	out<<"n\tindex\tx\ty"<<endl;

	for (int i=0;i<N_cities+1;i++)MPI_Finalize();ne(i).get_x()<<"\t"<<best_result.get_gene(i).get_y()<<endl;
	}
	out.close();


*/
MPI_Finalize();
return 0;
}