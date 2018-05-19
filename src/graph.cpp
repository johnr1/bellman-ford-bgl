#include "../include/graph.h"
#include <LEDA/graph/graph.h>


/**
 * Convert a BOOST Graph (as typedefed) into a LEDA
 * parameter GRAPH and returns it.
 * NodeInfo: Vertex Index as is in Graph
 * EdgeInfo: Edge Cost as is in Graph
 *
 * @param BG The boost Graph to transform
 * @return The converted LEDA parameter GRAPH
 */
leda::GRAPH<unsigned, long> boostToLeda(const Graph &BG){
	unsigned long n = boost::num_vertices(BG);
	leda::GRAPH<unsigned , long> LG;
	std::vector<leda::node> insertedNodes(n);

	VertexIterator vi, vi_end;
	for(boost::tie(vi, vi_end) = vertices(BG); vi != vi_end; ++vi){
		leda::node v = LG.new_node(*vi);
		insertedNodes[*vi] = v;
	}


	EdgeIterator ei, ei_end;
	leda::node v1, v2;
	for(boost::tie(ei, ei_end) = edges(BG); ei != ei_end; ++ei){
		Vertex vSource = boost::source(*ei, BG);
		Vertex vTarget = boost::target(*ei, BG);

		v1 = insertedNodes[vSource];
		v2 = insertedNodes[vTarget];

		LG.new_edge(v1, v2, BG[*ei].cost);
	}

	return LG;
}

/**
 * Translates the GraphType enum to
 * std::string;
 * 
 * @gt The GraphType class enum
 * @return The string corrisponding to that graph type
 * 
 */
std::string graphName(GraphType gt){
	switch(gt) {
        case GraphType::random : return "Random";
        case GraphType::grid : return "Grid";
    }
	return "ERR";
}

