#ifndef HEURISTIC_2_HPP
#define HEURISTIC_2_HPP

vector<Edge> result;

// comparator deciding if lhs has less cost than rhs
bool edgeCompare (Edge, Edge);

// tries to find path with minimal cost using modified Kruskal
long optimize (vector<Knoten>*, vector<Kante>*, int, int);

#endif
