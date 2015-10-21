//Klassen


//Strukturen
//Knoten im Graph
struct knoten_konstrukt{
	int id;
	int restriction;
};
//Kanten im Graph
struct kanten_konstrukt{
	int id;
	int start;
	int ziel;
	int kosten;
};

typedef kanten_konstrukt kante;
typedef knoten_konstrukt knoten;

//Variablen
int i;
int k_id;

//Hilfsvariablen zur Zeiterfassung
clock_t start_zeit;
clock_t end_zeit;

//Graphenstacks
vector<kante> kantenliste;
vector<knoten> knotenliste;

//Methoden von main.c
void showUsage(void);
void einlesen(char* path);
