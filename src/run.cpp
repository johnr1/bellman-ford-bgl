#include <boost/graph/graphviz.hpp>

#include "../include/run.h"
#include "../include/bellman_ford.h"
#include "../include/io.h"
#include "../include/graph_gen.h"

#include <iostream>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/timer.hpp>



/**
 * Performs a test run of the my implemented 
 * bellman ford algorithm and prints results.
 * 
 * @param &G The graph to execute the bf on
 * @param s The starting Vertex
 * 
 */
void run_my_bf(Graph &G, Vertex s){
    unsigned long n = boost::num_vertices(G);

    std::cout << "Running my Bellman Ford algorithm" << std::endl;

    // Declare dist(intialized to int-max -> inf) and pred vectors
    std::vector<long> dist (n);
    std::vector<Vertex> pred(n);

    // Get property map from bundled property cost
    CostPropertyMap costs = boost::get(&EdgeProperties::cost, G);

    // Start timer
    boost::timer timer;

    // Run algo
    bool no_neg_cycle = bellman_ford(G, s, costs, dist, pred);

    // Stop timer
    double elapsed_time = timer.elapsed();

    // Check results and categorize vertices
    std::vector<int> labels(n);
    bool correct_results = bellman_ford_checker(G, s, costs, dist, pred, labels);

    // Print results
    std::cout << "S vertex is: " << s << std::endl;
    if (!no_neg_cycle) {
        std::cout << "Negative cycled detected." << std::endl;
    }

    VertexIterator vi, vi_end;
    for(boost::tie(vi, vi_end) = vertices(G); vi != vi_end; ++vi){
        std::cout << "Vertex: " << *vi;
        std::cout << " | Dist: "<< dist[*vi];
        std::cout << " | Pred: ";
        if(pred[*vi] == *vi) std::cout << "nil";
        else std::cout << pred[*vi];
        std::cout << " | Label: " << labelName(labels[*vi]) << std::endl;
    }
    
    if (correct_results) {
        std::cout << "Results OK!" << std::endl;
    } else {
        std::cout << "[Warning] Results appear to be incorrect" << std::endl;
    }
    std::cout << "Time to complete: " << elapsed_time << "s" << std::endl;

	std::ofstream f("graph.dot");
	boost::write_graphviz(f, G, boost::default_writer(), MyEdgeWriter(G, pred));
    std::cout << "Wrote graphviz format in file graph.dot" << std::endl;
	f.close();
}


// ----

/**
 * (Unused in the final executable, useful for testing)
 * Performs a test run of the internal 
 * boost bellman ford algorithm and prints results.
 * 
 * @param &G The graph to execute the bf on
 * @param s The starting Vertex
 * 
 */
void run_boost_bf(Graph &G, Vertex s){
    std::cout << "Running Internal boost algorithm" << std::endl;

    unsigned long n = boost::num_vertices(G);

    // Start timer (dist is initialized in constructor so timer starts before that)
    boost::timer timer;

    // Declare dist (intialized to int-max -> inf) and pred vectors
    std::vector<long> dist (n, std::numeric_limits <long>::max());
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
            (G, long(n), costs, &pred[0], &dist[0],
             boost::closed_plus<long>(), std::less<long>(), boost::default_bellman_visitor());

    // Stop timer
    double elapsed_time = timer.elapsed();

    // Print results
    std::cout << "S vertex is: " << s << std::endl;
    if (no_neg_cycle){
        VertexIterator vi, vi_end;
        for(boost::tie(vi, vi_end) = vertices(G); vi != vi_end; ++vi){
            std::cout << "Vertex: " << *vi;
            std::cout << " | Dist: "<< dist[*vi];
            std::cout << " | Pred: ";
            if(pred[*vi] == *vi) std::cout << "nil";
            else std::cout << pred[*vi];
            std::cout << std::endl;
        }
    }
    else
        std::cout << "Negative cycled detected on boost Bellman ford." << std::endl;

    std::cout << "Time to complete: " << elapsed_time << "s" << std::endl;
}

