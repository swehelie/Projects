/**
 * Testing BST - Binary Search Tree functions
 *
 * @author Yusuf Pisan
 * @date 19 Oct 2019
 */

#include "graph.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * Trying to avoid global variables,
 * by creating a singleton class with our visitor functions
 * stringstream SS contains the output from visitor
 */
class Tester {
public:
  Tester() = delete;
  // insert output to SS rather than cout, so we can test it
  static stringstream SS;
  static string getSs() { return SS.str(); }
  static void resetSs() { SS.str(string()); }
  // visitor function used for DFS and BFS
  static void labelVisitor(const string &Label) { SS << Label; }
  // visitor function used for edges for minimum spanning tree
  static void edgeVisitor(const string &From, const string &To, int Weight) {
    SS << "[" << From << To << " " << Weight << "]";
  }
};

// initialize the static variable
// NOLINTNEXTLINE
stringstream Tester::SS;

// convert a map to a string so we can compare it
template <typename K, typename L>
static string map2string(const map<K, L> &Mp) {
  stringstream Out;
  for (auto &P : Mp)
    Out << "[" << P.first << ":" << P.second << "]";
  return Out.str();
}
// tests extra functions in graph
void testGraphBasic() {
  Graph G;
  assert(G.add("a") && "add vertex a");
  assert(G.add("b") && "add vertex b");
  assert(G.add("c") && "add vertex c");
  assert(G.add("d") && "add vertex d");
  assert(G.add("e") && "add vertex e");
  assert(!G.add("b") && "b added twice");
  assert(G.connect("a", "b", 10) && "connect a b");
  assert(!G.connect("a", "b", 50) && "duplicate connect a b");
  assert(!G.connect("a", "a", 1) && "connect a to itself");
  G.connect("a", "d", 40);
  G.connect("a", "c", 20);
//  cout << "<< Vert: " << G.verticesSize() << endl;
  assert((G.verticesSize() == 5) && "graph number of vertices");
//  cout << "<< Edge: " << G.edgesSize() << endl;
  assert((G.edgesSize() == 3) && "graph number of edges");
  assert((G.neighborsSize("a") == 3) && "vertex number of edges");
  assert((G.neighborsSize("c") == 0) && "no outgoing edges c");
  assert((G.neighborsSize("xxx") == -1) && "no edges for xxx");
  assert(!G.contains("xxx") && "xxx not in graph");
  assert(G.contains("a") && "a in graph");

  // check that they are sorted based on edge end label
  assert(G.getEdgesAsString("a") == "b(10),c(20),d(40)");
//  // disconnect non-existent edge/vertex
  assert(!G.disconnect("a", "e") && "disconnecting non-existent vertex");
  assert((G.edgesSize() == 3) && "disconnected nonexisting");
  assert(G.disconnect("a", "c") && "a-c disconnect");
  assert((G.edgesSize() == 2) && "number of edges after disconnect");
  assert((G.neighborsSize("a") == 2) && "a has 2 edges");
  assert(G.getEdgesAsString("a") == "b(10),d(40)" && "removing middle edge");
  cout << "Test Basic Done!" << endl;
}
//tests dfs
void testGraph0DFS() {
  cout << "testGraph0DFS" << endl;
  Graph G;
  if (!G.readFile("graph0.txt"))
    return;
  assert(G.contains("A") && "a in graph");
  assert(G.contains("B") && "b in graph");
  assert(G.contains("C") && "c in graph");
  assert(G.getEdgesAsString("A") == "B(1),C(8)");
  assert(G.getEdgesAsString("B") == "C(3)");
  assert(G.getEdgesAsString("C").empty());

  Tester::resetSs();
  G.dfs("A", Tester::labelVisitor);
  assert(Tester::getSs() == "ABC" && "starting from A");

  Tester::resetSs();
  G.dfs("B", Tester::labelVisitor);
  assert(Tester::getSs() == "BC" && "starting from B");

  Tester::resetSs();
  G.dfs("C", Tester::labelVisitor);
  assert(Tester::getSs() == "C" && "starting from C");

  Tester::resetSs();
  G.dfs("X", Tester::labelVisitor);
  assert(Tester::getSs().empty() && "starting from X");
  cout << "Test DFS Done!" << endl;
}
//tests BFS
void testGraph0BFS() {
  cout << "testGraph0BFS" << endl;
  Graph G;
  if (!G.readFile("graph0.txt"))
    return;

  Tester::resetSs();
  G.bfs("A", Tester::labelVisitor);
  assert(Tester::getSs() == "ABC" && "starting from A");

  Tester::resetSs();
  G.dfs("B", Tester::labelVisitor);
  assert(Tester::getSs() == "BC" && "starting from B");

  Tester::resetSs();
  G.dfs("C", Tester::labelVisitor);
  assert(Tester::getSs() == "C" && "starting from C");

  Tester::resetSs();
  G.dfs("X", Tester::labelVisitor);
  assert(Tester::getSs().empty() && "starting from X");
  cout << "Test BFS Done!" << endl;
}
//tests dijkstra function
void testGraph0Dijkstra() {
  cout << "testGraph0Dijkstra" << endl;
  Graph G;
  if (!G.readFile("graph0.txt"))
    return;
  map<string, int> Weights;
  map<string, string> Previous;
  tie(Weights, Previous) = G.dijkstra("A");
  assert(map2string(Weights) == "[B:1][C:4]" && "Dijkstra(A) weights");
  assert(map2string(Previous) == "[B:A][C:B]" && "Dijkstra(A) previous");

  tie(Weights, Previous) = G.dijkstra("B");
  assert(map2string(Weights) == "[C:3]" && "Dijkstra(B) weights");
  assert(map2string(Previous) == "[C:B]" && "Dijkstra(B) previous");

  tie(Weights, Previous) = G.dijkstra("X");
  assert(map2string(Weights).empty() && "Dijkstra(C) weights");
  assert(map2string(Previous).empty() && "Dijkstra(C) previous");
  cout << "Test Dijkstra Done!" << endl;
}
//test undirected graph
void testGraph0NotDirected() {
  cout << "testGraph0NotDirected" << endl;
  bool IsDirectional = false;
  Graph G(IsDirectional);
  if (!G.readFile("graph0.txt"))
    return;

  Tester::resetSs();
  G.bfs("A", Tester::labelVisitor);
  assert(Tester::getSs() == "ABC" && "starting from A");

  Tester::resetSs();
  G.dfs("B", Tester::labelVisitor);
  assert(Tester::getSs() == "BAC" && "starting from B");

  Tester::resetSs();
  G.dfs("C", Tester::labelVisitor);
  assert(Tester::getSs() == "CAB" && "starting from C");

  Tester::resetSs();
  G.dfs("X", Tester::labelVisitor);
  assert(Tester::getSs().empty() && "starting from X");

//  map<string, int> Weights;
//  map<string, string> Previous;
//  tie(Weights, Previous) = G.dijkstra("A");
//   cout << "Dijkstra(A) weights is " << map2string(Weights) << endl;
////  cout << Tester::getSs() << endl;
//  assert(map2string(Weights) == "[B:1][C:4]" && "Dijkstra(A) weights");
//   cout << "Dijkstra(A) previous is " << map2string(Previous) << endl;
//  assert(map2string(Previous) == "[B:A][C:B]" && "Dijkstra(A) previous");
////
//  tie(Weights, Previous) = G.dijkstra("B");
//  cout << "Dijkstra(B) weights is " << map2string(Weights) << endl;
//  assert(map2string(Weights) == "[A:1][C:3]" && "Dijkstra(B) weights");
//  cout << "Dijkstra(B) previous is " << map2string(Previous) << endl;
//  assert(map2string(Previous) == "[A:B][C:B]" && "Dijkstra(B) previous");
//
//  tie(Weights, Previous) = G.dijkstra("X");
//  assert(map2string(Weights).empty() && "Dijkstra(C) weights");
//  assert(map2string(Previous).empty() && "Dijkstra(C) previous");

//  Tester::resetSs();
//  int MstLength = G.mst("A", Tester::edgeVisitor);
////  cout << MstLength << endl;
//  assert(MstLength == 4 && "mst A is 4");
////  cout << Tester::getSs() << endl;
//  assert(Tester::getSs() == "[AB 1][BC 3]" && "mst A is [AB 1][BC 3]");
//
//  Tester::resetSs();
//  MstLength = G.mst("B", Tester::edgeVisitor);
//  assert(MstLength == 4 && "mst 4 is 4");
//  assert(Tester::getSs() == "[BA 1][BC 3]");
//
//  Tester::resetSs();
//  MstLength = G.mst("C", Tester::edgeVisitor);
//  assert(MstLength == 4 && "mst C is 4");
//  cout << MstLength << endl;
//  cout << Tester::getSs() << endl;
//  assert(Tester::getSs() == "[CB 3][BA 1]");
//
//  Tester::resetSs();
//  MstLength = G.mst("X", Tester::edgeVisitor);
//  assert(MstLength == -1 && "mst X is -1");
//  assert(Tester::getSs().empty() && "mst for vertex not found");
  cout << "Test Not Directed Done!" << endl;
}
//tests graph1
void testGraph1() {
  cout << "testGraph1" << endl;
  Graph G;
  if (!G.readFile("graph1.txt"))
    return;
  Tester::resetSs();
  G.dfs("A", Tester::labelVisitor);
  assert(Tester::getSs() == "ABCDEFGH" && "dfs starting from A");
//  cout << Tester::getSs() << endl;


  Tester::resetSs();
  G.bfs("A", Tester::labelVisitor);
  assert(Tester::getSs() == "ABHCGDEF" && "bfs starting from A");
//  cout << Tester::getSs() << endl;

  Tester::resetSs();
  G.dfs("B", Tester::labelVisitor);
  assert(Tester::getSs() == "BCDEFG" && "dfs starting from B");

  Tester::resetSs();
  G.bfs("B", Tester::labelVisitor);
  assert(Tester::getSs() == "BCDEFG" && "bfs starting from B");
  cout << "Test Graph Done!" << endl;
}

void testAll() {
  testGraphBasic();
  testGraph0DFS();
  testGraph0BFS();
  testGraph0Dijkstra();
  testGraph0NotDirected();
  testGraph1();
}
