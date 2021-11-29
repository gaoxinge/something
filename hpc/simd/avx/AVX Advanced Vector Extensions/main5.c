#include <stdio.h>
#include "immintrin.h"
#define N 16

void farray_print(float *f, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", f[i]);
	if (i % 8 == 7) {
            printf("\n");
	}
    }
    printf("\n");
}

// unalignment
// gcc main5.c -mavx -o main
int main() {
    float a[N], b[N];
    float c = 3.0;
    
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    __m256 C = _mm256_broadcast_ss(&c);
    for (int i = 0; i < N; i += 8) {
        __m256 A = _mm256_loadu_ps(a + i);
	__m256 B = _mm256_mul_ps(A, C);
	_mm256_storeu_ps(b + i, B);
    }

    farray_print(b, N);

    return 0;
}
