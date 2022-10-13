#include <stdio.h>
#include <stdlib.h>
#define N 1000000

__global__ void vector_add(float *out, float *a, float *b, int n) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;  // blockDim.x = block_size

    if (tid < n) {
        out[tid] = a[tid] + b[tid];
    }
}

int main() {
    float *a, *b, *out;
    float *d_a, *d_b, *d_out;

    a = (float *) malloc(sizeof(float) * N);
    b = (float *) malloc(sizeof(float) * N);
    out = (float *) malloc(sizeof(float) * N);

    for (int i = 0; i < N; i++) {
       a[i] = 1.0f;
       b[i] = 2.0f;
    }

    cudaMalloc((void **) &d_a, sizeof(float) * N);
    cudaMalloc((void **) &d_b, sizeof(float) * N);
    cudaMalloc((void **) &d_out, sizeof(float) * N);

    cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);
     
    int block_size = 256;
    int grid_size = N / block_size + (N % block_size != 0 ? 1 : 0);
    vector_add<<<grid_size, block_size>>>(d_out, d_a, d_b, N);

    cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);

    // for (int i = 0; i < N; i++) {
    //     printf("%0.1f ", out[i]);
    // }
     
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_out);
    free(a);
    free(b);
    free(out);
    return 0;
}
