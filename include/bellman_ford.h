#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "graph.h"

enum class VertexLabel {Vminus = -1, Vf = 0, Vplus = 1};
std::string labelName(VertexLabel);

bool bellman_ford(Graph&,
				  Vertex s,
				  CostPropertyMap &costs,
				  std::vector<int> &dist,
				  std::vector<Vertex> &pred);


std::vector<VertexLabel> labelVertices(Graph &G,
									   bool contains_cycle,
									   std::vector<int> &dist,
									   std::vector<Vertex> &pred);

leda::node_array<VertexLabel> ledaLabelVertices(leda::GRAPH<unsigned,int> &G, bool no_cycle, leda::node s, leda::node_array<int> &dist, leda::node_array<leda::edge> &pred);



#endif
