#include "../include/run.h"
#include "../include/bellman_ford.h"

#include <iostream>
#include <cstdlib>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/timer.hpp>
#include <LEDA/graph/graph.h>
#include <boost/graph/graph_utility.hpp>

void run_boost_bf(Graph &G, Vertex s){
    unsigned long n = boost::num_vertices(G);

    std::cout << "Running Internal boost algorithm" << std::endl;

    // Start timer (dist is initialized in constructor so timer starts before that)
    boost::timer timer;

    // Declare dist (intialized to int-max -> inf) and pred vectors
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
    bool no_neg_cycle = bellman_ford_shortest_paths
            (G, int(n), costs, &pred[0], &dist[0],
             boost::closed_plus<int>(), std::less<int>(), boost::default_bellman_visitor());

    // Stop timer
    double elapsed_time = timer.elapsed();

    // Print results
    std::cout << "S vertex is: " << s << std::endl;
    if (no_neg_cycle){
        VertexIterator vi, vi_end;
        for(boost::tie(vi, vi_end) = vertices(G); vi != vi_end; ++vi){
            std::cout << "Vertex: " << *vi
                      << " | Dist: "<< (dist[*vi] == std::numeric_limits<int>::max() ? std::string("+INF") : std::to_string(dist[*vi]))
                      << " | Pred: " << pred[*vi] << std::endl;
        }
    }
    else
        std::cout << "Negative cycled detected on boost Bellman ford." << std::endl;

    std::cout << "Time to complete: " << elapsed_time << std::endl;
}


void run_leda_bf(leda::GRAPH<unsigned, int> &G, leda::node s){
    std::cout << "Running LEDA algorithm" << std::endl;

    // Declare node_arrays dist and pred
    leda::node_array<leda::edge> pred(G);
    leda::node_array<int> dist(G);

    // Get property cost from inside GRAPH
    leda::edge_array<int> costs = G.edge_data();

    // Start timer
    boost::timer timer;

    // Run algo
    bool no_neg_cycle = false; //BELLMAN_FORD_T(G,s,costs,dist,pred);

    //Stop timer
    double elapsed_time = timer.elapsed();

    // Print results
    if (!no_neg_cycle) {
        std::cout << "Negative cycled detected." << std::endl;
    }
    std::cout << "S vertex is: "; G.print_node(s); std::cout << std::endl;

    leda::node v;
    forall_nodes(v, G) {
            std::cout << "Vertex: " ; G.print_node(v) ;
            std::cout << " | Dist: "<< dist[v]
                      << " | Pred: " << pred[v] << std::endl;
    }
    std::cout << "Time to complete: " << elapsed_time << std::endl;
}

void run_my_bf(Graph &G, Vertex s){
    unsigned long n = boost::num_vertices(G);

    std::cout << "Running my Bellman Ford algorithm" << std::endl;

    // Declare dist(intialized to int-max -> inf) and pred vectors
    std::vector<int> dist (n);
    std::vector<Vertex> pred(n);

    // Get property map from bundled property cost
    CostPropertyMap costs = boost::get(&EdgeProperties::cost, G);

    // Start timer
    boost::timer timer;

    // Run algo
    bool no_neg_cycle = bellman_ford(G, s, costs, dist, pred);

    // Stop timer
    double elapsed_time = timer.elapsed();

    // Categorize labels
    std::vector<VertexLabel> labels = labelVertices(G, no_neg_cycle, dist, pred);

    // Print results
    std::cout << "S vertex is: " << s << std::endl;
    if (!no_neg_cycle) {
        std::cout << "Negative cycled detected." << std::endl;
    }

    VertexIterator vi, vi_end;
    for(boost::tie(vi, vi_end) = vertices(G); vi != vi_end; ++vi){
        std::cout << "Vertex: " << *vi
                  << " | Dist: "<< (dist[*vi] == std::numeric_limits<int>::max() ? std::string("+INF") : std::to_string(dist[*vi]))
                  << " | Pred: " << pred[*vi]
                  << " | Label: " << labelName(labels[*vi]) << std::endl;
    }

    std::cout << "Time to complete: " << elapsed_time << std::endl;
}
