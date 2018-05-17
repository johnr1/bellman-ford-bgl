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

    benchmark();
    return 0;

    Graph G = randomGraph(50);
    Vertex s = boost::random_vertex(G, gen);
    unsigned long n = boost::num_vertices(G);

    boost::print_graph(G);

    // Declare dist and pred vectors
    std::vector<int> dist (n);
    std::vector<Vertex> pred(n);

    // Get property map from bundled property cost
    CostPropertyMap costs = boost::get(&EdgeProperties::cost, G);

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
