/**
 * Edge is the simplest structure of the graph
 * All edges are directed
 * Each edge belongs to a vertex
 */

#include "edge.h"

//default constructor
Edge::Edge(Vertex *From, Vertex *To, int Weight) : V1(From),
V2(To), vWeight(Weight) {
}
//returns weight of edge
int Edge::getWeight() const{
  return vWeight;
}
