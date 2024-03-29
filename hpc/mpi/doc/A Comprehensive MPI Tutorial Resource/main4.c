#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100

int main() {
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int numbers[MAX_NUMBERS];
    int number_amount;

    if (world_rank == 0) {
        srand(time(NULL));
	number_amount = (1.0 * rand() / RAND_MAX) * MAX_NUMBERS;
	MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
	printf("0 sent %d numbers to 1\n", number_amount);
    } else if (world_rank == 1) {
        MPI_Status status;
	MPI_Recv(numbers, MAX_NUMBERS, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	MPI_Get_count(&status, MPI_INT, &number_amount);
	printf("1 received %d numbers from 0. Message source = %d, tag = %d\n", number_amount, status.MPI_SOURCE, status.MPI_TAG);
    }

    MPI_Finalize();
    return 0;
}
