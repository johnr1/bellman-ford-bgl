#include <ctime>
#include <cstdlib>
#include <iostream>

#include <LEDA/graph/graph.h>
#include <boost/graph/random.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/timer.hpp>
#include <boost/graph/relax.hpp>
#include "../include/concrete_graph.h"
#include "../include/graph_gen.h"
#include "../include/benchmark.h"
#include "../include/run.h"
#include "../include/utility.h"

#define ITERATIONS 10

void benchmark(){
    boost::mt19937 gen(time(NULL));

    std::pair<std::string, unsigned> tests[] = {{"Random", 1000},{"Random", 4000},{"Random", 9000},{"Grid", 100},{"Grid", 200},{"Grid", 300}};
    Vertex b_start_nodes[ITERATIONS];
    leda::node l_start_nodes[ITERATIONS];

    for(auto &test : tests){
        std::string graph_type = test.first;
        unsigned n = test.second;

        Graph BG;
        if(graph_type == "Random")
            BG = randomGraph(n);
        else if(graph_type == "Grid")
            BG = myGridGraph(n);


        auto LG = boostToLeda(BG);

        // Pick same random nodes, translate them between formats
        for(int i=0; i<ITERATIONS; ++i){
            auto v = LG.choose_node();
            l_start_nodes[i] = v;
            b_start_nodes[i] = LG[v];
        }

        double boost_time = 0; //benchmark_boost_bf();
        double leda_time = 1; //benchmark_boost_bf();
        double my_time = 2; //benchmark_boost_bf();

        std::cout << "Graph Type: " << graph_type <<" | Nodes: " << boost::num_vertices(BG) << " | Edges: " << boost::num_edges(BG) << std::endl;
        std::cout << "BOOST_BF Time: " << boost_time << "s" << std::endl;
        std::cout << "LEDA_BF Time: " << leda_time << "s" << std::endl;
        std::cout << "MY_BF Time: " << my_time << "s" << std::endl << std::endl;
    }
}



double benchmark_boost_bf(Graph &G, Vertex start_nodes[]){
    unsigned long n = boost::num_vertices(G);

    // Get property map from bundled property cost
    CostPropertyMap costs = boost::get(&EdgeProperties::cost, G);

    // Declare dist and pred vectors
    std::vector<int> dist (n);
    std::vector<Vertex> pred(n);

    double elapsed_time = 0;
    std::clock_t start = clock();
    for(int it=0; it<ITERATIONS; ++it){
        Vertex s = start_nodes[it];

        // Set pred to self (signifies null) and dist to max (required before running boost_bf)
        for (unsigned long i = 0; i < n; ++i){
            pred[i] = i;
            dist[i] = std::numeric_limits<int>::max();
        }

        // Set s as starter vertex
        dist[s] = 0;

        // Run algo
        bool r = bellman_ford_shortest_paths(G, int(n), costs, &pred[0], &dist[0],
                 boost::closed_plus<int>(), std::less<int>(), boost::default_bellman_visitor());

        if(!r){
            // Id detected cycle return -1 as time
            elapsed_time = -1;
            return elapsed_time;
        }
    }
    elapsed_time = double(clock() - start) / CLOCKS_PER_SEC;
    return elapsed_time / ITERATIONS;
}
