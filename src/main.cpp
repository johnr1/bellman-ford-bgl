#include <iostream>
#include <LEDA/graph/graph.h>
#include <cstdlib>
#include <ctime>

#include "../include/graph.h"
#include "../include/benchmark.h"
#include "../include/run.h"

#include "../include/bellman_ford.h"

//
#include "../include/graph_gen.h"
#include <boost/graph/random.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/graph/graph_utility.hpp>
#include <cstdlib>
//

int main(int argc, char* argv[]) {
    srand (time(NULL));
    boost::mt19937 gen(time(NULL));

    Graph G; //= randomGraph(50);
    Vertex s; // = boost::random_vertex(G, gen);

    boost::add_edge(0,1, EdgeProperties(500), G);
    boost::add_edge(0,3, EdgeProperties(10), G);
    boost::add_edge(1,2, EdgeProperties(-5), G);
    boost::add_edge(2,1, EdgeProperties(-5), G);
    boost::add_edge(2,3, EdgeProperties(-5), G);
    boost::add_edge(4,3, EdgeProperties(-5), G);

    s = 0;

    run_my_bf(G, s);

    //benchmark();
    return 0;
}
