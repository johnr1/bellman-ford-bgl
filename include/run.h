#ifndef RUN_H
#define RUN_H

#include "graph.h"
#include <LEDA/graph/graph.h>

void run_boost_bf(Graph &, Vertex s);
void run_leda_bf(leda::GRAPH<unsigned, long> &G, leda::node s);
void run_my_bf(Graph &, Vertex s);

#endif
