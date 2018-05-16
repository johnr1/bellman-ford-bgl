#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphviz.hpp>
#include <LEDA/graph/graph.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "../include/concrete_graph.h"
#include "../include/graph_gen.h"
#include "../snippets/io.h"
#include "../include/utility.h"
#include "../include/benchmark.h"
#include "../include/run.h"

#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/random.hpp>
#include <boost/random/mersenne_twister.hpp>

int main(int argc, char* argv[]) {
    srand (time(NULL));
    boost::mt19937 gen(time(NULL));

    Graph G = randomGraph(1000);
    Vertex s = boost::random_vertex(G, gen);
    run_boost_bf(G, s);
    //benchmark();
    return 0;

}
