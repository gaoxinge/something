#include <stdio.h>
#include "cuda_math.h"

int main() {
    float a = 4;
    float b = math_sqrt(a);
    printf("%f\n", b);
    return 0;
}
