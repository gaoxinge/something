#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifdef __APPLE__
    #include "OpenCL/opencl.h"
#else
    #include "CL/cl.h"
#endif

std::string LoadKernel(const char *name) {
    std::ifstream in(name);
    std::string result(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>()
    );
    return result;
}

cl_program CreateProgram(const std::string &source, cl_context context) {
    const char* sources[1] = { source.data () };
    size_t lengths[1] = { source.size () };
    return clCreateProgramWithSource(
               context, 
               1, 
               sources,
               lengths,
               nullptr
           );
}

int main() {
    cl_uint platformIdCount = 0;
    clGetPlatformIDs(0, nullptr, &platformIdCount);
    std::vector<cl_platform_id> platformIds(platformIdCount);
    clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);

    cl_uint deviceIdCount = 0;
    clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, 0, nullptr, &deviceIdCount);
    std::vector<cl_device_id> deviceIds(deviceIdCount);
    clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, deviceIdCount, deviceIds.data(), nullptr);

    const cl_context_properties contextProperties[] =
    {
        CL_CONTEXT_PLATFORM,
        reinterpret_cast<cl_context_properties>(platformIds[0]),
        0, 
        0
    };
    cl_context context = clCreateContext(
        contextProperties, 
        deviceIdCount,
        deviceIds.data(), 
        nullptr,
        nullptr, 
        nullptr
    );

    size_t testDataSize = 10;
    std::vector<float> a(testDataSize);
    std::vector<float> b(testDataSize);
    for (int i = 0; i < testDataSize; i++) {
        a[i] = static_cast<float>(i);
        b[i] = static_cast<float>(i);
    }
    float two = 2.0f;

    cl_mem aBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * testDataSize, a.data(), nullptr);
    cl_mem bBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE|CL_MEM_COPY_HOST_PTR, sizeof(float) * testDataSize, b.data(), nullptr);

    cl_program program = CreateProgram(LoadKernel("saxpy.cl"), context);
    clBuildProgram(program, deviceIdCount, deviceIds.data(), nullptr, nullptr, nullptr);
    cl_kernel kernel = clCreateKernel(program, "SAXPY", nullptr);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &aBuffer);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &bBuffer);
    clSetKernelArg(kernel, 2, sizeof(float), &two);

    cl_command_queue queue = clCreateCommandQueue(context, deviceIds[0], 0, nullptr);
    size_t globalWorkSize[1] = { testDataSize };
    clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, globalWorkSize, nullptr, 0, nullptr, nullptr);
    clEnqueueReadBuffer(queue, bBuffer, CL_TRUE, 0, sizeof(float) * testDataSize, b.data(), 0, nullptr, nullptr);

    for (int i = 0; i < testDataSize; i++) {
        std::cout << b[i] << std::endl;
    }

    clReleaseCommandQueue(queue);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseMemObject(aBuffer);
    clReleaseMemObject(bBuffer);
    clReleaseContext(context);
    return 0;
}
