#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "../include/concrete_graph.h"
#include "../include/graph_gen.h"
#include "../include/io.h"

int main(int argc, char* argv[]) {
    srand (time(NULL));

	Graph G = myGridGraph(10);
	//Graph G = randomGraph(10);
	boost::print_graph(G);

    myEdgeWriter mew(G);
	std::ofstream f("graph.txt");
	boost::write_graphviz(f, G, boost::default_writer(), mew);
	//boost::write_graphviz(f, G);

	f.close();
	return 0;

}
