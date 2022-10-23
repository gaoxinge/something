#include <stdio.h>
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include "CL/cl.h"

const char *programCode = ""
"__kernel void vadd(__global const float *a," 
"                   __global const float *b," 
"                   __global float *c) {    "
"    int gid = get_global_id(0);            "
"    c[gid] = a[gid] + b[gid];              "
"}                                          ";

int main() {
    cl_platform_id platformId;
    clGetPlatformIDs(1, &platformId, NULL);
    
    cl_device_id deviceId;
    clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, 1, &deviceId, NULL);
    
    cl_context context = clCreateContext(NULL, 1, &deviceId, NULL, NULL, NULL);
    
    cl_command_queue queue = clCreateCommandQueue(context, deviceId, 0, NULL);
    
    size_t n = 30;
    float h_a[n], h_b[n], h_c[n], h_d[n], h_e[n];
    for (size_t i = 0; i < n; i++) {
        h_a[i] = 1.0f;
        h_b[i] = 2.0f;
        h_c[i] = 3.0f;
        h_d[i] = 4.0f;
    }
    
    cl_mem d_a = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * n, h_a, NULL);
    cl_mem d_b = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * n, h_b, NULL);
    cl_mem d_c = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * n, h_c, NULL);
    cl_mem d_d = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * n, h_d, NULL);
    cl_mem d_e = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * n, h_e, NULL);
    
    cl_program program = clCreateProgramWithSource(context, 1, &programCode, NULL, NULL);
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    cl_kernel kernel = clCreateKernel(program, "vadd", NULL);
    
    // add first time
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_e);
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &n, NULL, 0, NULL, NULL);
    
    // add second time
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_c);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_e);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_e);
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &n, NULL, 0, NULL, NULL);
    
    // add third time
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_d);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_e);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_e);
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &n, NULL, 0, NULL, NULL);
    
    // wait result
    clEnqueueReadBuffer(queue, d_e, CL_TRUE, 0, sizeof(float) * n, h_e, 0, NULL, NULL);
    for (size_t i = 0; i < n; i++) {
        printf("%0.1f ", h_e[i]);
    }
    printf("\n");
    
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    
    return 0;
}