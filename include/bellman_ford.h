#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "graph.h"

bool bellman_ford(Graph&,
				  Vertex s,
				  CostPropertyMap &costs,
				  std::vector<long> &dist,
				  std::vector<Vertex> &pred);




#endif
