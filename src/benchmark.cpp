#include "../include/benchmark.h"

#include <boost/graph/random.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/timer.hpp> // perhaps for better results
#include "../include/graph_gen.h"
#include "../include/bellman_ford.h"

#define ITERATIONS 10

void benchmark(){
    boost::mt19937 gen(time(NULL));

    std::vector<std::pair<std::string, unsigned>> tests =
            {{"Random", 1000},{"Random", 4000},{"Random", 9000},{"Grid", 100},{"Grid", 200},{"Grid", 300}};
    Vertex b_start_nodes[ITERATIONS];
    leda::node l_start_nodes[ITERATIONS];

    std::cout << "Running benchmark, results will appear as executions complete..." << std::endl;
    std::cout << "Please be patient..." << std::endl << std::endl;

    std::vector<std::pair<std::string, unsigned>>::iterator test = tests.begin();
    for(; test != tests.end(); ++test){
        std::string graph_type = test->first;
        unsigned n = test->second;

        Graph BG;
        if(graph_type == "Random")
            BG = randomGraph(n);
        else if(graph_type == "Grid")
            BG = myGridGraph(n);

        leda::GRAPH<unsigned, int> LG = boostToLeda(BG);

        // Pick same random nodes, translate them between formats
        for(int i=0; i<ITERATIONS; ++i){
            leda::node v = LG.choose_node(); // Pick random, if grid, change to first
            if(graph_type == "Grid")
                v = LG.first_node();

            l_start_nodes[i] = v;
            b_start_nodes[i] = LG[v];
        }

        double boost_time = benchmark_boost_bf(BG, b_start_nodes);
        double leda_time = benchmark_leda_bf(LG, l_start_nodes);
        double my_time = benchmark_my_bf(BG, b_start_nodes);

        std::cout << "Graph Type: " << graph_type <<" | Nodes: " << boost::num_vertices(BG) << " | Edges: " << boost::num_edges(BG) << std::endl;
        std::cout << "BOOST_BF Time: " << boost_time << "s" << (boost_time<0 ? " (cycle detected)" : " ") << std::endl;
        std::cout << "LEDA_BF Time: " << leda_time << "s" << std::endl;
        std::cout << "MY_BF Time: " << my_time << "s" << std::endl << std::endl;
    }
}


/* ========== Algorithm executors and timers ========== */

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
        bool no_neg_cycle = bellman_ford_shortest_paths(G, int(n), costs, &pred[0], &dist[0],
                                                        boost::closed_plus<int>(), std::less<int>(), boost::default_bellman_visitor());

        if(!no_neg_cycle){
            // If detected cycle return -1 as time
            elapsed_time = -1;
            return elapsed_time;
        }
    }
    elapsed_time = double(clock() - start) / CLOCKS_PER_SEC;
    return elapsed_time / ITERATIONS;
}


double benchmark_leda_bf(leda::GRAPH<unsigned, int> &G, leda::node start_nodes[]){
    // Declare node_arrays dist and pred
    leda::node_array<leda::edge> pred(G);
    leda::node_array<int> dist(G);

    // Get property cost from inside GRAPH
    leda::edge_array<int> costs = G.edge_data();

    double elapsed_time = 0;
    std::clock_t start = clock();
    for(int it=0; it<ITERATIONS; ++it){
        leda::node s = start_nodes[it];

        // Run algo
        //bool no_neg_cycle = BELLMAN_FORD_T(G,s,costs,dist,pred);
    }
    elapsed_time = double(clock() - start) / CLOCKS_PER_SEC;
    return elapsed_time / ITERATIONS;
}


double benchmark_my_bf(Graph &G, Vertex start_nodes[]){
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

        // Run algo
        bool no_neg_cycle = bellman_ford(G, s, costs, dist, pred);

    }
    elapsed_time = double(clock() - start) / CLOCKS_PER_SEC;
    return elapsed_time / ITERATIONS;
}
