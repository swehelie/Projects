#include "graph.h"
#include "edge.h"
#include <algorithm>
#include <cassert>
#include <map>
#include <utility>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// constructor, empty graph
Graph::Graph(bool DirectionalEdges)  {
  Directional = DirectionalEdges;
//  Vertices.clear();
}
/** destructor, delete all vertices and edges */
Graph::~Graph() {
  for(auto & I : Vertices){
    delete I.second;
  }
  Vertices.clear();
}

// Read edges from file
// first line of file is an integer, indicating number of edges
// each line represents an edge in the form of "string string int"
// vertex labels cannot contain spaces
// @return true if file successfully read
bool Graph::readFile(const string &Filename) {
  int Edge, Weight;
  string From, To;
  ifstream inFile(Filename);
  if(!inFile.is_open()){
    cerr << "Failure to open" << Filename << endl;
    return false;
  }
  inFile >> Edge;
  for (int I = 0; I < Edge; I++){
    inFile >> From >> To >> Weight;
    this->add(From);
    this->add(To);
    connect(From, To, Weight);
  }
  inFile.close();
  return true;
}

// @return total number of vertices
int Graph::verticesSize() const { return Vertices.size(); }

// @return total number of edges
int Graph::edgesSize() const {
  int num = 0;
  map<string, Vertex *>::const_iterator I;
  for(I = Vertices.begin(); I != Vertices.end(); I++){
    Vertex *Temp = I->second;
    num += Temp->Neighbors.size();
  }
  return num;
}

// @return number of edges from given vertex, -1 if vertex not found
int Graph::neighborsSize(const string &Label) const {
  int numV = -1;
  if(contains(Label)){
    Vertex *Temp = Vertices.find(Label)->second;
    numV = Temp->Neighbors.size();
  }
  return numV;
}

// @return true if vertex added, false if it already is in the graph
bool Graph::add(const string &Label) {
  if(!contains(Label)){
    Vertex *newV = new Vertex(Label);
    Vertices[Label] = newV;
    return true;
  }
  return false;
}

/** return true if vertex already in graph */
bool Graph::contains(const std::string &Label) const {
  return Vertices.count(Label) > 0;
}

// @return string representing edges and weights, "" if vertex not found
// A-3->B, A-5->C should return B(3),C(5)
string Graph::getEdgesAsString(const string &Label) const {
  string Edge;
  if(!contains(Label) || neighborsSize(Label) <= 0){
    return Edge;
  }
  if(contains(Label)){
    Vertex *Temp = Vertices.at(Label);
    string First;
    string Second;
    for(auto & I : Temp->Neighbors){
      First = I.first;
      Second = "(" + to_string(I.second.vWeight) + "),";
      Edge += First + Second;
    }
    Edge.erase(Edge.end()-1);
    return Edge;
  }
  return Edge;
}

// Add an edge between two vertices, create new vertices if necessary
// A vertex cannot connect to itself, cannot have P->P
// For digraphs (directed graphs), only one directed edge allowed, P->Q
// Undirected graphs must have P->Q and Q->P with same weight
// @return true if successfully connected
bool Graph::connect(const string &From, const string &To, int Weight) {
  Vertex *FromP = Vertices.at(From);
  Vertex *ToP = Vertices.at(To);
  if (From == To || !contains(From) || !contains(To) || Weight < 0) {
    return false;
  }
    if(!Directional) {
    Edge NewEdge(FromP, ToP, Weight);
    Edge NewEdge2(ToP, FromP, Weight);
    pair<string, Edge> EdgeToAdd (To, NewEdge);
    FromP->Neighbors.insert(EdgeToAdd);
    pair<string, Edge> EdgeToAdd2 (From, NewEdge2);
    ToP->Neighbors.insert(EdgeToAdd2);
    return true;
  }
    else {
      if (FromP->Neighbors.find(To) == FromP->Neighbors.end()) {
        Edge NewEdge(FromP, ToP, Weight);
        pair<string, Edge> EdgeToAdd(To, NewEdge);
        FromP->Neighbors.insert(EdgeToAdd);
        return true;
      }
      return false;
    }
}

// Remove edge from graph
// @return true if edge successfully deleted
bool Graph::disconnect(const string &From, const string &To) {
  if (From == To || !contains(From) || !contains(To)) {
    return false;
  }
  Vertex *Temp1 = Vertices.at(From);
  Vertex *Temp2 = Vertices.at(To);
  if(!Directional){
    if(Temp1->Neighbors.count(To) == 1 && Temp2->Neighbors.count(To) == 1){
      delete Vertices.at(From);
      delete Vertices.at(To);
      Temp1->Neighbors.erase(To);
      Temp2->Neighbors.erase(From);
      return true;
    }
  }
  else{
    if(Temp1->Neighbors.count(To) == 1 && Temp2->Neighbors.count(From) != 1){
      Temp1->Neighbors.erase(To);
      return true;
    }
    return false;
  }
  return false;
}

