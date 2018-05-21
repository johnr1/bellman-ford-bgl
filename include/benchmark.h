#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "graph.h"
#include <LEDA/graph/graph.h>


// Public
void benchmark(unsigned N, GraphType graph_type, unsigned ITERATIONS);

// Private
void benchmark_boost_bf(Graph &G, Vertex start_nodes[], unsigned ITERATIONS);
void benchmark_leda_bf(leda::GRAPH<unsigned, long> &G, leda::node start_nodes[], unsigned ITERATIONS);
void benchmark_my_bf(Graph &G, Vertex start_nodes[], unsigned ITERATIONS);

#endif