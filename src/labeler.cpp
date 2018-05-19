#include "../include/labeler.h"

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


leda::node_array<VertexLabel> ledaLabelVertices(leda::GRAPH<unsigned,int> &G, bool no_cycle, leda::node s, leda::node_array<leda::edge> &pred){
    leda::node_array<VertexLabel> labels(G);

    leda::node v;
    forall_nodes(v, G){
        // If dist = inf
        if(pred[v] == nil && v != s){
            labels[v] = VertexLabel::Vplus;
            continue;
        }

        if(no_cycle){
            labels[v] = VertexLabel::Vf;
            continue;
        }

        leda::node_array<bool> reachable(G);
        leda::node cur = v;
        reachable[cur] = true;
        while(true){
            // if pred == null (symbolized as parent==self)
            if(pred[cur] == nil){
                labels[v] = VertexLabel::Vf;
                break;
            }
                // if we saw same vertex, reachable from neg cycle
            else if(reachable[G.source(pred[cur])]){
                labels[v] = VertexLabel::Vminus;
                break;
            }

            reachable[cur] = true;
            cur = G.source(pred[cur]);
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
