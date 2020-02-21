#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <iostream>
using namespace std;
 
 
inline void totalPaths(list<string> & currPath, vector<list<string>> & paths, unordered_map<string, list<string>> & predecessor, string prev, string end, unordered_map<string, bool> seen){
 
  seen.insert({prev, true});
  list<string> options = predecessor[prev];
 
 
  if (find (options.begin(), options.end(), end) != options.end()){
    currPath.push_back(end);
    paths.push_back(currPath);
    return;
  }
  for (string option : options){
    if (seen.find(option) != seen.end()){
      continue;
    }
    currPath.push_back(option);
    totalPaths(currPath, paths, predecessor, option, end, seen);
    currPath.pop_back();
  }
}
 
/**
 * Returns an list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
list<string> Graph<V,E>::shortestPath(const string start, const string end) {
  // TODO: Part 3
  unordered_map<string, bool> seen;
  unordered_map<string, list<string>> predecessor;
 
  queue <string> bfs;
 
  list<string> first;
  predecessor.emplace(start, first);
 
  bfs.push(start);
 
  while(!bfs.empty()){
    list<edgeListIter> edgesIts = adjList.at(bfs.front()); //takes next vertex from queue and gets all edges connected to it
    list<Edge> edges;
    for (edgeListIter it : edgesIts){
      edges.push_back(*it); //pushes back all incident edges to a vector
    }
    //below pushes any vertices not already seen into the queue
    for (Edge edge : edges){
      string s;
      string d;
 
      if (seen.find(edge.dest().key()) == seen.end()){
        seen.emplace(edge.dest().key(), true);
        bfs.push(edge.dest().key());
        s = edge.source().key();
        d = edge.dest().key();
      }
 
      if (seen.find(edge.source().key()) == seen.end()){
        seen.emplace(edge.source().key(), true);
        bfs.push(edge.source().key());
        s = edge.source().key();
        d = edge.dest().key();
      }
 
 
      if (predecessor.find(d) == predecessor.end()){
        list<string> previous;
        previous.push_back(s);
        predecessor.emplace(d, previous);
      }
      else
      {
        predecessor[d].push_back(s);
      }
     
      if (predecessor.find(s) == predecessor.end()){
        list<string> previous;
        previous.push_back(d);
        predecessor.emplace(s, previous);
      }
      else
      {
        predecessor[s].push_back(d);
      }
    }
    bfs.pop();
  }
// up to here, we now have predecessor that stores the edges as a map, now to figure out how to get all possible paths to end
  list<string> path1;
  path1.push_back(end);
  list<string> pred = predecessor[end];
 
 
  vector<list<string>> allPaths;
  list<string> path;
  path.push_back(start);
  string one = start;
  string second = end;
  unordered_map<string, bool> seenMap;
  totalPaths(path, allPaths, predecessor, one, second, seenMap);
 
 
  list<string> ret;
  if (allPaths.size() == 0){
    return ret;
  }
  ret = allPaths[0];
 
  if (allPaths.size() == 1){
    return ret;
  }
  for (unsigned i = 1; i < allPaths.size(); i++){
    if (allPaths[i].size() < ret.size()){
      ret = allPaths[i];
    }
  }
 
  return ret;
}
