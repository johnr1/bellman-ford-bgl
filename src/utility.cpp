#include "../include/utility.h"
#include "../include/concrete_graph.h"
#include <LEDA/graph/graph.h>

/**
 * Convert a BOOST Graph (as typedefed) into a parametarized
 * LEDA GRAPH and returns it.
 * NodeInfo: Vertex Index as is in Graph
 * EdgeInfo: Edge Cost as is in Graph
 *
 *	@param BG The boost Graph to transform
 * @return The converted parametarized LEDA GRAPH
 */
leda::GRAPH<unsigned long, long> boostToLeda(const Graph &BG){
	unsigned long n = boost::num_vertices(BG);
	leda::GRAPH<unsigned long, long> LG;
	std::vector<leda::node> insertedNodes(n, nil);

	EdgeIterator ei, ei_end;
	leda::node v1;
	leda::node v2;
	for(boost::tie(ei, ei_end) = edges(BG); ei != ei_end; ++ei){
		Vertex vSource = boost::source(*ei, BG);
		Vertex vTarget = boost::target(*ei, BG);

		v1 = insertedNodes[vSource];
		if( v1 == nil){
			v1 = LG.new_node(vSource);
			insertedNodes[vSource] = v1;
		}

		v2 = insertedNodes[vTarget];
		if( v2 == nil ){
			v2 = LG.new_node(vTarget);
			insertedNodes[vTarget] = v2;
		}

		LG.new_edge(v1, v2, BG[*ei].cost);
	}

	return LG;
}
