#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/make_connected.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "../include/graph_gen.h"

/**
 * Returns a random BOOST graph, edge costs: [-100, 10000]
 *
 * @param n Number of vertexes
 * @return The random Graph (as has been typedefed)
 */
Graph randomGraph(unsigned n){
    Graph G;
	auto m = static_cast<unsigned>(20 * n * log(n));

	boost::mt19937 gen(time(NULL)); //Seed with current time
    boost::generate_random_graph(G, n, m, gen, false, false);
    boost::make_connected<Graph>(G);

    std::pair<EdgeIterator, EdgeIterator> ei;
    for(ei = edges(G); ei.first != ei.second; ++ei.first){
		G[*ei.first].cost = rand() % (10000+1) - 100;
    }

    return G;
}

/**
 * Returns a BOOST grid graph, as documented in the exercise
 *
 *	@param n Grid size (Total vertexed n*n)
 * @return The Grid Graph in BOOST format (as has been typedefed)
 */
Graph myGridGraph(unsigned n){
    // Use lists for quick edge adding, create Graph with iterator constructor
    std::list<VertexPair> edges;
    std::list<EdgeProperties> edgeWeights;

    if(n == 0) return Graph();

	for(unsigned j=0; j<n-1; ++j){
        createEdge(j, j+1, n, edges, edgeWeights);
    }

	for(unsigned i=n; i<n*n; ++i){
        createEdge(i-n, i, n, edges, edgeWeights);
        if(i%n != 0)
            createEdge(i-1, i, n, edges, edgeWeights);
    }

    return Graph(edges.begin(), edges.end(), edgeWeights.begin(), n*n);
}

// USED BY myGridGraph()
void createEdge(unsigned i,
					  unsigned j,
					  unsigned n,
                      std::list<VertexPair> &edges,
                      std::list<EdgeProperties> &edgeWeights){
    // Decompose Vertex indexes in 2D grid
	unsigned  sourceX= i/n;
	unsigned  sourceY= i%n;
	unsigned  targetX= j/n;
	unsigned  targetY= j%n;

    VertexPair vp;
	int cost;

    // Two special edges
    if(sourceX == n/2 && sourceY == n/2-1 && targetX == n/2 && targetY == n/2){
        // right -> left
        vp = VertexPair(j, i);
        cost = -100000;
    }
    else if (sourceX == n/2-1 && sourceY == n/2-1 && targetX == n/2 && targetY == n/2-1){
        // down -> up
        vp = VertexPair(j, i);
        cost = -100000;
    }
    else if(sourceX < n/2 || sourceY >= n/2 || targetX <= n/2) {
        vp = VertexPair(i, j);
        cost = rand() % (10000+1);
    }
    else {
        vp = (rand() % 2) ? VertexPair(i, j) : VertexPair(j, i);
        cost = rand() % (10000+1) - 100;
    }

    edges.emplace_back(vp);
    edgeWeights.emplace_back(cost);
}

