#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include "../include/concrete_graph.h"

typedef std::pair<unsigned, unsigned> VertexPair;

// Public
Graph randomGraph(unsigned);
Graph myGridGraph(unsigned);

// Private
void createEdge(unsigned i, unsigned j, unsigned n, std::list<VertexPair> &edges, std::list<EdgeProperties> &edgeWeights);


#endif
