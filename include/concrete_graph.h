#ifndef CON_GRAPH_H
#define CON_GRAPH_H

#include <boost/graph/adjacency_list.hpp>

// Forward declaration
struct VertexProperties;
struct EdgeProperties;


typedef boost::adjacency_list<boost::vecS,
							boost::vecS, 
							boost::directedS, 
							VertexProperties, 
							EdgeProperties> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIterator;

struct VertexProperties{
	int distanceFromS;
	Vertex pred;
};

struct EdgeProperties {
	int cost;
};

#endif
