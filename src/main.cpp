#include <iostream>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>

#include "../include/concrete_graph.h"
#include "../include/graph_gen.h"

class myEdgeWriter {
private:
    Graph G;

public:
    explicit myEdgeWriter(const Graph &g) : G(g) {}

    void operator()(std::ostream& out, const Edge& e) const {
        out << "[label=\"" << G[e].cost << "\"]";
    }
};

class myVertexWriter {
private:
    Graph G;

public:
    explicit myVertexWriter(const Graph &g) : G(g) {}

    void operator()(std::ostream& out, const Vertex& v) const {
        out << "[label=\"" << G[v].distanceFromS << "\"]";
    }
};




int main(int argc, char* argv[]) {
	Graph G = myGridGraph(9);
	boost::print_graph(G);

	myVertexWriter mvw(G);
    myEdgeWriter mew(G);
	std::ofstream f("graph.txt");
	//boost::write_graphviz(f, G, mvw, mew);
	boost::write_graphviz(f, G);

	f.close();
	return 0;

}
