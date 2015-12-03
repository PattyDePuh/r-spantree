#include <algorithm>
#include <vector>
#include <iostream>

#include "header.hpp"
#include "heuristic_2.hpp"

bool edgeCompare (Kante l, Kante r) {
  return l.cost < r.cost;
}

bool circleRecursive(int nodeIndex, std::vector<Knoten>* nodes, std::vector<Kante>& edges, int* visited, int* finished, int sourceIndex) {
  if (finished[nodeIndex]) {
    return false;
  }
  if (visited[nodeIndex]) {
    return true;
  }
  visited[nodeIndex]++;

  for (std::vector<Kante>::iterator it = edges->begin(); it < edges->end(); it++) {
    if (it->start == nodesIndex && it->ziel) {
      circleRecursive(it, edges, visited, finished, node);
    }
  }

  finished[nodeIndex]++;
  return false;
}

bool circle (std::vector<Knoten>* nodes, std::vector<Kante>& edges) {
  int visited[nodes.size()] = {};
  int finished[nodes.size()] = {};
  for (std::vector<Knoten>::iterator it = nodes->begin(); it < nodes->end(); it++) {
    circleRecursive(it->id, nodes, edges, visited, finished, it->id);
  }
  return false;
}

long optimize (std::vector<Knoten>* nodes, std::vector<Kante>* edges, int, int) {
  //TODO think about sorting the other way
  std::sort(edges->begin(), edges->end(), edgeCompare);
  std::reverse(edges.begin(), edges.end());

  while (edges.size()) {
    Kante* e = edges.end();
    result.push_back(e);
    if (circle(nodes, result));
  }

  return -1;
}
