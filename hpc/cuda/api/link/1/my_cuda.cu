#include "my_cuda.h"

__global__ void dummy_gpu_kernel() {
    //do something
}

void dummy_gpu() {
    dummy_gpu_kernel<<<128,128>>>();
}