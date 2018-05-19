#ifndef LABELER_H
#define LABELER_H

#include <LEDA/graph/graph.h>
#include "graph.h"
#include <vector>

enum class VertexLabel {Vminus = -1, Vf = 0, Vplus = 1};
std::string labelName(VertexLabel);

std::vector<VertexLabel> labelVertices(Graph &G,
									   bool contains_cycle,
									   std::vector<long> &dist,
									   std::vector<Vertex> &pred);

leda::node_array<VertexLabel> ledaLabelVertices(leda::GRAPH<unsigned,long> &G, 
												bool no_cycle, 
												leda::node s, 
												leda::node_array<leda::edge> &pred);

#endif