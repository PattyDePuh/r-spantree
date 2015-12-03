/* Header-File heuristic_1.hpp */
#ifndef HEURISTIC_1_HPP
#define HEURISTIC_1_HPP

typedef struct queItem QueItem;

struct queItem{
	queItem(int index, int cost) : index(index) , cost(cost){}
	int index;
	long cost;
};

class CompareItem {
    public:
    bool operator()(QueItem& item1, QueItem& item2) // Returns true if item1 is greater than item2
    {
       return item1.cost > item2.cost ? true: false;
    }
};

std::priority_queue<QueItem, vector<QueItem>, CompareItem> pq;

long optimize(vector<Knoten>* knotenliste, vector<Kante>* kantenliste, int anzahl_knoten, int anzahl_kanten);

bool recursiv_solver(vector<Knoten>* knotenliste, vector<Kante>* kantenliste, int& anzahl_knoten, int& anzahl_kanten,
					int incidente_array[], int restriction_array[], int verbunden_array[], int current_solution[], 
					int locked_edge[], long& current_cost);

#endif