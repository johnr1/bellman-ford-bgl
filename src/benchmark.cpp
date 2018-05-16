#include <ctime>
#include <cstdlib>
#include <iostream>

#include <LEDA/graph/graph.h>
#include <boost/graph/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "../include/concrete_graph.h"
#include "../include/graph_gen.h"
#include "../include/benchmark.h"
#include "../include/run.h"


void benchmark(){
    boost::mt19937 gen(time(NULL));
    int iterations = 10;
    unsigned randSizes[] = {1000, 4000, 9000};
    unsigned gridSizes[] = {100, 200, 300};

    for(unsigned n : randSizes){
        Graph G = randomGraph(n);

        std::clock_t start = clock();
        for(int i=0; i<iterations; ++i){
            Vertex s = boost::random_vertex(G, gen);
            run_boost_bf(G, s, false);
        }
        double time = double(clock() - start) / CLOCKS_PER_SEC;
        std::cout << "Graph Type: Random | Algo: Boost | Time: " << time/iterations << "s" << std::endl;
    }

    for(int n : gridSizes){
        std::clock_t start;

        for(int i=0; i<iterations; ++i){
            std::cout << "size: " << n << "iter: " << i << "TO BE IMPLEMENTED" << std::endl;
        }
    }


}