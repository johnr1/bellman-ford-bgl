#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <LEDA/graph/graph.h>

enum class GraphType {random, grid};
enum{ NEG_CYCLE = -2, ATT_TO_CYCLE = -1, FINITE = 0, PLUS = 1, CYCLE = 2, ON_CUR_PATH = 3, UNKNOWN = 4 };


// ===== CONCRETE GRAPH STRUCTURE =====
struct EdgeProperties {
	int cost;

	EdgeProperties() = default;
	explicit EdgeProperties(int c) : cost(c){}
};

typedef boost::adjacency_list<boost::vecS,
							boost::vecS, 
							boost::directedS, 
							boost::no_property,
							EdgeProperties> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;
typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIterator;

typedef boost::property_map<Graph, int EdgeProperties::*>::type CostPropertyMap;




// ===== FUNCTIONS =====
leda::GRAPH<unsigned, long> boostToLeda(const Graph &);
std::string graphName(GraphType gt);
std::string labelName(int);



#endif
