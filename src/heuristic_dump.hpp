/* Header-File heuristic_dump.hpp */
#ifndef HEURISTIC_DUMP_HPP
#define HEURISTIC_DUMP_HPP

long optimize(vector<Knoten>* knotenliste, vector<Kante>* kantenliste, int anzahl_knoten, int anzahl_kanten);
void kante_setzen(int current_solution[], int kante_untersucht[], int incidente_array[], int restriction_array[], std::vector<Kante>* kantenliste, long* current_cost);
bool validate_graph(vector<Knoten>* knotenliste, vector<Kante>* kantenliste, int anzahl_knoten, int anzahl_kanten);
#endif