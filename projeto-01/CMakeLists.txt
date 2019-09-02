cmake_minimum_required(VERSION 3.9)
project (projeto1)
set (CMAKE_CXX_STANDARD 11)

add_executable(main-O0
    main.cpp
    parser.cpp
)

add_executable(main-O1
    main.cpp
    parser.cpp
)

add_executable(main-O2
    main.cpp
    parser.cpp
)

add_executable(main-O3
    main.cpp
    parser.cpp
)

add_executable(main-O3-avx
    main.cpp
    parser.cpp
)

target_compile_options(main-O0 PUBLIC -O0)
target_compile_options(main-O1 PUBLIC -O1)
target_compile_options(main-O2 PUBLIC -O2)
target_compile_options(main-O3 PUBLIC -O3)
target_compile_options(main-O3-avx PUBLIC -O3 -ffast-math -ftree-vectorize -mavx)