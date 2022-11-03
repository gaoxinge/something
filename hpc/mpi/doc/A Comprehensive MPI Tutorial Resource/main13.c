#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

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

    float global_sum;
    MPI_Allreduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    float mean = global_sum / (world_size * num_elements_per_proc);
    float local_sq_diff = 0;
    for (int i = 0; i < num_elements_per_proc; i++) {
        local_sq_diff += (rand_nums[i] - mean) * (rand_nums[i] - mean);
    }

    float global_sq_diff;
    MPI_Reduce(&local_sq_diff, &global_sq_diff, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (world_rank == 0) {
	float stddev = sqrt(global_sq_diff / (num_elements_per_proc * world_size));
        printf("Mean - %f, Standard deviation = %f\n", mean, stddev);
    }

    free(rand_nums);
    MPI_Finalize();
    return 0;
}
