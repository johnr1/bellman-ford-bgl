#include "ctime"
#include "../include/benchmark.h"

#include <boost/random/mersenne_twister.hpp>
#include "../include/graph_gen.h"
#include "../include/bellman_ford.h"

#include <boost/graph/random.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>


/**
 * Runs, times and prints the time to complete
 * the bellman ford algorithm.
 *
 */
void benchmark(unsigned n, GraphType graph_type, unsigned ITERATIONS){
    boost::mt19937 gen(time(NULL));
    std::cout << "Running benchmark for " << ITERATIONS << " iteration(s)..." << std::endl;    

    Graph G;
    Vertex start_nodes[ITERATIONS];

    // Generate graph
    if(graph_type == GraphType::random)
        G = randomGraph(n);
    else if(graph_type == GraphType::grid)
        G = myGridGraph(n);


    std::cout << "Graph Type: " << graphName(graph_type) <<" | Nodes: " << boost::num_vertices(G) << " | Edges: " << boost::num_edges(G) << std::endl;

    // Pick same random nodes
    for(unsigned i=0; i<ITERATIONS; ++i){
        Vertex v = random_vertex(G, gen); // Pick random, if grid, change to first
        if(graph_type == GraphType::grid)
            v = 1;

        start_nodes[i] = v;
    }

    benchmark_boost_bf(G, start_nodes, ITERATIONS);
    benchmark_my_bf(G, start_nodes, ITERATIONS);
}


/* ========== Algorithm executors and timers ========== */

void benchmark_boost_bf(Graph &G, Vertex start_nodes[], unsigned ITERATIONS){
    unsigned long n = boost::num_vertices(G);

    // Get property map from bundled property cost
    CostPropertyMap costs = boost::get(&EdgeProperties::cost, G);

    // Declare dist and pred vectors
    std::vector<long> dist (n);
    std::vector<Vertex> pred(n);

    bool no_neg_cycle = true;

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
        bool cur_no_neg_cycle = bellman_ford_shortest_paths(G, long(n), costs, &pred[0], &dist[0],
                                                        boost::closed_plus<long>(), std::less<long>(), boost::default_bellman_visitor());

        no_neg_cycle = cur_no_neg_cycle & no_neg_cycle;
    }
    elapsed_time = double(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "BOOST BF Time: " << elapsed_time / ITERATIONS << "s" << (!no_neg_cycle ? " (cycle detected)" : " ") << std::endl;
}


void benchmark_my_bf(Graph &G, Vertex start_nodes[], unsigned ITERATIONS){
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
        bool no_neg_cycle = bellman_ford(G, s, costs, dist, pred);
    }
    elapsed_time = double(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "MY BF Time: " << elapsed_time / ITERATIONS << "s"  << std::endl;
}
