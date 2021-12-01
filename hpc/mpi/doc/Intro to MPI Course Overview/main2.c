#include <math.h>
#include <stdio.h>
#include "mpi.h"

float integral(float a, float b, int n) {
    float s = 0, h = (b - a) / n;
    for (int i = 0; i < n; i++) {
        s += cos(a + h * (i + 0.5)) * h;
    }
    return s;
}

// mpicc main2.c -o main
// mpiexec -n 10 main
int main(int argc, char *argv[]) {
    int idx, num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &idx);
    MPI_Comm_size(MPI_COMM_WORLD, &num);
    
    float pi = 3.141592653;

    float a = 0;
    float b = pi / 2;
    float n = 100000;

    float h = (b - a) / num;
    float a0 = a + idx       * h;
    float b0 = a + (idx + 1) * h;

    float r = integral(a0, b0, n);
    printf("process %d has the partial result of %f\n", idx, r);

    float s;
    MPI_Reduce(&r, &s, 1, MPI_REAL, MPI_SUM, 0, MPI_COMM_WORLD);
    if (idx == 0) {
	printf("process %d has the final result of %f\n", idx, s);
    }

    MPI_Finalize();
    return 0;
}
