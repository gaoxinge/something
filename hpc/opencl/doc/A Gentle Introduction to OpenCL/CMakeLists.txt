cmake_minimum_required(VERSION 3.10)
project(add_numbers)

find_package(OpenCL REQUIRED)
add_executable(add_numbers add_numbers.c)
target_link_libraries(add_numbers OpenCL::OpenCL)
