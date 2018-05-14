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
	double distanceFromS;
	Vertex pred;

	VertexProperties(){
	    pred = NULL;
        distanceFromS = std::numeric_limits<double>::infinity();
        //distanceFromS = std::numeric_limits<int>::max();
    }

};

struct EdgeProperties {
	double cost;

    EdgeProperties(){}

	EdgeProperties(int c){
	    cost = c;
	}

};

#endif
