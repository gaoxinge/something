#include <stdio.h>
#include "xmmintrin.h"

void farray_print(float *vals, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", vals[i]);
	if (i % 4 == 3) {
            printf("\n");
	}
    }
}

// gcc main2.c -msse -o main
int main() {
    float vals[16];
    float a = 2;
    float b = 2;

    for (int i = 0; i < 16; i++) {
        vals[i] = i;
    }

    for (int i = 0; i < 16; i += 4) {
        __m128 SSEa = _mm_load1_ps(&a);
	__m128 SSEb = _mm_load1_ps(&b);
	__m128 v = _mm_load_ps(vals + i);
        v = _mm_add_ps(_mm_mul_ps(v, SSEa), SSEb);
	_mm_store_ps(vals + i, v);
    }

    farray_print(vals, 16);
    
    return 0;
}
