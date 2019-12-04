cmake_minimum_required(VERSION 3.9)
project (projeto3 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 11)


find_package(Boost REQUIRED mpi serialization)
find_package(MPI REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(exaustive-mpi exaustive-mpi.cpp)
add_executable(exaustive-bb exaustive-bb.cpp)
add_executable(2opt-mpi 2opt-mpi.cpp)

target_link_libraries(exaustive-mpi Boost::mpi Boost::serialization MPI::MPI_CXX)
target_link_libraries(2opt-mpi Boost::mpi Boost::serialization MPI::MPI_CXX)