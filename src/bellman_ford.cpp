#include <vector>

#include "../include/bellman_ford.h"
#include "../include/concrete_graph.h"


bool bellman_ford(const Graph &G,
								const std::vector<int> &costs,
								std::vector<int> &dist,
								std::vector<Vertex> &pred)
{
	long n = boost::num_vertices(G);
	long phase_count = 0;

	return false;
}
