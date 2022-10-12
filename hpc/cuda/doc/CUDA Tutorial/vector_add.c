#include <stdio.h>
#include <stdlib.h>
#define N 1000000

void vector_add(float *out, float *a, float *b, int n) {
     for (int i = 0; i < n; i++) {
         out[i] = a[i] + b[i];
     }
}

int main() {
     float *a, *b, *out;

     a = (float *) malloc(sizeof(float) * N);
     b = (float *) malloc(sizeof(float) * N);
     out = (float *) malloc(sizeof(float) * N);

     for (int i = 0; i < N; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
     }

    vector_add(out, a, b, N);

    // for (int i = 0; i < N; i++) {
    //     printf("%0.1f ", out[i]);
    // }

    free(a);
    free(b);
    free(out);
    return 0;
}
