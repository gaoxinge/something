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
        char profile[128];
        char version[128];
        char name[128];
        char vendor[128];
        char extensions[128];
        clGetPlatformInfo(platformId, CL_PLATFORM_PROFILE, 128 * sizeof(char), profile, NULL);
        clGetPlatformInfo(platformId, CL_PLATFORM_VERSION, 128 * sizeof(char), version, NULL);
        clGetPlatformInfo(platformId, CL_PLATFORM_NAME, 128 * sizeof(char), name, NULL);
        clGetPlatformInfo(platformId, CL_PLATFORM_VENDOR, 128 * sizeof(char), vendor, NULL);
        clGetPlatformInfo(platformId, CL_PLATFORM_EXTENSIONS, 128 * sizeof(char), extensions, NULL);
        printf("%s-%s-%s-%s-%s\n", profile, version, name, vendor, extensions);
    }
    
    free(platforms);
    return 0;
}