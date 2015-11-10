/* Header-Datei main.hpp */
#ifndef MAIN_HPP
#define MAIN_HPP

//Variablen

//Parameter-Flag
bool eval_parameter;
string input_path;
string output_path;

//Hilfsvariablen zur Zeiterfassung
clock_t start_zeit;
clock_t end_zeit;

//Graphenstacks
vector<Kante> kantenliste;
vector<Knoten> knotenliste;

//Einlese-Stream
ifstream input_graph;
ofstream output_graph;

//Zähler
int anzahl_knoten;
int anzahl_kanten;

//Fehlerausgabe
std::stringstream fehlertext;

//Methoden von main.c
void showUsage(void);
void einlesen(string file_path);
bool validate();
void ausgeben(string file_path);


#endif