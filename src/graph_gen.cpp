#include "../include/graph_gen.h"

typedef std::pair<int,int> VertexPair;

VertexPair createVertexPair(unsigned long i, unsigned long j, unsigned long n);

Graph myGridGraph(unsigned long n){
    std::list<VertexPair> edges;
    std::list<EdgeProperties> edgeWeights;

    for(unsigned long j=0; j<n-1; ++j){
        edges.emplace_back(VertexPair(j, j+1));
        edgeWeights.emplace_back(55);
    }

    for(unsigned long i=1; i<n; ++i){
        for(unsigned long j=0; j<n-1; ++j){
            edges.emplace_back(createVertexPair(i*n+j, i*n+j+1, n));
            edges.emplace_back(createVertexPair((i-1)*n+j, i*n+j, n));
            edgeWeights.emplace_back(66);
            edgeWeights.emplace_back(77);
        }
        edges.emplace_back(createVertexPair((i-1)*n+n-1, i*n+n-1, n));
        edgeWeights.emplace_back(88);
    }

    Graph G(edges.begin(), edges.end(), edgeWeights.begin(), n*n);

    return G;

}

VertexPair createVertexPair(unsigned long i, unsigned long j, unsigned long n){
    unsigned long sourceX= i/n;
    unsigned long sourceY= i%n;

    if(sourceX == n/2+1 && sourceY == n/2-1 ){
        return{j, i};
    }

    if(sourceX == n/2 && sourceY == n/2-1 ){
        return{j, i};
    }

    if(sourceX < n/2) {
        return {i, j};
    } else if ( sourceY >= n/2){
        return {i,j};
    } else {
        return {i,j};
    }

}

