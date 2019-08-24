cmake_minimum_required(VERSION 3.9)
project (02-oo-cpp)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-mavx")

# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

add_executable(vector_operations
    main.cpp
    experimento.cpp
    log.cpp
    pow3.cpp
    pow3mult.cpp
    sqrt.cpp
    sum.cpp
    sumavx.cpp
)

target_compile_definitions(vector_operations PUBLIC O0)

add_executable(vector_03
    main.cpp
    experimento.cpp
    log.cpp
    pow3.cpp
    pow3mult.cpp
    sqrt.cpp
    sum.cpp
    sumavx.cpp
)

target_compile_definitions(vector_03 PUBLIC O3)