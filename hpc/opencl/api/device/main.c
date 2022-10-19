#include <stdio.h>
#include <stdlib.h>
#include "CL/cl.h"

int main() {
    cl_platform_id platform;
    clGetPlatformIDs(1, &platform, NULL);
    
    cl_uint deviceNum;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &deviceNum);
    printf("%d\n", deviceNum);
    
    cl_device_id *devices = malloc(deviceNum * sizeof(cl_device_id));
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, deviceNum, devices, NULL);
    
    for (cl_uint i = 0; i < deviceNum; i++) {
        cl_device_id device = devices[i];
        
        size_t profileSize;
        size_t versionSize;
        size_t nameSize;
        size_t vendorSize;
        size_t extensionsSize;
        clGetDeviceInfo(device, CL_DEVICE_PROFILE, 0, NULL, &profileSize);
        clGetDeviceInfo(device, CL_DEVICE_VERSION, 0, NULL, &versionSize);
        clGetDeviceInfo(device, CL_DEVICE_NAME, 0, NULL, &nameSize);
        clGetDeviceInfo(device, CL_DEVICE_VENDOR, 0, NULL, &vendorSize);
        clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 0, NULL, &extensionsSize);
        
        char profile[profileSize];
        char version[versionSize];
        char name[nameSize];
        char vendor[vendorSize];
        char extensions[extensionsSize];
        clGetDeviceInfo(device, CL_DEVICE_PROFILE, profileSize, profile, NULL);
        clGetDeviceInfo(device, CL_DEVICE_VERSION, versionSize, version, NULL);
        clGetDeviceInfo(device, CL_DEVICE_NAME, nameSize, name, NULL);
        clGetDeviceInfo(device, CL_DEVICE_VENDOR, vendorSize, vendor, NULL);
        clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, extensionsSize, extensions, NULL);
        
        printf("\n%s\n%s\n%s\n%s\n%s\n", profile, version, name, vendor, extensions);
    }
    
    free(devices);
    return 0;
}
