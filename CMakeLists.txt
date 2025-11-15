# Puts the minimum required version for the CMake
cmake_minimum_required(VERSION 3.10)

# Creates a project name
set(CMAKE_CXX_COMPILER_ID "GNU")
set(CMAKE_COMPILER_IS_GNUCXX "1")
# set(CMAKE_CXX_COMPILER "/usr/local/bin/mpicxx")
# set(CMAKE_CXX_STANDARD 17)
set(CXX "/usr/local/bin/g++")
set(CMAKE_C_COMPILER "/usr/local/bin/gcc-15")
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++")
set(MPI_CXX_COMPILER "/usr/local/bin/mpicxx")
project(tutorial_MPI VERSION 0.1)

set(CMAKE_OSX_ARCHITECTURES "x86_64")


# Set right compiler for MPI
# Look for MPI package
set(CMAKE_PREFIX_PATH "/usr/local/bin/mpiexec")
find_package(MPI REQUIRED)

# Add header files to search path
include_directories(SYSTEM ${MPI_INCLUDE_PATH})



# Adds debug features
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(compiler_flags INTERFACE -Wall -O0 -g)
endif()

# Add the executable
add_executable(tuto_mpi main.cpp)
add_executable(passing_message_tuto mp.cpp)
add_executable(group_ops_tuto GroupOperators.cpp)
add_executable(LongMessage LongMessage.cpp)

# Link libraries
target_link_libraries(tuto_mpi PRIVATE MPI::MPI_CXX)
target_link_libraries(tuto_mpi PUBLIC compiler_flags)
target_link_libraries(passing_message_tuto PRIVATE MPI::MPI_CXX)
target_link_libraries(passing_message_tuto PUBLIC compiler_flags)
target_link_libraries(group_ops_tuto PRIVATE MPI::MPI_CXX)
target_link_libraries(group_ops_tuto PUBLIC compiler_flags)
target_link_libraries(LongMessage PRIVATE MPI::MPI_CXX)
target_link_libraries(LongMessage PUBLIC compiler_flags)