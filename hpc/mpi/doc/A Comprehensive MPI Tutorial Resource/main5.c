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

    int number_amount;

    if (world_rank == 0) {
        int numbers[MAX_NUMBERS];
	srand(time(NULL));
	number_amount = (1.0 * rand() / RAND_MAX) * MAX_NUMBERS;
	MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
	printf("0 sent %d numbers to 1\n", number_amount);
    } else if (world_rank == 1) {
        MPI_Status status;
	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
	MPI_Get_count(&status, MPI_INT, &number_amount);

	int *number_buf = malloc(sizeof(int) * number_amount);
	MPI_Recv(number_buf, number_amount, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("1 dynamically received %d numbers from 0\n", number_amount);
	free(number_buf);
    }

    MPI_Finalize();
    return 0;
}
