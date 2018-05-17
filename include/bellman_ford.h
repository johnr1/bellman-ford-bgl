#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "concrete_graph.h"


bool bellman_ford(const Graph&,
							 const std::vector<int> &costs,
							 std::vector<int> &dist,
							 std::vector<Vertex> &pred);


std::vector<VertexLabel> labelVertices(Graph &G,
									   bool contains_cycle,
									   std::vector<int> dist,
									   std::vector<Vertex> pred);



#endif
