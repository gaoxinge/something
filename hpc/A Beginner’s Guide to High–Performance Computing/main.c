#include <stdio.h>
#include <stdlib.h>

#define drand48 1.0 / RAND_MAX * rand
#define srand48 srand
#define max 1000
#define seed 68111

int main() {
    int pi = 0;
    double area;
    srand48(seed);
    for (int i = 0; i < max; i++) {
        double x = drand48() * 2 - 1;
        double y = drand48() * 2 - 1;
        if ((x * x + y * y) < 1) pi++;
        area = 4 * (double) pi / i;
        printf("%d\t%f\n", i, area);
    }
    return 0;
}