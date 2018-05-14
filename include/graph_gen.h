#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include "../include/concrete_graph.h"

typedef std::pair<int,int> VertexPair;

// Public
Graph randomGraph(unsigned long n);
Graph myGridGraph(unsigned long);

// Private
void createEdge(unsigned long i, unsigned long j, unsigned long n, std::list<VertexPair> &edges, std::list<EdgeProperties> &edgeWeights);


#endif