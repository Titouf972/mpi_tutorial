# Puts the minimum required version for the CMake
cmake_minimum_required(VERSION 3.10)

# Creates a project name
project(tutorial_MPI VERSION 0.1)

# Look for MPI package
find_package(MPI REQUIRED)

# Add header files to search path
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

# Set right compiler for MPI
set(CMAKE_CXX_COMPILER mpicxx)


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

# Link libraries
target_link_libraries(tuto_mpi PRIVATE ${MPI_CXX})
target_link_libraries(tuto_mpi PUBLIC compiler_flags)
target_link_libraries(passing_message_tuto PRIVATE ${MPI_CXX})
target_link_libraries(passing_message_tuto PUBLIC compiler_flags)
target_link_libraries(group_ops_tuto PRIVATE ${MPI_CXX})
target_link_libraries(group_ops_tuto PUBLIC compiler_flags)