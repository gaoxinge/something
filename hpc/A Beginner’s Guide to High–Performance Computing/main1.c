#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mpi.h"

#define drand48 1.0 / RAND_MAX * rand
#define srand48 srand
#define max 1000

int main(int argc, char **argv) {
    int numprocs, myid;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    
    int total_pi = 0;
    int pi = 0;
    MPI_Status status;
    
    if (myid == 0) {
        for (int proc = 1; proc < numprocs; proc++) {
            MPI_Recv(&pi, 1, MPI_REAL, proc, 123, MPI_COMM_WORLD, &status);
            total_pi += pi;
        }
        printf("result: %f from %d\n", 4 * (double) total_pi / ((numprocs - 1) * max), myid);
        fflush(stdout);
    } else {
        srand48(myid);
        for (int i = 0; i < max; i++) {
            double x = drand48() * 2 - 1;
            double y = drand48() * 2 - 1;
            if ((x * x + y * y) < 1) pi++;
        }
        printf("result: %f from %d\n", 4 * (double) pi / max, myid);
        fflush(stdout); 
        MPI_Send(&pi, 1, MPI_REAL, 0, 123, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}