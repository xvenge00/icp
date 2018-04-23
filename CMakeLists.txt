cmake_minimum_required(VERSION 3.9)
project(icp)

set(CMAKE_CXX_STANDARD 11)

add_executable(icp src/Computable.cpp src/Computable.h src/block.cpp src/block.h src/connection.cpp src/connection.h src/schema.cpp src/schema.h)
add_executable(block src/block.cpp src/block.h src/connection.cpp src/connection.h)
add_executable(computable src/Computable.cpp src/Computable.h)
