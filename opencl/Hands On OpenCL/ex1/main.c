#include <stdio.h>
#include <stdlib.h>
#include "CL/cl.h"

void showPlatformInfo(cl_platform_id platformId) {
    size_t profileSize;
    size_t versionSize;
    size_t nameSize;
    size_t vendorSize;
    size_t extensionsSize;
    clGetPlatformInfo(platformId, CL_PLATFORM_PROFILE, 0, NULL, &profileSize);
    clGetPlatformInfo(platformId, CL_PLATFORM_VERSION, 0, NULL, &versionSize);
    clGetPlatformInfo(platformId, CL_PLATFORM_NAME, 0, NULL, &nameSize);
    clGetPlatformInfo(platformId, CL_PLATFORM_VENDOR, 0, NULL, &vendorSize);
    clGetPlatformInfo(platformId, CL_PLATFORM_EXTENSIONS, 0, NULL, &extensionsSize);
        
    char profile[profileSize];
    char version[versionSize];
    char name[nameSize];
    char vendor[vendorSize];
    char extensions[extensionsSize];
    clGetPlatformInfo(platformId, CL_PLATFORM_PROFILE, profileSize, profile, NULL);
    clGetPlatformInfo(platformId, CL_PLATFORM_VERSION, versionSize, version, NULL);
    clGetPlatformInfo(platformId, CL_PLATFORM_NAME, nameSize, name, NULL);
    clGetPlatformInfo(platformId, CL_PLATFORM_VENDOR, vendorSize, vendor, NULL);
    clGetPlatformInfo(platformId, CL_PLATFORM_EXTENSIONS, extensionsSize, extensions, NULL);
    
    char *s = "- platform info:\n"
    "  - profile: %s\n"
    "  - version: %s\n"
    "  - name: %s\n"
    "  - vendor: %s\n"
    "  - extensions: %s\n";
    printf(s, profile, version, name, vendor, extensions);
}

void showDeviceInfo(cl_device_id deviceId) {
    size_t profileSize;
    size_t versionSize;
    size_t nameSize;
    size_t vendorSize;
    size_t extensionsSize;
    clGetDeviceInfo(deviceId, CL_DEVICE_PROFILE, 0, NULL, &profileSize);
    clGetDeviceInfo(deviceId, CL_DEVICE_VERSION, 0, NULL, &versionSize);
    clGetDeviceInfo(deviceId, CL_DEVICE_NAME, 0, NULL, &nameSize);
    clGetDeviceInfo(deviceId, CL_DEVICE_VENDOR, 0, NULL, &vendorSize);
    clGetDeviceInfo(deviceId, CL_DEVICE_EXTENSIONS, 0, NULL, &extensionsSize);
        
    char profile[profileSize];
    char version[versionSize];
    char name[nameSize];
    char vendor[vendorSize];
    char extensions[extensionsSize];
    clGetDeviceInfo(deviceId, CL_DEVICE_PROFILE, profileSize, profile, NULL);
    clGetDeviceInfo(deviceId, CL_DEVICE_VERSION, versionSize, version, NULL);
    clGetDeviceInfo(deviceId, CL_DEVICE_NAME, nameSize, name, NULL);
    clGetDeviceInfo(deviceId, CL_DEVICE_VENDOR, vendorSize, vendor, NULL);
    clGetDeviceInfo(deviceId, CL_DEVICE_EXTENSIONS, extensionsSize, extensions, NULL);
    
    char *s = "  - device info:\n"
    "    - profile: %s\n"
    "    - version: %s\n"
    "    - name: %s\n"
    "    - vendor: %s\n"
    "    - extensions: %s\n";
    printf(s, profile, version, name, vendor, extensions);
}

int main() {
    cl_uint platformNum;
    clGetPlatformIDs(0, NULL, &platformNum);
    
    cl_platform_id *platformIds = malloc(platformNum * sizeof(cl_platform_id));
    clGetPlatformIDs(platformNum, platformIds, NULL);
    
    for (cl_uint i = 0; i < platformNum; i++) {
        cl_platform_id platformId = platformIds[i];
        showPlatformInfo(platformId);
        
        cl_uint deviceNum;
        clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, 0, NULL, &deviceNum);
        
        cl_device_id *deviceIds = malloc(deviceNum * sizeof(cl_device_id));
        clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, deviceNum, deviceIds, NULL);
        
        for (cl_uint j = 0; j < deviceNum; j++) {
            cl_device_id deviceId = deviceIds[j];
            showDeviceInfo(deviceId);
        }
        
        free(deviceIds);
    }
    
    free(platformIds);
    
    return 0;
}