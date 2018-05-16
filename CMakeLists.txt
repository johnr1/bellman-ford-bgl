cmake_minimum_required(VERSION 3.10)
project(algoask2)

set(CMAKE_CXX_STANDARD 11)
set(LEDAROOT "/home/john/Documents/lib/LEDA")

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

include_directories(${LEDAROOT}/incl)
link_directories(${LEDAROOT})

set(SOURCES
	"src/main.cpp"
	"src/graph_gen.cpp"
	"src/io.cpp"
	"src/utility.cpp"
	"src/boost_bf.cpp"
	"src/bellman_ford.cpp")

set(HEADERS
	"include/graph_gen.h"
	"include/io.h"
	"include/utility.h"
	"include/concrete_graph.h"
	"include/boost_bf.h"
	"include/bellman_ford.h")

add_executable(algoask2 ${SOURCES} ${HEADERS})
target_link_libraries(algoask2 leda m X11)
