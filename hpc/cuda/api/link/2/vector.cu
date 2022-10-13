#include "vector.h"
#define N 2048
#define M 512

__global__ void cuda_vector_add(int *a, int *b, int *c, int n) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < n) c[index] = a[index] + b[index];
}

void vector_add(int *a, int *b, int *c, int n) {
    int *d_a, *d_b, *d_c;
    

    cudaMalloc((void **) &d_a, n * sizeof(int));
    cudaMalloc((void **) &d_b, n * sizeof(int));
    cudaMalloc((void **) &d_c, n * sizeof(int));

    cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, n * sizeof(int), cudaMemcpyHostToDevice);

    cuda_vector_add<<<(N+M-1)/M,M>>>(d_a, d_b, d_c, n);
    
    cudaMemcpy(c, d_c, n * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}
