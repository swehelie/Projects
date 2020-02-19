/**
 * Edge is the simplest structure of the graph
 * All edges are directed
 * Each edge belongs to a vertex
 */
#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

// forward declaration for class Vertex
class Vertex;

class Edge {
  friend class Vertex;
  friend class Graph;
 private:
  /** constructor with label and weight */
   Edge(Vertex *From, Vertex *To, int Weight);
   // returns weight of edge
   int getWeight() const;
   // Vertices pointer
   Vertex *V1, *V2;
   // weight of edge
   int vWeight;
};

#endif
