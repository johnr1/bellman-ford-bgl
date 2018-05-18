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
    Vertex sperator = boost::graph_traits<Graph>::null_vertex(); //End marker
    unsigned long n = boost::num_vertices(G);
	long phase_count = 0;

	std::queue<Vertex> Q;
	std::vector<bool> in_Q(n, false);

    // Make everything equal infinity
	for(auto &d : dist)
	    d = std::numeric_limits<int>::max();

	// Make parent = self (signifies null)
	for(unsigned long i; i<n; i++)
	    pred[i] = i;

    dist[s] = 0;
    Q.emplace(s);
    in_Q[s] = true;
    Q.emplace(sperator); // end marker

    Vertex u;
    while(phase_count < n){
        u = Q.front(); Q.pop();
        if(u == sperator){
            phase_count++;
            if(Q.empty()) return true;
            Q.emplace(sperator);
            continue;
        }
        else
            in_Q[u] = false;

        int du = dist[u];

        OutEdgeIterator ei, ei_end;
        for(boost::tie(ei, ei_end) = boost::out_edges(u, G); ei != ei_end; ++ei){
            Vertex v = boost::target(*ei, G);
            int d = du + costs[*ei];
            if((pred[v] == sperator && v != s) || d < dist[v]){
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



/**
 * Given the dist and pred vectors, calculates the (V+, V- VF)
 * sets and returns them in a vector containing the VertexLabel
 * enum for each Vertex
 *
 * @param &G The Graph
 * @param no_cycle Whether it contains a negative circle or not
 * @param &dist The dist vector
 * @param &pred The pred vector
 * @return The set labels for each Vertex
 */
std::vector<VertexLabel> labelVertices(Graph &G, bool no_cycle, std::vector<int> &dist, std::vector<Vertex> &pred){
    unsigned long n = boost::num_vertices(G);
    std::vector<VertexLabel> labels(n);

    VertexIterator vi, vi_end;
    for(boost::tie(vi, vi_end) = vertices(G); vi!=vi_end; ++vi){
        // If dist = inf
        if(dist[*vi] == std::numeric_limits<int>::max()){
            labels[*vi] = VertexLabel::Vplus;
            continue;
        }

        if(no_cycle){
            labels[*vi] = VertexLabel::Vf;
            continue;
        }

        std::vector<bool> reachable(n);
        Vertex cur = *vi;
        reachable[cur] = true;
        while(true){
            // if pred == null (symbolized as parent==self)
            if(pred[cur] == cur){
                labels[*vi] = VertexLabel::Vf;
                break;
            }
                // if we saw same vertex, reachable from neg cycle
            else if(reachable[pred[cur]]){
                labels[*vi] = VertexLabel::Vminus;
                break;
            }

            reachable[cur] = true;
            cur = pred[cur];
        }
    }
    return labels;
}



/**
 * Returns a string of the Vertex label enum (V+, V-, Vf)
 *
 * @param vi The VertexLabel enum
 * @return The std::tring containing the name
 */
std::string labelName(VertexLabel vl){
    switch(vl) {
        case VertexLabel::Vminus : return "V-";
        case VertexLabel::Vf : return "Vf";
        case VertexLabel::Vplus : return "V+";
    }
    return "ERR";
}
