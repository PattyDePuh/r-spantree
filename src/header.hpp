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
	kanten_konstrukt(int id, int start, int ziel, int kosten, int result): id(id), start(start), ziel(ziel), kosten(kosten), result(result) {};
	int id;
	int start;
	int ziel;
	int kosten;
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

//Methoden von main.c
void showUsage(void);
void einlesen(string path);
bool validate();
bool optimize();
void ausgeben(string path);

#endif 
/* Ende HEADER_HPP */