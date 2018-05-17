#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "graph.h"

enum class VertexLabel {Vminus = -1, Vf = 0, Vplus = 1};
std::string labelName(VertexLabel);

bool bellman_ford(Graph&,
				  std::vector<int> &costs,
				  std::vector<int> &dist,
				  std::vector<Vertex> &pred);


std::vector<VertexLabel> labelVertices(Graph &G,
									   bool contains_cycle,
									   std::vector<int> dist,
									   std::vector<Vertex> pred);



#endif
