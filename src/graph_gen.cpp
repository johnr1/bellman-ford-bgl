#include "../include/graph_gen.h"

Graph myGridGraph(int n){
    typedef std::pair<int,int> VertexPair;
    std::list<VertexPair> edges;
    for(int j=0; j<n-1; ++j){
        edges.emplace_back(VertexPair(j, j+1));
    }

    for(int i=1; i<n; ++i){
        for(int j=0; j<n-1; ++j){
            edges.emplace_back(VertexPair(i*n+j, i*n+j+1));
            edges.emplace_back(VertexPair((i-1)*n+j, i*n+j));
        }
        edges.emplace_back(VertexPair((i-1)*n+n-1, i*n+n-1));
    }

    Graph G(edges.begin(), edges.end(), n*n);

    return G;

}