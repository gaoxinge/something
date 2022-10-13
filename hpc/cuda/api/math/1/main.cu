#include <stdio.h>

__global__ void math_sqrt(float *a, float *b) {
    *b = sqrt(*a);
}

int main() {
    float a, b;
    float *d_a, *d_b;

    a = 4;
    
    cudaMalloc((void **) &d_a, sizeof(float));
    cudaMalloc((void **) &d_b, sizeof(float));

    cudaMemcpy(d_a, &a, sizeof(float), cudaMemcpyHostToDevice);

    math_sqrt<<<1, 1>>>(d_a, d_b);

    cudaMemcpy(&b, d_b, sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);

    printf("%f\n", b);
    return 0;
}
