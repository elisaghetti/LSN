#include <cmath>
#include <cstdlib>
#include <string>
#include <cstddef>
#include <cstdio>

#include "mpi.h"
#include "parallel_chromosome.h"


using namespace std;


MPI_Datatype create_gene();
void send_chromosome(parallel_chromosome ch, int recv);
parallel_chromosome receive_chromosome(int send);
