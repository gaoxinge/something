cmake_minimum_required(VERSION 3.10)
project(2)
enable_language(CUDA)

add_executable(main main.cpp cuda_math.cu)
