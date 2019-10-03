cmake_minimum_required(VERSION 3.9)
project (projeto2)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_COMPILER /usr/local/bin/g++-9)
set (CMAKE_C_COMPILER /usr/local/bin/gcc-9)

# add_executable(tsp-O0-seq
#     tsp.cpp
# )

# add_executable(tsp-O1-seq
#     tsp.cpp
# )

# add_executable(tsp-O2-seq
#     tsp.cpp
# )

add_executable(tsp-O3-seq
    tsp.cpp
)

# add_executable(tsp-O0-parallel
#     tsp.cpp
# )

# add_executable(tsp-O1-parallel
#     tsp.cpp
# )

# add_executable(tsp-O2-parallel
#     tsp.cpp
# )

add_executable(tsp-O3-parallel
    tsp.cpp
)

# add_executable(tsp-O0-bb
#     tsp.cpp
# )

# add_executable(tsp-O1-bb
#     tsp.cpp
# )

# add_executable(tsp-O2-bb
#     tsp.cpp
# )

add_executable(tsp-O3-bb
    tsp.cpp
)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    # target_link_libraries(tsp-O0-seq PUBLIC OpenMP::OpenMP_CXX)
    # target_link_libraries(tsp-O1-seq PUBLIC OpenMP::OpenMP_CXX)
    # target_link_libraries(tsp-O2-seq PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(tsp-O3-seq PUBLIC OpenMP::OpenMP_CXX)
    # target_link_libraries(tsp-O0-parallel PUBLIC OpenMP::OpenMP_CXX)
    # target_link_libraries(tsp-O1-parallel PUBLIC OpenMP::OpenMP_CXX)
    # target_link_libraries(tsp-O2-parallel PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(tsp-O3-parallel PUBLIC OpenMP::OpenMP_CXX)
    # target_link_libraries(tsp-O0-bb PUBLIC OpenMP::OpenMP_CXX)
    # target_link_libraries(tsp-O1-bb PUBLIC OpenMP::OpenMP_CXX)
    # target_link_libraries(tsp-O2-bb PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(tsp-O3-bb PUBLIC OpenMP::OpenMP_CXX)
endif()

# target_compile_options(tsp-O0-seq PUBLIC -O0 -fopenmp)
# target_compile_options(tsp-O1-seq PUBLIC -O1 -fopenmp)
# target_compile_options(tsp-O2-seq PUBLIC -O2 -fopenmp)
target_compile_options(tsp-O3-seq PUBLIC -O3 -fopenmp)

# target_compile_options(tsp-O0-parallel PUBLIC -O0 -fopenmp -DPARALLEL)
# target_compile_options(tsp-O1-parallel PUBLIC -O1 -fopenmp -DPARALLEL)
# target_compile_options(tsp-O2-parallel PUBLIC -O2 -fopenmp -DPARALLEL)
target_compile_options(tsp-O3-parallel PUBLIC -O3 -fopenmp -DPARALLEL)

# target_compile_options(tsp-O0-bb PUBLIC -O0 -fopenmp -DPARALLEL -DBB)
# target_compile_options(tsp-O1-bb PUBLIC -O1 -fopenmp -DPARALLEL -DBB)
# target_compile_options(tsp-O2-bb PUBLIC -O2 -fopenmp -DPARALLEL -DBB)
target_compile_options(tsp-O3-bb PUBLIC -O3 -fopenmp -DPARALLEL -DBB)