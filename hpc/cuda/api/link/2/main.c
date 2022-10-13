#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#define N 10

void init_ints1(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = 1;
    }
}

void init_ints2(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = 2;
    }
}

void print_ints(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}

int main() {
    int *a, *b, *c;
    
    a = (int *) malloc(N * sizeof(int));
    b = (int *) malloc(N * sizeof(int));
    c = (int *) malloc(N * sizeof(int));
    
    init_ints1(a, N);
    init_ints2(b, N);
    vector_add(a, b, c, N);
    print_ints(c, N);
    
    free(a);
    free(b);
    free(c);

    return 0;
}
