cmake_minimum_required(VERSION 3.10)
project(ex9)

find_package(OpenCL REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC OpenCL::OpenCL)
target_include_directories(main PUBLIC ../Cpp_common)

add_executable(main1 main1.cpp)
target_link_libraries(main1 PUBLIC OpenCL::OpenCL)
target_include_directories(main1 PUBLIC ../Cpp_common)
