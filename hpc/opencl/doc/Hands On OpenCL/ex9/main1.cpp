#define __CL_ENABLE_EXCEPTIONS

#include <cstdio>
#include <iostream>
#include <vector>

#include "cl.hpp"
#include "util.hpp"
#include "err_code.h"

// pick up device type from compiler command line or from the default type
#ifndef DEVICE
#define DEVICE CL_DEVICE_TYPE_DEFAULT
#endif

#define steps 100000000

int main() {
    int N1 = 1000;
    int N2 = 100;
    int N3 = 1000;

    float step = 1.0f / steps;

    util::Timer timer;

    try {
        cl::Context context(DEVICE);
        cl::Program program(context, util::loadProgram("calpi.cl"), true);
        cl::CommandQueue queue(context);
    
        std::vector<float> global_arr(N1);
        cl::Buffer d_global_arr = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * N1);
        cl::LocalSpaceArg d_local_arr = cl::Local(sizeof(float) * N2);
    
        auto calpi = cl::make_kernel<int, float, cl::Buffer, cl::LocalSpaceArg>(program, "calpi");
        calpi(
            cl::EnqueueArgs(queue, cl::NDRange(N1 * N2), cl::NDRange(N2)),
            N3,
            step,
            d_global_arr,
            d_local_arr	
        );
        queue.finish();

        cl::copy(queue, d_global_arr, begin(global_arr), end(global_arr));

        float sum = 0.0f;
        for (int i = 0; i < N1; i++) {
            sum += global_arr[i];
        }
        sum *= step;
    
        double run_time = static_cast<double>(timer.getTimeMilliseconds()) / 1000.0;
	printf("\n pi with %ld steps is %lf in %lf seconds\n", steps, sum, run_time);
    } catch (cl::Error err) {
        std::cout << "Exception\n";
        std::cerr << "ERROR: "
                  << err.what()
                  << "("
                  << err_code(err.err())
                  << ")"
                  << std::endl;
    }

    return 0;
}
