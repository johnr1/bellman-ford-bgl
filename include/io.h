#ifndef IO_H
#define IO_H

#include "../include/concrete_graph.h"

class myEdgeWriter {
private:
    Graph G;

public:
    explicit myEdgeWriter(const Graph &g) : G(g) {}

    void operator()(std::ostream& out, const Edge& e) const {
        out << "[label=\"" << G[e].cost << "\"]";
    }
};

#endif
