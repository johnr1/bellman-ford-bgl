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

    Graph G;// = randomGraph(50);

    boost::add_edge(0,1, EdgeProperties(500), G);
    boost::add_edge(0,3, EdgeProperties(10), G);
    boost::add_edge(1,2, EdgeProperties(-5), G);
    boost::add_edge(2,1, EdgeProperties(-5), G);
    boost::add_edge(2,3, EdgeProperties(-5), G);
    boost::add_edge(4,3, EdgeProperties(-5), G);

    Vertex s = 0 ; //boost::random_vertex(G, gen);

    unsigned long n = boost::num_vertices(G);

    boost::print_graph(G);

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
    //bool r = bellman_ford_shortest_paths
    //        (G, int(n), costs, &pred[0], &dist[0],
    //         boost::closed_plus<int>(), std::less<int>(), boost::default_bellman_visitor());

    bool r = bellman_ford(G, s, costs, dist, pred);


    if(!r){
        std::cout << "Cycle detected" << std::endl;
    }

    // Label the vertexes
    std::vector<VertexLabel> labels = labelVertices(G, r, dist, pred);

    // Print results
    VertexIterator vi, vi_end;
    std::cout << "S: " << s << std::endl;
    for(boost::tie(vi, vi_end) = vertices(G); vi != vi_end; ++vi){
        std::cout << "Vertex: " << *vi
        << " | Dist: "<< (dist[*vi] == std::numeric_limits<int>::max() ? std::string("INF") : std::to_string(dist[*vi]))
        << " | Pred: " << pred[*vi]
        << " | Label: " << labelName(labels[*vi]) << std::endl;
    }





    //benchmark();
    return 0;
}
