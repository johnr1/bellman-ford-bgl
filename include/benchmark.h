#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "../include/concrete_graph.h"
#include <LEDA/graph/graph.h>


// Public
void benchmark();

// Private
double benchmark_boost_bf(Graph &G, Vertex start_nodes[]);
double benchmark_leda_bf(leda::GRAPH<unsigned, int> &G, leda::node start_nodes[]);
double benchmark_my_bf(Graph &G, Vertex start_nodes[]);

#endif