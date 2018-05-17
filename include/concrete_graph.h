#ifndef CON_GRAPH_H
#define CON_GRAPH_H

#include <boost/graph/adjacency_list.hpp>

enum class VertexLabel {Vminus = -1, Vf = 0, Vplus = 1};
//std::string labelNames[] = {"Vminus", "Vf", "Vplus"};


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

#endif
