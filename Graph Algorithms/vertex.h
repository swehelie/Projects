/**
 * A Graph is made up of Vertex objects that hold data values
 * A vertex is connected to other vertices via Edges
 * A vertex can be visited/unvisited
 * Can connect to another vertex via directed edge with weight
 * The edge can be disconnected
 * A vertex cannot have an edge back to itself
 * getNextNeighbor returns the next neighbor each time it is called
 * when there are no more neighbors, the vertex label is returned
 */

#ifndef VERTEX_H
#define VERTEX_H

//#include "edge.h"
#include <string>
#include <vector>
#include <map>

//#include "edge.h"

using namespace std;
class Edge;
class Vertex {
  friend class Graph;
  friend class Edge;

public:
  /** Creates an unvisited vertex, gives it a label, and clears its
      adjacency list.
      NOTE: A vertex must have a unique label that cannot be changed. */
  explicit Vertex(const string &Label);

  /** Destructor. Delete all edges from this vertex to other vertices */
  ~Vertex();
  //returns vertex label
  string getVLabel() const;
  //checks off item as unvisited
  void unVisit();
  // return next item in the map, returns vertexLabel if no more
  // neighbors
  string getNextNeighbor();
  //returns weight of particular edge of a string
  int getEWeight(const string &To) const;
   //resets map to iterate from beginning
   void reset();
   //returns size of map
   int getNum() const;

private:
    //vertex label
    string vertexLabel;
    //holds string as keys and edge objects
    map<string, Edge> Neighbors;
    //iterator for map
    map<string, Edge>::iterator Curr;
    //true if visited, false if not
    bool Visit;

};

#endif  //  ASS3_GRAPHS_VERTEX_H
