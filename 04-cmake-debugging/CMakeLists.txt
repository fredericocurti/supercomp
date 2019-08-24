cmake_minimum_required(VERSION 3.9)
project (projeto_basico)
add_executable(hello hello_world.cpp)
    target_compile_definitions(hello PUBLIC O3)

