#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphviz.hpp>
#include <LEDA/graph/graph.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "../include/concrete_graph.h"
#include "../include/graph_gen.h"
#include "../include/io.h"
#include "../include/utility.h"

#include <boost/graph/bellman_ford_shortest_paths.hpp>

int main(int argc, char* argv[]) {
    srand (time(NULL));

	std::cout << std::numeric_limits<int>::max() << std::endl;

	Graph G = randomGraph(50);
	boost::print_graph(G);
	auto LG = boostToLeda(G);

	return 0;
	// ===================
	CostPropertyMap costsMap = boost::get(&EdgeProperties::cost, G);

	std::vector<int> distance (10, std::numeric_limits <int>::max());
	std::vector<Vertex> pred(10);
	int s = 0;

	for (int i = 0; i < 10; ++i) pred[i] = i;
	distance[s] = 0;

	bool r = bellman_ford_shortest_paths
	  (G, int(10), costsMap, &pred[0], &distance[0],
		boost::closed_plus<int>(), std::less<int>(), boost::default_bellman_visitor());

	if (r){
		std::pair<VertexIterator, VertexIterator> vi;
	  for (vi = vertices(G); vi.first != vi.second; ++vi.first)
		std::cout << *vi.first << ": " << std::setw(3) << distance[*vi.first]
		  << " " << pred[*vi.first] << std::endl;
	}
	else
	  std::cout << "negative cycle" << std::endl;

	return 0;

}
