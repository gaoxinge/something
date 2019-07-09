#include <stdio.h>
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include "CL/cl.h"

const char *program_code = ""
"__kernel void SAXPY(__global float *x, __global float *y, float a)"
"{                                                                 "
"    int i = get_global_id(0);                                     "   
"    y[i] += a * x[i];                                             "
"}                                                                 ";

int main() {
    cl_platform_id platform;
    clGetPlatformIDs(1, &platform, NULL);
    
    cl_device_id device;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);
    
    cl_program program = clCreateProgramWithSource(context, 1, (const char *[]){program_code}, NULL, NULL);
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    
    cl_kernel kernel = clCreateKernel(program, "SAXPY", NULL);
    
    size_t testDataSize = 10;
    float a[testDataSize];
    float b[testDataSize];
    float two = 2.0f;
    for (size_t i = 0; i < testDataSize; i++) {
        a[i] = i;
        b[i] = 0;
    }
    
    cl_mem aBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, testDataSize * sizeof(float), a, NULL);
    cl_mem bBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, testDataSize * sizeof(float), b, NULL);
    
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &aBuffer);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &bBuffer);
    clSetKernelArg(kernel, 2, sizeof(float), &two);
    
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, (const size_t[]){testDataSize, 0, 0}, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, bBuffer, CL_TRUE, 0, testDataSize * sizeof(float), b, 0, NULL, NULL);
    
    for (size_t i = 0; i < testDataSize; i++) {
        printf("%0.1f ", b[i]);
    }
    
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    
    return 0;
}