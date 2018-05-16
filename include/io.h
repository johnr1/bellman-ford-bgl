#ifndef IO_H
#define IO_H

#include "../include/concrete_graph.h"

// SIMPLE COST WRITER
class CostEdgeWriter {
private:
    Graph G;

public:
	explicit CostEdgeWriter(const Graph &g) : G(g) {}

    void operator()(std::ostream& out, const Edge& e) const {
        out << "[label=\"" << G[e].cost << "\"]";
    }
};



// BF WRITER
template < typename Graph, typename ParentMap >
struct edge_writer
{
  edge_writer(const Graph & g, const ParentMap & p)
  : m_g(g), m_parent(p)
  {
  }

  template < typename Edge >
	void operator() (std::ostream & out, const Edge & e) const
  {
	out << "[label=\"" << get(&EdgeProperties::cost, m_g, e) << "\"";
	typename boost::graph_traits < Graph >::vertex_descriptor
	  u = source(e, m_g), v = target(e, m_g);
	if (m_parent[v] == u)
		out << ", color=\"black\"";
	else
		out << ", color=\"grey\"";
	  out << "]";
  }
  const Graph & m_g;
  ParentMap m_parent;
};

#endif
