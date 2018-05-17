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
	"src/graph.cpp"
	"src/bellman_ford.cpp"
	"src/benchmark.cpp"
	"src/run.cpp")

set(HEADERS
	"include/graph_gen.h"
	"snippets/io.h"
	"include/graph.h"
    "include/bellman_ford.h"
	"include/benchmark.h"
	"include/run.h")

add_executable(algoask2 ${SOURCES} ${HEADERS})
target_link_libraries(algoask2 leda m X11)
