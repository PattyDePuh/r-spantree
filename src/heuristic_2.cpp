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
    //std::cout << "circle at node " << nodeIndex << " from " << sourceIndex << std::endl;
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
  int* visited = new int[nodes->size()];
  int* finished = new int[nodes->size()];
  for (std::vector<Knoten>::iterator it = nodes->begin(); it < nodes->end(); it++) {
    //std::cout << "It for node " << it->id << std::endl;
    if (circleRecursive(it->id, nodes, edges, visited, finished, it->id)) {
      delete[] visited;
      delete[] finished;
      return true;
    }
  }
  delete[] visited;
  delete[] finished;
  return false;
}

long optimize (std::vector<Knoten>* nodes, std::vector<Kante>* edges, int, int) {
  long bestcost = 0;
  vector<Kante> tmpedges;
  // sort the edges by their cost
  std::sort(edges->begin(), edges->end(), edgeCompare);

  int* reached = new int[nodes->size()];

  int* degree = new int[nodes->size()];
  for (unsigned int i = 0; i < nodes->size(); i++) {
    degree[i] = (*nodes)[i].restriction;
    reached[i] = 0;
    //std::cout << "degree:" << degree[i] << " ";
  }

  for (unsigned int i = 0; i < edges->size(); i++) {
    tmpedges.push_back((*edges)[i]);
    if (circle(nodes, tmpedges) || degree[(*edges)[i].start] == 0 || degree[(*edges)[i].ziel] == 0) {
      tmpedges.pop_back();
      (*edges)[i].result = 0;
    }
    else {
      (*edges)[i].result = 1;
      degree[(*edges)[i].start]--;
      degree[(*edges)[i].ziel]--;
      reached[(*edges)[i].start] = 1;
      reached[(*edges)[i].ziel] = 1;
      bestcost += (*edges)[i].cost;
    }
  }

  unsigned int reachedsum = 0;
  for (unsigned int i = 0; i < nodes->size(); i++) {
    reachedsum += reached[i];
  }

  delete[] degree;
  delete[] reached;
  //std::cout << "reachedsum:" << reachedsum << " nodessize:" << nodes->size() << std::endl;
  if (reachedsum == nodes->size()) {
    return bestcost;
  }
  else {
    return -1;
    //return bestcost;
  }
}
