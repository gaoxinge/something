#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#ifdef __APPLE__
    #include "OpenCL/opencl.h"
#else
    #include "CL/cl.h"
#endif

struct Image {
    std::vector<char> pixel;
    int width;
    int height;
};

Image LoadImage(const char *path) {
    std::ifstream in(path, std::ios::binary);
    
    std::string s;
    
    in >> s;
    if (s != "P6") {
        exit(1);
    }

    for (;;) {
        getline(in, s);
	if (s.empty()) {
            continue;
	}
	if (s[0] != '#') {
            break;
	}
    }

    std::stringstream str(s);
    int width;
    int height;
    str >> width >> height;
    
    int maxColor;
    in >> maxColor;
    if (maxColor != 255) {
        exit(1);
    }

    std::string tmp;
    getline(in, tmp);

    std::vector<char> data(width * height * 3);
    in.read(reinterpret_cast<char *>(data.data()), data.size());

    return {data, width, height};
}

void SaveImage(Image &img, const char *path) {
    std::ofstream out(path, std::ios::binary);
    out << "P6\n";
    out << img.width << " " << img.height << "\n";
    out << "225\n";
    out.write(img.pixel.data(), img.pixel.size());
}

Image RGBtoRGBA(Image &input) {
    Image result;
    result.width = input.width;
    result.height = input.height;
    for (std::size_t i = 0; i < input.pixel.size(); i += 3) {
        result.pixel.push_back(input.pixel[i + 0]);
        result.pixel.push_back(input.pixel[i + 1]);
        result.pixel.push_back(input.pixel[i + 2]);
        result.pixel.push_back(0);
    }
    return result;
}

Image RGBAtoRGB(Image &input) {
    Image result;
    result.width = input.width;
    result.height = input.height;
    for (std::size_t i = 0; i < input.pixel.size(); i += 4) {
        result.pixel.push_back(input.pixel[i + 0]);
        result.pixel.push_back(input.pixel[i + 1]);
        result.pixel.push_back(input.pixel[i + 2]);
    }
    return result;
}

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

    float filter[] = {
        1, 2, 1,
        2, 4, 2,
        1, 2, 1,
    };
    for (int i = 0; i < 9; i++) {
        filter[i] /= 16.0f;
    }
    Image image = RGBtoRGBA(LoadImage("test.ppm"));
    Image result = image;
    std::fill(result.pixel.begin(), result.pixel.end(), 0);

    cl_image_format format = { CL_RGBA, CL_UNORM_INT8 };
    cl_mem inputImage = clCreateImage2D(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, &format, image.width, image.height, 0, const_cast<char *>(image.pixel.data()), nullptr);
    cl_mem outputImage = clCreateImage2D(context, CL_MEM_WRITE_ONLY, &format, image.width, image.height, 0, nullptr, nullptr);
    cl_mem filterWeightsBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(float) * 9, filter, nullptr);

    cl_program program = CreateProgram(LoadKernel("image.cl"), context);
    clBuildProgram(program, deviceIdCount, deviceIds.data(), "-D FILTER_SIZE=1", nullptr, nullptr);
    cl_kernel kernel = clCreateKernel(program, "FILTER", nullptr);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputImage);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &filterWeightsBuffer);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputImage);

    cl_command_queue queue = clCreateCommandQueue(context, deviceIds[0], 0, nullptr);
    std::size_t offset[2] = { 0, 0 };
    std::size_t size[2] = { image.width, image.height };
    clEnqueueNDRangeKernel(queue, kernel, 2, offset, size, nullptr, 0, nullptr, nullptr);
    std::size_t origin[2] = { 0, 0 };
    std::size_t region[2] = { image.width, image.height };
    clEnqueueReadImage(queue, outputImage, CL_TRUE, origin, region, 0, 0, result.pixel.data(), 0, nullptr, nullptr);

    SaveImage(RGBAtoRGB(result), "output.ppm");

    clReleaseCommandQueue(queue);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseMemObject(inputImage);
    clReleaseMemObject(filterWeightsBuffer);
    clReleaseMemObject(outputImage);
    clReleaseContext(context);
    return 0;
}
