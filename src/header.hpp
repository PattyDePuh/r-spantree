/* Header-File “header.hpp“: */
#ifndef HEADER_HPP
#define HEADER_HPP
#define DEBUG

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <istream>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <exception>
#include <queue>

using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::strtok;
using std::queue;

#define FAIL 99999999

//Strukturen
//Knoten im Graph
struct knoten_konstrukt{
	knoten_konstrukt(int id, int restriction): id(id), restriction(restriction) {};
	int id;
	int restriction;
};
//Kanten im Graph
struct kanten_konstrukt{
	kanten_konstrukt(int id, int start, int ziel, int cost, int result): id(id), start(start), ziel(ziel), cost(cost), result(result) {};
	int id;
	int start;
	int ziel;
	int cost;
	int result;
};

typedef kanten_konstrukt Kante;
typedef knoten_konstrukt Knoten;

#endif 
/* Ende HEADER_HPP */