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

// alignment reference
//   - https://stackoverflow.com/questions/32612190/how-to-solve-the-32-byte-alignment-issue-for-avx-load-store-operations
// g++ main4.c -mavx -o main
int main() {
    alignas(32) float a[N], b[N];
    float c = 3.0;
    
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    __m256 C = _mm256_broadcast_ss(&c);
    for (int i = 0; i < N; i += 8) {
        __m256 A = _mm256_load_ps(a + i);
	__m256 B = _mm256_mul_ps(A, C);
	_mm256_store_ps(b + i, B);
    }

    farray_print(b, N);

    return 0;
}
