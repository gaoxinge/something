#include <stdio.h>
#include "mpi.h"

// compile:
//   - mpicc main.c -o main
//   - gcc main.c -o main
// run:
//   - ./main
//   - mpiexec -n 4 main
int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Hello world from process %d of %d\n", rank, size);
    MPI_Finalize();
    return 0;
}
