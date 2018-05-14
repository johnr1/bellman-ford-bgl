cmake_minimum_required(VERSION 3.10)
project(algoask2)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

add_executable(algoask2 src/main.cpp src/graph_gen.cpp include/concrete_graph.h include/graph_gen.h)