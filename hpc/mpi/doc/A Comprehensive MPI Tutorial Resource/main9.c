#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

float *create_rand_nums(int num_elements) {
    float *rand_nums = malloc(sizeof(float) * num_elements);
    for (int i = 0; i < num_elements; i++) {
        rand_nums[i] = 1.0 * rand() / RAND_MAX;
    }
    return rand_nums;
}

float compute_avg(float *array, int num_elements) {
    float sum = 0.0f;
    for (int i = 0; i < num_elements; i++) {
        sum += array[i];
    }
    return sum / num_elements;
}

int main(int argc, char **argv) {
    int elements_per_proc = atoi(argv[1]);
    srand(time(NULL));

    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    float *rand_nums = NULL;
    if (world_rank == 0) {
        rand_nums = create_rand_nums(elements_per_proc * world_size);
    }

    float *sub_rand_nums = malloc(sizeof(float) * elements_per_proc);
    MPI_Scatter(rand_nums, elements_per_proc, MPI_FLOAT, sub_rand_nums, elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

    float sub_avg = compute_avg(sub_rand_nums, elements_per_proc);

    float *sub_avgs = NULL;
    if (world_rank == 0) {
        sub_avgs = malloc(sizeof(float) * world_size);
    }
    MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        float avg = compute_avg(sub_avgs, world_size);
	printf("Avg of all elements is %f\n", avg);
	float original_data_avg = compute_avg(rand_nums, elements_per_proc * world_size);
	printf("Avg computed across originals data is %f\n", original_data_avg);
    }

    if (world_rank == 0) {
        free(rand_nums);
	free(sub_avgs);
    }
    free(sub_rand_nums);

    MPI_Finalize();
    return 0;
}
