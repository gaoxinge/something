cmake_minimum_required(VERSION 3.10)
project(context)

find_package(OpenCL REQUIRED)
add_executable(main main.c)
target_link_libraries(main OpenCL::OpenCL)
