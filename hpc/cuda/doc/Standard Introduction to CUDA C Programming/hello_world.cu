#include <stdio.h>

__global__ void myKernel() {
    printf("Hello World!\n");
}

int main() {
    myKernel<<<1,1>>>();
    return 0;
}
