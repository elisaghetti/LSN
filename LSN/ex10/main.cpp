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

int ngen =300;
int N_cities = 110;
int population_size=300;
int sim_type=2;
int n_migr =30;
ofstream out ("./OUTPUT/costs.csv");
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
	
		//process 0 exchanges with other process
		int recv1;
		do{
		recv1 = int(rnd.Rannyu(0,size));
		} while(recv1==0);
		//cout<<"Exchange between 0 and "<<recv1<<endl;
		best_results[0].send(recv1);
		best_ch = best_results[recv1];
		
		vector <int> couple2;
		for (int i=1;i<size;i++){
			if (i==recv1) continue;
			else couple2.push_back(i);
		}
		best_results[couple2[0]].send(couple2[1]);
		best_results[couple2[1]].send(couple2[0]);
				//cout<<rank<<endl;
		//best_ch.print_configuration();
	}

	if(rank>0) {
		best_ch.receive(0);
		//cout<<rank<<endl;
		//best_ch.print_configuration();
	}
}
out.close();

string filename = "./OUTPUT/best_path_" + to_string(rank) + ".csv";

			
ofstream out_path(filename);
out_path<<"n\tindex\tx\ty"<<endl;

	for (int i=0;i<N_cities+1;i++){
		out_path<<i<<"\t"<<best_ch.get_gene(i).index<<"\t"<<best_ch.get_gene(i).x<<"\t"<<best_ch.get_gene(i).y<<endl;
	}
out_path.close();
	

MPI_Finalize();
return 0;
}

//optimizing
//first do rank 0 which is main process

//migration
/*
if (rank ==0){//generate exchanges
	for (int j = 0;j<3;j++){
		vector <int> couple1;
		couple1.push_back(0);

		int recv1;
		do{
		recv1 = int(rnd.Rannyu(0,size));
		} while(recv1==0);
		couple1.push_back(recv1);

		vector <int> couple2;
		for (int i=1;i<size;i++){
			if (i==recv1) continue;
			else couple2.push_back(i);
		}

cout<<"Exchange between "<<couple1[0]<<" "<<couple1[1]<<" and "<<couple2[0]<<" "<<couple2[1]<<endl;
}

}*/
/*
for(int sender =0;sender<size;sender ++){
	int receiver;
	do{
	     receiver = int(rnd.Rannyu(0,size));
		} while(receiver == sender);
	cout<<"sendin from process "<<sender<<" to "<<receiver<<endl;
	if (rank==sender)proc[sender].get_best().send(receiver);
	if (rank==receiver){
	cout<<"receiving in process "<<receiver<<endl;
	proc[receiver].get_best().receive(sender);
	//proc[receiver].migration(i);
	}
}
*/



/*
	}
	for (continent x: proc){
		cn.migration(size,rank,);
	
/*
	Random rnd;
	rnd.RandomSetup(i);
	cout<<"Beginning process "<<i<<endl;
	parallel_GeneticOptimizer gen;
	gen.initialize(sim_type,N_cities,population_size);
	gen.create_starting_population(rnd);
	cout<<"Population for process "<<i<<"created, population size "<<population_size<<endl;
	parallel_chromosome best_result = gen.optimize(rnd,ngen);
	cout<<"finished optimization"<<endl;}
}
if (rank!=0){
	best_result.send(0);
}

if (rank==0){
	parallel_chromosome br1,br2;
	br1.initialize(N_cities,2);
	br1.receive(1);
	c

	br2.initialize(N_cities,2);
	br2.receive(2);

	
}
	/*
	ofstream out;
	string filename;
	if (i==0) filename = "./OUTPUT/best_path_0.csv";
	if (i==1) filename = "./OUTPUT/best_path_1.csv";
	if (i==2) filename = "./OUTPUT/best_path_2.csv";

	out.open(filename);

	out<<"n\tindex\tx\ty"<<endl;

	for (int i=0;i<N_cities+1;i++){
		out<<i<<"\t"<<best_result.get_gene(i).index<<"\t"<<best_result.get_gene(i).x<<"\t"<<best_result.get_gene(i).y<<endl;
	}
	out.close();
*/
	//for (int j=0;j<population_size;j++) gen.get_chromosome(j).print_configuration();
	
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