// depth-first traversal starting from given startLabel
void Graph::dfs(const string &StartLabel, void Visit(const string &Label)) {
//  this->unVisitNeighbor();
  visited.clear();
  DFSHelper(StartLabel, Visit);

}
//dfs helper, called in dfs function
void Graph::DFSHelper(const string &StartLabel,
        void Visit(const string &Label)) {
  if(contains(StartLabel)){
    Vertex *Temp = Vertices.at(StartLabel);
    if(visited.count(StartLabel) == 0){
      Visit(StartLabel);
      visited.insert(StartLabel);
      for(auto & I : Temp->Neighbors){
        string Result = I.first;
        if(visited.count(Result) == 0){
          DFSHelper(Result, Visit);
        }
      }
    }
  }
}


// breadth-first traversal starting from startLabel
// call the function visit on each vertex label */
void Graph::bfs(const string &StartLabel, void Visit(const string &Label)) {
  this->unVisitNeighbor();
  queue<Vertex *> myQ;
  Vertex *Curr = Vertices.at(StartLabel);
  myQ.emplace(Curr);
  Curr->Visit = true;
  Visit(Curr->getVLabel());
  while(!myQ.empty()){
    Vertex *Next = myQ.front();
    myQ.pop();
    for(const auto& I : Next->Neighbors){
      Vertex *To = I.second.V2;
      if(!To->Visit){
        myQ.emplace(To);
        Visit(To->getVLabel());
        To->Visit = true;
      }
    }
  }
}
//checks off all items in map as unvisited
void Graph::unVisitNeighbor() {
  map<string, Vertex*>::iterator It = Vertices.begin();
  while(It != Vertices.end()){
    It->second->unVisit();
    It->second->reset();
    It++;
  }
}
// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &StartLabel) const{
  map<string, int> Weights;
  map<string, string> Previous;
  Weights.clear();
  Previous.clear();
  if(contains(StartLabel)) {
    Vertex *Temp = Vertices.at(StartLabel);
    int numNeighbors = neighborsSize(StartLabel);
    typedef pair<int, string> iPair;
    string U = "";
    string V = "";
    int vNeighbors = 0;
    int Cost = 0;
    priority_queue<iPair, vector<iPair>, greater<> > pq;
    set<string> vSet;
    for (int I = 0; I < numNeighbors; I++) {
      U = Temp->getNextNeighbor();
      Weights[U] = Temp->getEWeight(U);
      Previous[U] = StartLabel;
      pq.push(iPair(Weights[U], U));
    }
    vSet.insert(Temp->getVLabel());
    while (!pq.empty()) {
      V = pq.top().second;
      vSet.insert(Vertices.at(V)->getVLabel());
      pq.pop();
      if (vSet.find(V) != vSet.end()) {
        vNeighbors = neighborsSize(V);
        U = Vertices.at(V)->getNextNeighbor();
        for (int K = 0; K < vNeighbors; K++) {
          if (vSet.count(U) > 0) {
            U = Vertices.at(V)->getNextNeighbor();
            continue;
          }
          Cost = Vertices.at(V)->getEWeight(U);
          if (Weights.find(U) == Weights.end()) {
            Weights[U] = Weights[V] + Cost;
            Previous[U] = V;
            pq.push(iPair(Weights[U], U));
          } else {
            if (Weights[U] > (Weights[V] + Cost)) {
              Weights[U] = Weights[V] + Cost;
              Previous[U] = V;
              pq.push(iPair(Weights[U], U));
            }
          }
          U = Vertices.at(V)->getNextNeighbor();
        }
      }
    }
  }
  return make_pair(Weights, Previous);
}

/**
 * minimum spanning tree
 * @param function to be called on each edge
 * @return length of the minimum spanning tree or -1 if start vertex not found
 */
int Graph::mst(const string &StartLabel,
               void Visit(const string &From, const string &To,
                          int Weight)) const {
  assert(!Directional);
  if(!contains(StartLabel)){
    return -1;
  }
  map<string, bool> Check;
  return mstHelper(StartLabel, Visit, Check);
}
// minimum time span helper :: incomplete
int Graph::mstHelper(const string &StartLabel,
                     void Visit(const string &From, const string &To,
                                int Weight),
                     map<string, bool> &Check) const{
  Check.emplace(StartLabel, true);
  int Size = Vertices.at(StartLabel)->Neighbors.size();
  for(int I=0; I < Size; I++){
    string Result = Vertices.at(StartLabel)->vertexLabel;
    if(Check.find(Result) == Check.end()){
      int Weight = Vertices.at(StartLabel)->getEWeight(StartLabel);
      Visit(StartLabel, Result, Weight);
      return Weight + mstHelper(Result, Visit, Check);
    }
  }
  return 0;
}
