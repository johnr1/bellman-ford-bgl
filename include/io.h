#ifndef IO_H
#define IO_H

#include "../include/graph.h"

// BF WRITER
struct MyEdgeWriter 
{
  const Graph & mG;
  std::vector<Vertex> mPred;

  MyEdgeWriter(const Graph &G, const std::vector<Vertex> &pred)
  : mG(G), mPred(pred){}


	void operator() (std::ostream & out, const Edge & e) const {
    out << "[label=\"" << get(&EdgeProperties::cost, mG, e) << "\"";

    Vertex u = boost::source(e, mG);
    Vertex v = boost::target(e, mG);
    if (mPred[v] == u)
      out << ", color=\"black\"";
    else
      out << ", color=\"grey\"";
      out << "]";
  }

};

#endif
