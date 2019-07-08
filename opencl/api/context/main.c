#include <stdio.h>
#include <stdlib.h>
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include "CL/cl.h"

int main() {
    int err;
    
    cl_platform_id platform;
    clGetPlatformIDs(1, &platform, NULL);
    
    cl_device_id device;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);
    
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    return 0;
}