#include <stdio.h>

__global__ void add(int *a, int *b, int *c) {
    *c = *a + *b;
}

int main() {
    int a, b, c;
    int *d_a, *d_b, *d_c;

    a = 2;
    b = 7;

    cudaMalloc((void **) &d_a, sizeof(int));
    cudaMalloc((void **) &d_b, sizeof(int));
    cudaMalloc((void **) &d_c, sizeof(int));

    cudaMemcpy(d_a, &a, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, &b, sizeof(int), cudaMemcpyHostToDevice);

    add<<<1,1>>>(d_a, d_b, d_c);

    cudaMemcpy(&c, d_c, sizeof(int), cudaMemcpyDeviceToHost);

    printf("%d\n", c);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c); 
    return 0;
}
