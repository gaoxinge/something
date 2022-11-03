#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

float *create_rand_nums(int num_elements) {
    float *rand_nums = malloc(sizeof(float) * num_elements);
    for (int i = 0; i < num_elements; i++) {
        rand_nums[i] = 1.0 * rand() / RAND_MAX;
    }
    return rand_nums;
}

int main(int argc, char **argv) {
    int num_elements_per_proc = atoi(argv[1]);

    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    srand(time(NULL) * world_rank);

    float *rand_nums = create_rand_nums(num_elements_per_proc);
    
    float local_sum = 0;
    for (int i = 0; i < num_elements_per_proc; i++) {
        local_sum += rand_nums[i];
    }
    printf("Local sum for process %d - %f, avg = %f\n", world_rank, local_sum, local_sum / num_elements_per_proc);
    fflush(stdout);

    float global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (world_rank == 0) {
        printf("Total sum = %f, avg = %f\n", global_sum, global_sum / (world_size * num_elements_per_proc));
    }

    free(rand_nums);
    MPI_Finalize();
    return 0;
}
