cmake_minimum_required(VERSION 3.9)
project (projeto3 LANGUAGES CXX CUDA)
set (CMAKE_CXX_STANDARD 11)

add_executable(random-sol
    random-sol.cu
)

add_executable(2opt-sol
    2opt-sol.cu
)

add_executable(cpu-sol
    cpu-sol.cpp
)

target_compile_options(random-sol PUBLIC -O3)
target_compile_options(2opt-sol PUBLIC -O3)
target_compile_options(cpu-sol PUBLIC -O3 -DPARALLEL -DBB)