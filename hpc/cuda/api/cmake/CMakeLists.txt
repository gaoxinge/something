cmake_minimum_required(VERSION 3.10)
project(cmake)
enable_language(CUDA)

add_executable(main main.cpp my_cuda.cu)
