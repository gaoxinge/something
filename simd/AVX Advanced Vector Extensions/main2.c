#include <stdio.h>
#include "immintrin.h"

void iarray_print(int *f, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", f[i]);
}

// gcc main.c -mavx2 -o main
int main() {
    int f[8] = {1.0, 2.0, 1.2, 2.1, 5.2, 5.3, 10.1, 11.0};
	__m256i v = _mm256_load_si256((__m256i *) f);
    v = _mm256_add_epi32(v, v);
	_mm256_store_si256((__m256i *) f, v);
    iarray_print(f, 8);
    return 0;
}