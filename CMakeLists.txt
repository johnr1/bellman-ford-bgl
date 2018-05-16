cmake_minimum_required(VERSION 3.10)
project(algoask2)

set(CMAKE_CXX_STANDARD 11)
set(LEDAROOT "/home/john/bin/LEDA")

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

include_directories(${LEDAROOT}/incl)
link_directories(${LEDAROOT})

add_executable(algoask2 src/main.cpp src/graph_gen.cpp include/concrete_graph.h include/graph_gen.h src/io.cpp include/io.h)
target_link_libraries(algoask2 leda m X11)
