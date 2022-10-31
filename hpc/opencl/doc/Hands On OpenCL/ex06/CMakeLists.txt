cmake_minimum_required(VERSION 3.10)
project(ex06)

find_package(OpenCL REQUIRED)
add_executable(main matmul.cpp matrix_lib.cpp)
target_link_libraries(main PUBLIC OpenCL::OpenCL)
target_include_directories(main PUBLIC matmul.hpp matrix_lib.hpp ../Cpp_common)
