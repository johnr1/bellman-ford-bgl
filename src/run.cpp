#include "../include/run.h"
#include "../include/bellman_ford.h"

#include <iostream>
#include <cstdlib>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <LEDA/graph/graph.h>


void run_boost_bf(Graph &G, Vertex s, bool printResults){
    unsigned long n = boost::num_vertices(G);

    // Declare dist(intialized to int-max -> inf) and pred vectors
    std::vector<int> dist (n, std::numeric_limits <int>::max());
    std::vector<Vertex> pred(n);

    // Get property map from bundled property cost
    CostPropertyMap costs = boost::get(&EdgeProperties::cost, G);

    // Initialize preds to self(signifies null)
    for (unsigned long i = 0; i < n; ++i)
        pred[i] = i;

    // Set s as starter vertex
    dist[s] = 0;

    // Run algo
    bool r = bellman_ford_shortest_paths
            (G, int(n), costs, &pred[0], &dist[0],
             boost::closed_plus<int>(), std::less<int>(), boost::default_bellman_visitor());


    if(!printResults)
        return;
    // Print results
    std::cout << "S vertex is: " << s << std::endl;
    if (r){
        std::pair<VertexIterator, VertexIterator> vi;
        for (vi = vertices(G); vi.first != vi.second; ++vi.first)
            std::cout << "Vertex " << *vi.first << ": " << "Distance from s=" << dist[*vi.first]
                << " | pred=" << pred[*vi.first] << std::endl;
    }
    else
        std::cout << "Negative cycled detected on boost Bellman ford." << std::endl;

}


void run_leda_bf(const leda::GRAPH<unsigned, int> &G, const leda::node s, bool printResults){
    long n = G.number_of_nodes();

    // Declare node_arrays dist and pred
    leda::node_array<leda::edge> pred(G);
    leda::node_array<int> dist(G);

    // Get property cost from inside GRAPH
    auto costs = G.edge_data();

    // Run algo
    bool no_neg_cycle;
#ifdef RUNNING_ON_DIOGENIS
    no_neg_cycle = BELLMAN_FORD_T(G,s,costs,dist,pred);
#else
    std::cout << "no leda algorithms available on free edition" << std::endl;
    return;
#endif

    if(!printResults)
        return;
    // Print results
    if (no_neg_cycle){
        leda::node v;
        forall_nodes(v, G) {
            std::cout << "Vertex " << v << ": " << "Distance from s=" << dist[v] << " | pred=" << pred[v] << std::endl;
        }
    }
    else
        std::cout << "Negative cycled detected on Bool bellmand ford." << std::endl;

}

