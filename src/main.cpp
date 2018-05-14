#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include "../include/concrete_graph.h"
#include "../include/graph_gen.h"

int main(int argc, char* argv[]) {
	Graph G = myGridGraph(10);
	boost::print_graph(G);

	
	
}
