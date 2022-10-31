cmake_minimum_required(VERSION 3.10)
project(ex02)

find_package(OpenCL REQUIRED)
file(GLOB SOURCES ../C_common/*)
add_executable(main main.c ${SOURCES})
target_link_libraries(main PUBLIC OpenCL::OpenCL)
target_include_directories(main PUBLIC ../C_common)
