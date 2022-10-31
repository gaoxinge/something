cmake_minimum_required(VERSION 3.10)
project(ex04)

find_package(OpenCL REQUIRED)
add_executable(main main2.cpp)
target_link_libraries(main PUBLIC OpenCL::OpenCL)
target_include_directories(main PUBLIC ../Cpp_common)
