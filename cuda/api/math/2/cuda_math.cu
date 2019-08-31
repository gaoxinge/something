#include "cuda_math.h"


__global__ void cuda_math_sqrt(float *a, float *b) {
    *b = sqrt(*a);
}


float math_sqrt(float a) {
    float b;
    float *d_a,  *d_b;

    cudaMalloc((void **) &d_a, sizeof(float));
    cudaMalloc((void **) &d_b, sizeof(float));
    
    cudaMemcpy(d_a, &a, sizeof(float), cudaMemcpyHostToDevice);

    cuda_math_sqrt<<<1,1>>>(d_a, d_b);

    cudaMemcpy(&b, d_b, sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);

    return b;
}

