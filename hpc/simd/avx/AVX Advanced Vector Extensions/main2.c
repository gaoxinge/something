#include <stdio.h>
#include "immintrin.h"

void iarray_print(int *f, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", f[i]);
    }
    printf("\n");
}

int main() {
    int f[8] = {1, 2, 0, 3, 5, 5, 10, 11};
    __m256i v = _mm256_load_epi32(f);
    v = _mm256_add_epi32(v, v);
    _mm256_store_epi32(f, v);
    iarray_print(f, 8);
    return 0;
}
