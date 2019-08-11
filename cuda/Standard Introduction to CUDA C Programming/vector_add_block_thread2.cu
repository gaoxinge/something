#include <stdio.h>
#define N 2048*2048
#define M 512


__global__ void add(int *a, int *b, int *c, int n) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < n) {
        c[index] = a[index] + b[index];
    }
}

void random_ints(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand();
    }
}

void print_ints(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}


int main() {
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;

    a = (int *) malloc(N * sizeof(int));
    b = (int *) malloc(N * sizeof(int));
    c = (int *) malloc(N * sizeof(int));

    random_ints(a, N);
    random_ints(b, N);

    cudaMalloc((void **) &d_a, N * sizeof(int));
    cudaMalloc((void **) &d_b, N * sizeof(int));
    cudaMalloc((void **) &d_c, N * sizeof(int));
    
    cudaMemcpy(d_a, a, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N * sizeof(int), cudaMemcpyHostToDevice);

    add<<<(N+M-1)/M,M>>>(d_a, d_b, d_c, N);

    cudaMemcpy(c, d_c, N * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    
    print_ints(c, N);

    free(a);
    free(b);
    free(c);    
    return 0;
}
