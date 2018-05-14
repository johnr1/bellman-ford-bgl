#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/make_connected.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <cstdlib>

#include "../include/graph_gen.h"

// Creates random connected Graph with edge cost -> [-100, 10000].
Graph randomGraph(unsigned long n){
    Graph G;
    auto m = static_cast<unsigned long>(20 * n * log(n));

    boost::mt19937 gen;
    boost::generate_random_graph(G, n, m, gen, false, false);
    boost::make_connected<Graph>(G);

    std::pair<EdgeIterator, EdgeIterator> ei;
    for(ei = edges(G); ei.first != ei.second; ++ei.first){
        G[*ei.first].cost = rand() % 10000 - 100;
    }

    return G;
}

// Creates the Grid Graph specified in the report.
Graph myGridGraph(unsigned long n){
    // Use lists for quick edge adding, create Graph with iterator constructor
    std::list<VertexPair> edges;
    std::list<EdgeProperties> edgeWeights;

    // Create first line of grid
    for(unsigned long j=0; j<n-1; ++j){
        createEdge(j, j+1, n, edges, edgeWeights);
    }

    // Create rest of lines, connect previous's line parallel vertex
    // createEdge() flips direction when needed (or randomly if in random range)
    for(unsigned long i=1; i<n; ++i){
        for(unsigned long j=0; j<n-1; ++j){
            createEdge(i*n+j, i*n+j+1, n, edges, edgeWeights);
            createEdge((i-1)*n+j, i*n+j, n, edges, edgeWeights);
        }
        createEdge((i-1)*n+n-1, i*n+n-1, n, edges, edgeWeights);
    }

    return Graph(edges.begin(), edges.end(), edgeWeights.begin(), n*n);
}

// PRIVATE - USED BY myGridGraph()
void createEdge(unsigned long i,
                      unsigned long j,
                      unsigned long n,
                      std::list<VertexPair> &edges,
                      std::list<EdgeProperties> &edgeWeights){
    // Decompose Vertex indexes in 2D grid
    unsigned long sourceX= i/n;
    unsigned long sourceY= i%n;
    unsigned long targetX= j/n;
    unsigned long targetY= j%n;

    VertexPair vp;
    double cost;

    // Two special edges
    if(sourceX == n/2+1 && sourceY == n/2-1 && targetX == n/2+1 && targetY == n/2){
        vp = VertexPair(j, i);
        cost = -100000;
    }
    else if (sourceX == n/2 && sourceY == n/2-1 && targetX == n/2+1 && targetY == n/2-1){
        vp = VertexPair(j, i);
        cost = -100000;
    }
    else if(sourceX < n/2 || sourceY >= n/2 || targetX <= n/2) {
        vp = VertexPair(i, j);
        cost = rand() % 10000;
    }
    else {
        vp = (rand() % 2) ? VertexPair(i, j) : VertexPair(j, i);
        cost = rand() % 10000 - 100;
    }

    edges.emplace_back(vp);
    edgeWeights.emplace_back(cost);

}

