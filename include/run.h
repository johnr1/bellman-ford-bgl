#ifndef RUN_H
#define RUN_H

#include "../include/concrete_graph.h"
#include <LEDA/graph/graph.h>

void run_boost_bf(const Graph &, const Vertex s, bool printResults = true );
void run_leda_bf(const leda::GRAPH<unsigned, int> &G, const leda::node s, bool printResults = true);


#endif
