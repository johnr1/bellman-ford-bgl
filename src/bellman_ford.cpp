#include <vector>
#include <stack>
#include <queue>
#include <limits>

#include "../include/bellman_ford.h"
#include "../include/graph.h"

inline void update_pred(Graph& G, Vertex v, std::vector<bool> &reached_from_node_in_U, std::vector<bool> &in_R, std::vector<Vertex> &pred);

/**
 * Implements the bellman ford algorithm
 * as described in the documentation provided.
 * It updates the preds if a negative cycle
 * is detected.
 * 
 * @param &G The graph to execute the bf on
 * @param s The starting Vertex
 * @param &costs The property map containing the costs
 * @param &dist The distance vector (is populated with the distances)
 * @param &pred The pred vector (is popuated with the parent Vertices)
 * @return Boolean, true if didn't find cycle
 * 
 */
bool bellman_ford(Graph &G,
                  Vertex s,
                  CostPropertyMap &costs,
                  std::vector<long> &dist,
                  std::vector<Vertex> &pred)
{
    const Vertex separator = boost::graph_traits<Graph>::null_vertex(); //End marker
    unsigned long n = boost::num_vertices(G);
	unsigned long phase_count = 0;

	std::queue<Vertex> Q;
	std::vector<bool> in_Q(n, false);

	// Make parent = self (signifies null) and dist=inf
	for(unsigned long i=0; i<n; i++) {
	    dist[i] = std::numeric_limits<long>::max();
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

        long du = dist[u];

        OutEdgeIterator ei, ei_end;
        for(boost::tie(ei, ei_end) = boost::out_edges(u, G); ei != ei_end; ++ei){
            Vertex v = boost::target(*ei, G);
            long d = du + costs[*ei];
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

    // BELLMAN-FORD POSTPROCESSING
    if (pred[s] != s) return false;

    std::vector<bool> reached_from_node_in_U(n, false);
    std::vector<bool> in_R(n, false); // until you  find a way to specify R keep true

    Graph tmpG(n);
    VertexIterator vi, vi_end;
    for(boost::tie(vi, vi_end) = boost::vertices(G); vi != vi_end; ++vi){
        if(pred[*vi] != *vi){
           boost::add_edge(pred[*vi], *vi, EdgeProperties(0), tmpG);
        }
    }

    dfs(tmpG, s, in_R);
    
    for(boost::tie(vi, vi_end) = boost::vertices(G); vi != vi_end; ++vi){
        if(in_Q[*vi] && !reached_from_node_in_U[*vi]) {
            update_pred(G, *vi, reached_from_node_in_U, in_R, pred);
        }
    }

    return false;
}

inline void update_pred(Graph& G, Vertex v, std::vector<bool> &reached_from_node_in_U, std::vector<bool> &in_R, std::vector<Vertex> &pred){
    reached_from_node_in_U[v] = true;
    OutEdgeIterator ei, ei_end;

    for(boost::tie(ei, ei_end) = boost::out_edges(v, G); ei != ei_end; ++ei){
        Vertex w = boost::target(*ei, G);
        if(!reached_from_node_in_U[w]){
            if(in_R[w]) {
                pred[w] = v;
            }
            update_pred(G, w, reached_from_node_in_U, in_R, pred);
        }
    }
}


/**
 * Checks the correctness of the results
 * of the bellman ford algorithm.
 * 
 * @param &G The graph to search
 * @param s The starter vertex
 * @param &costs The CostPropertyMap containing the cost of the edges
 * @param &dist The vector containing the distance of the Vertices
 * @param &pred The vector containing the preds of the Vertices
 * @return True if correct or false if integrity check failed
 */
bool bellman_ford_checker (Graph& G,
				  Vertex s,
				  CostPropertyMap &costs,
				  std::vector<long> &dist,
				  std::vector<Vertex> &pred)
{
    unsigned long n = boost::num_vertices(G);
    enum{ NEG_CYCLE = -2, ATT_TO_CYCLE = -1, FINITE = 0, PLUS = 1, CYCLE = 2, ON_CUR_PATH = 3, UNKNOWN = 4 };

    std::vector<Vertex> label(n,UNKNOWN);
    std::vector<bool> reachable(n,false);

    // Condition (1)
    dfs(G,s,reachable);

    VertexIterator vi, vi_end;
    for(boost::tie(vi, vi_end) = boost::vertices(G); vi != vi_end; ++vi){
        if( *vi != s ){
            if(!((pred[*vi] == *vi) == (reachable[*vi] == false))) return false;
            if(reachable[*vi] == false) label[*vi] = PLUS;
        }
    }

    // Classification of nodes
    if (pred[s] == s) label[s] = FINITE;

    for(boost::tie(vi, vi_end) = boost::vertices(G); vi != vi_end; ++vi){
        Vertex v = *vi;
        if ( label[v] == UNKNOWN ){ 
            std::stack<Vertex> S;
            Vertex w = v;
            while ( label[w] == UNKNOWN && w != pred[w]){ //added check for nil (w != pred[w])
                label[w] = ON_CUR_PATH;
                S.push(w);
                w = pred[w];
            }

            // label all nodes on current path
            int t = label[w];
            if ( t == ON_CUR_PATH ){
                Vertex z;
                do { 
                    z = S.top(); S.pop();
                    label[z] = CYCLE;
                }
                while ( z != w );
                while ( !S.empty() ){ 
                    label[S.top()] = ATT_TO_CYCLE;
                    S.pop();
                }
            }
            else{ // t is CYCLE, ATT_TO_CYCLE, or FINITE
                if ( t == CYCLE ) t = ATT_TO_CYCLE;
                while ( !S.empty() ){ 
                    label[S.top()] = t;
                    S.pop();
                }
            }
        }
    }

    // Condition (2)
    for(boost::tie(vi, vi_end) = boost::vertices(G); vi != vi_end; ++vi){
        Vertex v = *vi;
        if ( label[v] == CYCLE ){
            Vertex w = v;
            long cycle_length = 0;
            do{ 
                Edge e = boost::edge(pred[w], w, G).first;
                cycle_length += costs[e];
                label[w] = NEG_CYCLE;
                w = pred[w];
            } while (w != v);
            if(!(cycle_length < 0)) return false;
        }
    }

    // Conditions (3), (4), and (5)
    if ( label[s] == FINITE ) 
        if(!(dist[s] == 0 )) return false;


    EdgeIterator ei, ei_end;
    for(boost::tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei){
        Vertex v = boost::source(*ei, G);
        Vertex w = boost::target(*ei, G);
        if ( label[w] == FINITE ){ 
            if( !(label[v] == FINITE || label[v] == PLUS) ) return false;
            if ( label[v] == FINITE ) {
                if( !( dist[v] + costs[*ei] >= dist[w] ) ) return false;
                if ( boost::source(*ei, G) == pred[w] )
                    if( !( dist[v] + costs[*ei] == dist[w] ) ) return false;
            }
        }
    }

    return true;
}


/**
 * Implements the DFS algorithm from 
 * a start Vertex.
 * 
 * @param &G The graph to search
 * @param s The starter vertex
 * @param &reachable The bool vector showing if reachable
 *
 */
void dfs(Graph &G, Vertex s, std::vector<bool> &reachable){
    reachable[s] = true;
    
    OutEdgeIterator ei, ei_end;
    for(boost::tie(ei, ei_end) = boost::out_edges(s, G); ei != ei_end; ++ei){
        Vertex w = boost::target(*ei, G);
        if(!reachable[w])
            dfs(G, w, reachable);
    }
}

