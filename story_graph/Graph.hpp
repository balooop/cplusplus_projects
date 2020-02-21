#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
using std::list;
using std::unordered_map;
/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  //gets all adjacent 
  list<edgeListIter> adjacent = adjList.at(v.key());
  return adjacent.size();
}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  //inserts vertex in map
  vertexMap.emplace(key, v);
  //inserts a blank adjacency list with the key in map
  adjList.emplace(key, std::list<edgeListIter>(0));
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  for(auto it = adjList.at(key).begin(); it != adjList.at(key).end(); )
  {
    removeEdge(*(it++));
  }
  vertexMap.erase(vertexMap.find(key));
  adjList.erase(adjList.find(key));
  // //removes the vertex from the vertex map
  // vertexMap.erase(vertexMap.find(key));
  // //removes all adjacent edges 
  // //loops through edges
  // for(Edge e: edgeList)
  // {
  //   //if either source or destination is the vertex we are removing
  //   if(e.dest() == key || e.source() == key)
  //   {
  //     //we remove the edge
  //     removeEdge(e.source(), e.dest());
  //   }
  // }
  // //removes the adjacency list for the vertex being removed
  // adjList.erase(key);
}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  //inserts the edge at the end of the edgelist
  auto position = edgeList.insert(edgeList.end(), e);
  //inserts the position of the edge in the list for v1
  list<edgeListIter> & v1_adjacent = adjList.at(v1.key());
  v1_adjacent.push_back(position);
  //inserts the position of the edge in the list for v2
  list<edgeListIter> & v2_adjacent = adjList.at(v2.key());
  v2_adjacent.push_back(position);
  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {  
  // TODO: Part 2
  //removes adjacencies
  auto position = edgeList.begin();
  //loops through edge list
  Edge toCheck = Edge(key1, key2);
  for(Edge e : edgeList)
  {
    //if the edge is found
    if(e == toCheck)
    {
      //removes by iterator
      removeEdge(position);
      break;
    }
    position++;
  }
}


/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  //erases from edgelist
  edgeList.erase(it);
  //gets edge
  Edge remove = *it;
  //removes from source and dest's adjacency lists
  auto & src_list = adjList.at(remove.source().key());
  src_list.remove(it);
  auto & dest_list = adjList.at(remove.dest().key());
  dest_list.remove(it);
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>  
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  auto adj_list = adjList.at(key);
  for(auto e : adj_list)
  {
    edges.push_back(*e);
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  //gets incidence lists
  list<std::reference_wrapper<E>> key1_edges = incidentEdges(key1);
  list<std::reference_wrapper<E>> key2_edges = incidentEdges(key2);
  //creates an edge to compare against
  Edge toCheck = Edge(key1, key2);
  //loops through edges  
  for(Edge e : key1_edges)
  {
    if(e.dest() == toCheck.dest())  return true;
  }
  for(Edge e : key2_edges)
  {
    if(e.source() == toCheck.source())  return true;
  }
  return false;
}
