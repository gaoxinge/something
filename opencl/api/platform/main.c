#include <stdio.h>
#include <stdlib.h>
#include "CL/cl.h"

int main() {
    // get numbers of all available platforms
    cl_uint platformNum;
    clGetPlatformIDs(0, NULL, &platformNum);
    printf("%d\n", platformNum);
    
    // get all platform
    cl_platform_id *platforms = malloc(platformNum * sizeof(cl_platform_id));
    clGetPlatformIDs(platformNum, platforms, NULL);
    
    // show all platform infos
    for (cl_uint i = 0; i < platformNum; i++) {
        cl_platform_id platformId = platforms[i];
        
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
        
        printf("\n%s\n%s\n%s\n%s\n%s\n", profile, version, name, vendor, extensions);
    }
    
    free(platforms);
    return 0;
}