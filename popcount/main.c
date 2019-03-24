#include <stdio.h>
#include <stdint.h>

const int __popcount_table1[] = {  
  0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,  
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,  
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,  
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,  
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,  
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,  
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,  
  3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8,  
};

static int __popcount_table2[256];


void init();
int popcount_iter(unsigned);
int popcount_sparse(unsigned);
int popcount_lookup1(uint64_t);
int popcount_lookup2(uint64_t);


int main() {
    
    init();
    
    printf("%d\n", popcount_iter(7));
    printf("%d\n", popcount_sparse(7));
    printf("%d\n", popcount_lookup1(7));
    printf("%d\n", popcount_lookup2(7));
    printf("%d\n", __builtin_popcount(7));
    printf("%d\n", __builtin_popcountl(7));
    printf("%d\n", __builtin_popcountll(7));
    
    return 0;
}

void init() {
    for (unsigned i = 0; i < 256; ++i)
        __popcount_table2[i] = __popcount_table2[i/2] + (i & 1);
}

int popcount_iter(unsigned x) {
    int c;
    for (c = 0; x != 0; x >>= 1)
        if (x & 1)
            c++;
    return c;
}

int popcount_sparse(unsigned x) {
    int c;
    for (c = 0; x != 0; x &= x - 1)
        c++;
    return c;
}


int popcount_lookup1(uint64_t x) {
    return __popcount_table1[(x >> (0 * 8)) && 0xff] +
           __popcount_table1[(x >> (1 * 8)) && 0xff] +
           __popcount_table1[(x >> (2 * 8)) && 0xff] +
           __popcount_table1[(x >> (3 * 8)) && 0xff] +
           __popcount_table1[(x >> (4 * 8)) && 0xff] +
           __popcount_table1[(x >> (5 * 8)) && 0xff] +
           __popcount_table1[(x >> (6 * 8)) && 0xff] +
           __popcount_table1[(x >> (7 * 8)) && 0xff] ;
}

int popcount_lookup2(uint64_t x) {
    return __popcount_table2[(x >> (0 * 8)) && 0xff] +
           __popcount_table2[(x >> (0 * 8)) && 0xff] +
           __popcount_table2[(x >> (0 * 8)) && 0xff] +
           __popcount_table2[(x >> (0 * 8)) && 0xff] +
           __popcount_table2[(x >> (0 * 8)) && 0xff] +
           __popcount_table2[(x >> (0 * 8)) && 0xff] +
           __popcount_table2[(x >> (0 * 8)) && 0xff] +
           __popcount_table2[(x >> (0 * 8)) && 0xff] ;
    
}