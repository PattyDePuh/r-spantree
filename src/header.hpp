/* Header-File “header.hpp“: */
#ifndef HEADER_HPP
#define HEADER_HPP

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

//Variablen
//Läufer
int i;
int k_id;

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
bool erfolg;

//Optimierungsvariablen
//int current_solution[];
//int current_cost[];
//int best_solution[];
//int best_cost[];

//int incidente_array[];
//int restriction_array[];
//int kante_untersucht

int current_cost;
int best_cost;

//Methoden von main.c
void showUsage(void);
void einlesen(string path);
bool validate(bool schreibe_Fehlertext);
bool optimize();
void kante_setzen(int current_solution[], int kante_untersucht[], int incidente_array[], int restriction_array[]);
bool einigkeits_test();
void ausgeben(string path);

#endif 
/* Ende HEADER_HPP */