#include "parallel_tools.h"

using namespace std;

MPI_Datatype create_gene(){
    const int nitems=3;
    int blocklengths[3] = {1,1,1};
    MPI_Datatype types[3] = {MPI_INT, MPI_DOUBLE, MPI_DOUBLE};
    MPI_Datatype mpi_gene;
    MPI_Aint offsets[3];

    offsets[0] = offsetof(gene, index);
    offsets[1] = offsetof(gene, x);
    offsets[2] = offsetof(gene,y);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_gene);
    MPI_Type_commit(&mpi_gene);

    return mpi_gene;
}

void send_chromosome(parallel_chromosome ch, int recv){
    int ngenes = ch.get_ngenes();
    MPI_Datatype MPI_GENE = create_gene();
    vector <gene> chr_vec = ch.get_genevector();
    double cost = ch.get_cost();

    MPI_Send(&ngenes, 1, MPI_INT,recv,0,MPI_COMM_WORLD);
    MPI_Send(&chr_vec[0],ngenes+1,MPI_GENE,recv,1,MPI_COMM_WORLD);
    MPI_Send(&cost, 1, MPI_DOUBLE,recv,2,MPI_COMM_WORLD);

}


/*
void send_population(parallel_GeneticOptimizer gen,int recv){
    int population_size = gen.get_population_size();
    for (int i = 0; i<population_size;i++){
        parallel_chromosome ch = gen.get_chromosome(i);
        send_chromosome(ch, recv);
    }
}*/
parallel_chromosome receive_chromosome(int sender){
    int ngenes;
    double cost;
   
    MPI_Status status_n,status_ch,status_c;
    MPI_Datatype MPI_GENE = create_gene();
    MPI_Recv(&ngenes, 1, MPI_INT,sender,0,MPI_COMM_WORLD,&status_n);
    vector <gene> chr_vec(ngenes+1);
    cout<<"received ngenes: "<<ngenes<<endl;
    MPI_Recv(&chr_vec[0], ngenes+1, MPI_GENE,sender,1,MPI_COMM_WORLD,&status_ch);
    MPI_Recv(&cost, 1, MPI_DOUBLE,sender,2,MPI_COMM_WORLD,&status_c);

    parallel_chromosome ch;
    ch.set_ngenes(ngenes);
    ch.set_genevector(chr_vec);
    ch.set_cost(cost);

    return ch;
}

/*
void receive_population(parallel_GeneticOptimizer gen,int send){
    int population_size = gen.get_population_size();
    for (int i = 0; i<population_size;i++){
        parallel_chromosome ch = gen.get_chromosome(i);
        send_chromosome(ch, recv);
    }
}
*/