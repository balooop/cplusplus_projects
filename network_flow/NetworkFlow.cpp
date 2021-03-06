/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  maxFlow_ = 0;
  //gets vertices and edges
  vector<Vertex> v_set = g_.getVertices();
  vector<Edge> e_set = g_.getEdges();  
  //inserts all vertices
  for(Vertex v : v_set)
  {
    flow_.insertVertex(v);
    residual_.insertVertex(v);
  }
  for(Edge e : e_set)
  {
    //inserts edges into graphs
    flow_.insertEdge(e.source, e.dest);
    residual_.insertEdge(e.source, e.dest);
    residual_.insertEdge(e.dest, e.source);
    //sets weights
    flow_.setEdgeWeight(e.source, e.dest, 0);
    residual_.setEdgeWeight(e.source, e.dest, e.getWeight());
    residual_.setEdgeWeight(e.dest, e.source, 0);
  }

  
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  
  //sets min edge to first edge
  int min = residual_.getEdge(path[0], path[1]).getWeight();

  //loops through other vertices
  for(unsigned i = 1; i < path.size() - 1; i++)
  {
    //gets weight
    int cur_weight = residual_.getEdge(path[i], path[i+1]).getWeight();
    (cur_weight < min) ? min = cur_weight : cur_weight += 0;
  }
  return min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  vector<Vertex> path;
  int total_capacity = 0;
  while(findAugmentingPath(source_, sink_, path) != false)
  {
    //int capacity = pathCapacity(path);
    auto tmp = pathCapacity(path);
    total_capacity += pathCapacity(path);
    for(unsigned i = 0; i < path.size() - 1; i++)
    {
      if(flow_.edgeExists(path[i], path[i+1]))
      {
        flow_.setEdgeWeight(path[i], path[i+1], flow_.getEdge(path[i], path[i+1]).getWeight() + tmp);
      }
      else
      {
        flow_.setEdgeWeight(path[i+1], path[i], flow_.getEdge(path[i], path[i+1]).getWeight() - tmp);
      }
      residual_.setEdgeWeight(path[i], path[i+1], residual_.getEdge(path[i], path[i+1]).getWeight() - tmp);
      residual_.setEdgeWeight(path[i+1], path[i], residual_.getEdge(path[i+1], path[i]).getWeight() + tmp);
    }
  }
  maxFlow_ = total_capacity;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

