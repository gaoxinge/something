#include <stdio.h>
#include "mpi.h"
#define min(a, b) (a) < (b) ? (a) : (b)

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int buf[400];
    if (rank == 0) {
        for (int i = 0; i < 400; i++) {
            buf[i] = i;
	}
    }
    MPI_Bcast(buf, 400, MPI_INT, 0, MPI_COMM_WORLD);

    int dummy;
    MPI_Status status;
    MPI_Request request;
    int done;

    MPI_Irecv(&dummy, 1, MPI_INT, MPI_ANY_SOURCE, 123, MPI_COMM_WORLD, &request);
    MPI_Test(&request, &done, &status);

    int h = 400 / (size - 1);
    int a = h * rank;
    int b = h * (rank + 1);
    b = min(b, 400);
    int i;
    printf("%d handle in [%d, %d)\n", rank, a, b);
    for (i = a; i < b; i++) {
        if (done) {
            break;
	}

	if (buf[i] == 50) {
	     printf("%d found it at global index %d in [%d, %d)\n", rank, i, a, b);
             for (int j = 0; j < size; j++) {
                 // MPI_Send(&dummy, 1, MPI_INT, j, 123, MPI_COMM_WORLD);
	     }
	}

	MPI_Test(&request, &done, &status);
    }

    printf("%d stop at global index %d in [%d, %d)\n", rank, i, a, b);
    MPI_Finalize();
    return 0;
}
