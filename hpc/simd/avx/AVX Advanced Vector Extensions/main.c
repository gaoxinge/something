#include <stdio.h>
#include "immintrin.h"

void farray_print(float *f, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", f[i]);
    }
    printf("\n");
}

// gcc main.c -mavx -o main
int main() {
    float f[8] = {1.0, 2.0, 1.2, 2.1, 5.2, 5.3, 10.1, 11.0};
    __m256 v = _mm256_load_ps(f);
    v = _mm256_add_ps(v, v);
    _mm256_store_ps(f, v);
    farray_print(f, 8);
    return 0;
}
