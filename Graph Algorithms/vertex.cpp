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

#include "vertex.h"
#include "edge.h"
#include <algorithm>

using namespace std;


Vertex::Vertex(const string &Label) : vertexLabel{Label} {
  Visit = false;
  reset();
}
// return next item in the map, returns vertexLabel if no more
// neighbors
string Vertex::getNextNeighbor() {
  string Result = vertexLabel;
  auto It = Neighbors.begin();
  auto Next = Neighbors.begin();
  if(It == Neighbors.end()){
    return Result;
  }
  It = Neighbors.end();
  It--;
  Result = Next->first;
  if(It->first != Next->first){
    Next++;
  }
  return Result;
}
//returns weight of particular edge of a string
int Vertex::getEWeight(const string &To) const{
  if(Neighbors.find(To) != Neighbors.end()){
    return Neighbors.at(To).getWeight();
  }
  return -1;
}
//returns size of map
int Vertex::getNum() const {
  return Neighbors.size();
}
//resets map to iterate from beginning
void Vertex::reset() {
  Curr = Neighbors.begin();
}
//returns vertex label
string Vertex::getVLabel() const {
  return vertexLabel;
}
//checks off item as unvisited
void Vertex::unVisit() {
  Visit = false;
}
// destructor clears out all items in map
Vertex::~Vertex() {
  Neighbors.clear();
}



