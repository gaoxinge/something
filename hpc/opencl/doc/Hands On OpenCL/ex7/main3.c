#include <stdio.h>
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include "CL/cl.h"

cl_program clCreateProgramWithFile(cl_context context, 
                                   cl_uint count, 
                                   char *fileName,
                                   cl_int *errcode_ret) {
    FILE *f = fopen(fileName, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    rewind(f);
    
    char *programCode = malloc(fsize + 1);
    fread(programCode, 1, fsize, f);
    fclose(f);
    programCode[fsize] = '\0';
    
    cl_program program = clCreateProgramWithSource(context, 
                                                   count, 
                                                   (const char **)&programCode,
                                                   NULL,
                                                   errcode_ret);
    free(programCode);
    return program;
}

void initMatrix(int N, float *A, float *B) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = 1.0f;
            B[i * N + j] = 2.0f;
        }
    }
}

void printMatrix(int N, float *C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%0.1f ", C[i * N + j]);
        }
        printf("\n");
    }
}

int main() {
    cl_platform_id platformId;
    clGetPlatformIDs(1, &platformId, NULL);
    
    cl_device_id deviceId;
    clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, 1, &deviceId, NULL);
    
    cl_context context = clCreateContext(NULL, 1, &deviceId, NULL, NULL, NULL);
    
    size_t N = 10;
    size_t M = N / 5;
    float A[N * N], B[N * N], C[N * N], localmem[N];
    initMatrix(N, A, B);
    
    cl_mem dA = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * N * N, A, NULL);
    cl_mem dB = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * N * N, B, NULL);
    cl_mem dC = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * N * N, C, NULL);
    cl_mem dLocalmem = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * N, localmem, NULL);
    
    cl_program program = clCreateProgramWithFile(context, 1, "mat_mul2.cl", NULL);
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    cl_kernel kernel = clCreateKernel(program, "mat_mul", NULL);
    
    clSetKernelArg(kernel, 0, sizeof(int), &N);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &dA);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &dB);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &dC);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), &dLocalmem);
    
    cl_command_queue queue = clCreateCommandQueue(context, deviceId, 0, NULL);
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &N, &M, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, dC, CL_TRUE, 0, sizeof(float) * N * N, C, 0, NULL, NULL);
    printMatrix(N, C);
    
    clReleaseCommandQueue(queue);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseContext(context);
    return 0;
}