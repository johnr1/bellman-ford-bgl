#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "concrete_graph.h"

bool bellman_ford(const Graph&,
							 const std::vector<int> &costs,
							 std::vector<int> &dist,
							 std::vector<Vertex> &pred);


#endif
