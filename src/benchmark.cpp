#include "ctime"
#include "../include/benchmark.h"

#include <boost/random/mersenne_twister.hpp>
#include "../include/graph_gen.h"
#include "../include/bellman_ford.h"

#include <LEDA/graph/templates/shortest_path.h>
#include <boost/graph/bellman_ford_shortest_paths.hpp>


/**
 * Runs, times and prints the time to compelete
 * the bellman ford algorithm.
 *
 */
void benchmark(unsigned n, GraphType graph_type, unsigned ITERATIONS){
    boost::mt19937 gen(time(NULL));
    std::cout << "Running benchmark for " << ITERATIONS << " iteration(s)..." << std::endl;    

    Graph BG;
    Vertex b_start_nodes[ITERATIONS];
    leda::node l_start_nodes[ITERATIONS];

    // Generate graph
    if(graph_type == GraphType::random)
        BG = randomGraph(n);
    else if(graph_type == GraphType::grid)
        BG = myGridGraph(n);

    // Make copy in LEDA format
    leda::GRAPH<unsigned, long> LG = boostToLeda(BG);

    std::cout << "Graph Type: " << graphName(graph_type) <<" | Nodes: " << boost::num_vertices(BG) << " | Edges: " << boost::num_edges(BG) << std::endl;    

    // Pick same random nodes, translate them between formats
    for(unsigned i=0; i<ITERATIONS; ++i){
        leda::node v = LG.choose_node(); // Pick random, if grid, change to first
        if(graph_type == GraphType::grid)
            v = LG.first_node();

        l_start_nodes[i] = v;
        b_start_nodes[i] = LG[v];
    }

    double boost_time = benchmark_boost_bf(BG, b_start_nodes, ITERATIONS);
    std::cout << "BOOST_BF Time: " << boost_time << "s" << (boost_time<0 ? " (cycle detected)" : " ") << std::endl;

    double leda_time = benchmark_leda_bf(LG, l_start_nodes, ITERATIONS);
    std::cout << "LEDA_BF Time: " << leda_time << "s" << std::endl;
    
    double my_time = benchmark_my_bf(BG, b_start_nodes, ITERATIONS);
    std::cout << "MY_BF Time: " << my_time << "s" << std::endl << std::endl;
}


/* ========== Algorithm executors and timers ========== */

double benchmark_boost_bf(Graph &G, Vertex start_nodes[], unsigned ITERATIONS){
    unsigned long n = boost::num_vertices(G);

    // Get property map from bundled property cost
    CostPropertyMap costs = boost::get(&EdgeProperties::cost, G);

    // Declare dist and pred vectors
    std::vector<long> dist (n);
    std::vector<Vertex> pred(n);

    double elapsed_time = 0;
    std::clock_t start = clock();
    for(unsigned it=0; it<ITERATIONS; ++it){
        Vertex s = start_nodes[it];

        // Set pred to self (signifies null) and dist to max (required before running boost_bf)
        for (unsigned long i = 0; i < n; ++i){
            pred[i] = i;
            dist[i] = std::numeric_limits<long>::max();
        }

        // Set s as starter vertex
        dist[s] = 0;

        // Run algo
        bool no_neg_cycle = bellman_ford_shortest_paths(G, long(n), costs, &pred[0], &dist[0],
                                                        boost::closed_plus<long>(), std::less<long>(), boost::default_bellman_visitor());

        if(!no_neg_cycle){
            // If detected cycle return -1 as time
            elapsed_time = -1;
            return elapsed_time;
        }
    }
    elapsed_time = double(clock() - start) / CLOCKS_PER_SEC;
    return elapsed_time / ITERATIONS;
}


double benchmark_leda_bf(leda::GRAPH<unsigned, long> &G, leda::node start_nodes[], unsigned ITERATIONS){
    // Declare node_arrays dist and pred
    leda::node_array<leda::edge> pred(G);
    leda::node_array<long> dist(G);

    // Get property cost from inside GRAPH
    leda::edge_array<long> costs = G.edge_data();

    double elapsed_time = 0;
    std::clock_t start = clock();
    for(unsigned it=0; it<ITERATIONS; ++it){
        leda::node s = start_nodes[it];

        // Run algo
        bool no_neg_cycle = BELLMAN_FORD_B_T(G,s,costs,dist,pred);
    }
    elapsed_time = double(clock() - start) / CLOCKS_PER_SEC;
    return elapsed_time / ITERATIONS;
}


double benchmark_my_bf(Graph &G, Vertex start_nodes[], unsigned ITERATIONS){
    unsigned long n = boost::num_vertices(G);

    // Get property map from bundled property cost
    CostPropertyMap costs = boost::get(&EdgeProperties::cost, G);

    // Declare dist and pred vectors
    std::vector<long> dist (n);
    std::vector<Vertex> pred(n);

    double elapsed_time = 0;
    std::clock_t start = clock();
    for(unsigned it=0; it<ITERATIONS; ++it){
        Vertex s = start_nodes[it];

        // Run algo
        bool no_neg_cycle = bellman_ford(G, s, costs, dist, pred);
    }
    elapsed_time = double(clock() - start) / CLOCKS_PER_SEC;
    return elapsed_time / ITERATIONS;
}
