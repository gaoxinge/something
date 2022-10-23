cmake_minimum_required(VERSION 3.10)
project(image)

find_package(OpenCL REQUIRED)
add_executable(main main.cpp)
target_link_libraries(main OpenCL::OpenCL)
