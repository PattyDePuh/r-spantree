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
    std::cout << "circle at node " << nodeIndex << " from " << sourceIndex << std::endl;
    return true;
  }
  visited[nodeIndex]++;

  for (std::vector<Kante>::iterator it = edges.begin(); it < edges.end(); it++) {
    if (it->start == nodeIndex && it->ziel != sourceIndex) {
      circleRecursive(it->ziel, nodes, edges, visited, finished, nodeIndex);
    }
    if (it->ziel == nodeIndex && it->start != sourceIndex) {
      circleRecursive(it->start, nodes, edges, visited, finished, nodeIndex);
    }
  }

  finished[nodeIndex]++;
  return false;
}

bool circle (std::vector<Knoten>* nodes, std::vector<Kante>& edges) {
  //int visited[nodes->size()] = {};
  //int finished[nodes->size()] = {};
  int visited[100] = {};
  int finished[100] = {};
  for (std::vector<Knoten>::iterator it = nodes->begin(); it < nodes->end(); it++) {
    std::cout << "It for node " << it->id << std::endl;
    circleRecursive(it->id, nodes, edges, visited, finished, it->id);
  }
  return false;
}

long optimize (std::vector<Knoten>* nodes, std::vector<Kante>* edges, int, int) {
  int i = 0;
  vector<Kante> tmpedges;
  //TODO think about sorting the other way
  std::sort(edges->begin(), edges->end(), edgeCompare);
  std::reverse(edges->begin(), edges->end());

  while (edges->size()) {
    tmpedges.push_back(*(edges->end()));
    edges->pop_back();
    circle(nodes, tmpedges);
  }
  return -1;
}
