#include <vector>
#include <queue>
#include <limits>

#include "../include/bellman_ford.h"
#include "../include/graph.h"

inline void update_pred(Graph& G, Vertex v, std::vector<bool> &reached_from_node_in_U, std::vector<int> &dist, std::vector<Vertex> &pred);

bool bellman_ford(Graph &G,
                  Vertex s,
                  CostPropertyMap &costs,
                  std::vector<int> &dist,
                  std::vector<Vertex> &pred)
{
    Vertex separator = boost::graph_traits<Graph>::null_vertex(); //End marker
    unsigned long n = boost::num_vertices(G);
	unsigned long phase_count = 0;

	std::queue<Vertex> Q;
	std::vector<bool> in_Q(n, false);

	// Make parent = self (signifies null) and dist=inf
	for(unsigned long i=0; i<n; i++) {
	    dist[i] = std::numeric_limits<int>::max();
        pred[i] = i;
    }

    dist[s] = 0;
    Q.emplace(s);
    in_Q[s] = true;
    Q.emplace(separator); // end marker

    Vertex u;
    while(phase_count < n){
        u = Q.front(); Q.pop();
        if(u == separator){
            phase_count++;
            if(Q.empty()) return true;
            Q.emplace(separator);
            continue;
        }
        else
            in_Q[u] = false;

        int du = dist[u];

        OutEdgeIterator ei, ei_end;
        for(boost::tie(ei, ei_end) = boost::out_edges(u, G); ei != ei_end; ++ei){
            Vertex v = boost::target(*ei, G);
            int d = du + costs[*ei];
            if((pred[v] == separator && v != s) || d < dist[v]){
                dist[v] = d;
                pred[v] = u;
                if( !in_Q[v] ){
                    Q.emplace(v);
                    in_Q[v] =  true;
                }
            }
        }
    }

    // BF POST PROCESSING

    if (pred[s] != s) return false;
    std::vector<bool> reached_from_node_in_U(n, false);

    VertexIterator vi, vi_end;
    for(boost::tie(vi, vi_end) = boost::vertices(G); vi != vi_end; ++vi){
        if(in_Q[*vi] && !reached_from_node_in_U[*vi]) {
            update_pred(G, *vi, reached_from_node_in_U, dist, pred);
        }
    }

    return false;
}

inline void update_pred(Graph& G, Vertex v, std::vector<bool> &reached_from_node_in_U, std::vector<int> &dist, std::vector<Vertex> &pred){
    reached_from_node_in_U[v] = true;
    OutEdgeIterator ei, ei_end;

    for(boost::tie(ei, ei_end) = boost::out_edges(v, G); ei != ei_end; ++ei){
        Vertex w = boost::target(*ei, G);
        if(!reached_from_node_in_U[w]){
            if(dist[w] < std::numeric_limits<int>::max()){
                pred[w] = v;
            }
            update_pred(G, w, reached_from_node_in_U, dist, pred);
        }
    }
}
