#include <vector>

#include "../include/bellman_ford.h"
#include "../include/concrete_graph.h"


bool bellman_ford(const Graph &G,
								const std::vector<int> &costs,
								std::vector<int> &dist,
								std::vector<Vertex> &pred)
{
	long n = boost::num_vertices(G);
	long phase_count = 0;

	return false;
}






std::vector<VertexLabel> labelVertices(Graph &G, bool no_cycle, std::vector<int> dist, std::vector<Vertex> pred){
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