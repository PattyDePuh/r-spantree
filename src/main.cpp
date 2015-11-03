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

#include "header.hpp"

#define FAIL 99999999

int main(int argc, char* argv[]){
	
	//Eingabe-Validierung
  if( argc != 5 && argc != 3){
  	printf("Unzulässige Anzahl an Argumenten: %d \n", argc);
  	showUsage();
  	return 1;
  }
  printf("Moin, dies ist der Aufruf von r-spantree.\n");
  //Parameter filtern
  eval_parameter = false;
  for( i = 1; i < argc - 1; i++ ){
    //Argument erfassen
    string s = argv[i];
    //Ist der -in Parameter erfasst, lese die Datei aus folgenden Path ein.
    if(s.compare( "-in" ) == 0){
      input_path = argv[i+1];
    }
    if(s.compare( "-out" ) == 0){
      output_path = argv[i+1];
    }
    //Ist der -eval Parameter erfasst, setze die entsprechende flag 
    if(s.compare( "-eval" ) == 0){
      eval_parameter = true;
      input_path = argv[i+1];
    }
  }
    
  //Parameter Bearbeitung/Validierung
  einlesen(input_path);
  if(eval_parameter == true){
    //Führe Validierung
    erfolg = validate(true);
    if(erfolg){
      //Validierung erfolgreich
      printf("valide Lösung\n");
      return 0;
    }else{
      //Lösung ist nicht valide.
      printf("ERROR:\n");
      std::cout << fehlertext.str();
      return 1;
    }
  }else{
    //Führe Optimierung durch
    erfolg = optimize();
    if(erfolg){
      ausgeben(output_path);
    }
  }

  //TODO dynamische Ausgabe 
  printf("%d\t%ld\n", -1, ((end_zeit - start_zeit) * 1000) / CLOCKS_PER_SEC );
  return 0;
}



void showUsage(){
	printf("Aufrufschema: './rspantree -in <path/to/input> -out <path/to/output>'\n");
	printf("Bzw: './r-spantree -eval <path/to/instance>' für Evaluierung");
}



void einlesen(string path){
  std::cout << "Lese "<< path << " ein ...\n";
  //Initialisierung Stream
  input_graph.open(path);
  //Lese Kanten und Knotenanzahl aus.
  string input_knoten;
  string input_kanten;
  getline(input_graph, input_knoten);
  getline(input_graph, input_kanten);
  anzahl_knoten = stoi(input_knoten);
  anzahl_kanten = stoi(input_kanten);
  //Reserviere Speicher in den Stacks
  kantenliste.reserve(anzahl_kanten);
  knotenliste.reserve(anzahl_knoten);
  //Lese die Knoten ein
  for(int j = 0; j <= anzahl_knoten - 1; j++){
    string input_string;
    getline(input_graph, input_string);
    knotenliste.emplace_back(j, stoi(input_string));
  }
  //Lese die Kanten ein
  for(int j = 0; j <= anzahl_kanten - 1; j++){
    //Trenne die eingelesene Zeile an den Leerzeichen.
    string input_string;
    //Startknoten
    getline(input_graph, input_string, ' ');
    int stk = stoi(input_string);

    //Endknoten
    getline(input_graph, input_string, ' ');
    int enk = stoi(input_string);

    //Kosten
    getline(input_graph, input_string, ' ');
    int cost = stoi(input_string);

    //ggf. Lösungsvorschlag
    getline(input_graph, input_string);
    int result = 0;
    if(stoi(input_string) == 1){
      result = 1;
    }
    kantenliste.emplace_back(j, stk, enk, cost, result);
  }
  input_graph.close();
  printf("Einlese-Prozess fertig.\n");
}



bool optimize(){
  //Start
  start_zeit = clock();

  //Initialisierung der Arrays (zT. Monitoring)
  int current_solution[anzahl_kanten];
  int best_solution[anzahl_kanten]; //Wird in der ersten Phase nicht verwendet
  int kante_untersucht[anzahl_kanten];
  int incidente_array[anzahl_knoten];
  int restriction_array[anzahl_knoten];

  for(int k = 0; k < anzahl_kanten; k++){
    current_solution[k] = 0;
    best_solution[k] = 0; 
    kante_untersucht[k] = 0;
  }
  for(int k = 0; k < anzahl_knoten;k++){
    incidente_array[k] = 0;
    restriction_array[k] = knotenliste.at(k).restriction;
  }
  int anzahl_kanten_picked = 0;
  current_cost = 0;
  best_cost = FAIL;

  //Initiales Einfügen
  //Füge die n-günstigsten Kanten ein ohne Prüfung (logische Mindestanzahl)
  while(anzahl_kanten_picked < anzahl_knoten-1){
    //Füge dem Graphen eine Kante hinzu
    kante_setzen(current_solution, kante_untersucht, incidente_array, restriction_array);
  }
  //Anschließend füge solange Kanten hinzu, bis der Graph valide ist.
  while(!validate(false)){
    kante_setzen(current_solution, kante_untersucht, incidente_array, restriction_array);
  }

  //Ende
  end_zeit = clock();

  //return true, wenn eine valide Lösung gefunden wurde. 
  if(best_cost == FAIL){
    return false;
  }else{
    return true;
  }
}

//Sucht nach der nächst-günstigen Kante und versucht diese einzufügen.
void kante_setzen(int current_solution[], int kante_untersucht[], int incidente_array[], int restriction_array[]){

  int min_cost = FAIL;
  int min_candidat = -1;
  for(auto it = kantenliste.begin(); it != kantenliste.end(); it++){
    //Wenn die Kante noch nicht besucht wurde
    if(current_solution[it->id] != 1 && it->cost < min_cost && kante_untersucht[it->id] != 1){
      min_cost = it->cost;
      min_candidat = it->id;
    }  
  }
  //Wenn alle Kanten bereits besucht sind -> Fehler: Brich ab.
  if(min_candidat == -1){
    std::cout << "-1\t0\n";
    exit(0);
  }
  //Hol dir die Kante ausm vector.
  Kante kante = kantenliste.at(min_candidat);
  //Markiere die Kante, dass sie untersucht wird.
  kante_untersucht[kante.id] = 1;
  //Überprüfe, ob die Kante von den Knoten tragbar ist.
  if(incidente_array[kante.start] < restriction_array[kante.start] &&
    incidente_array[kante.ziel] < restriction_array[kante.ziel]){
    //Es passt! Füge die Kante der Lösung hinzu.
    current_solution[kante.id] = 1;
    kante.result = 1;
    current_cost += kante.cost;
    //Passe das entsprechen incidente_array an.
    ++incidente_array[kante.start];
    ++incidente_array[kante.ziel];
  }
  //ggf TODO - Schleife bauen, wenn die Kante nicht hinzugefügt wurde.
}

bool validate(bool schreibe_Fehlertext){
  bool valide = true;
  //Initialisierung des Check-Arrays und des Stacks
  bool besucht[anzahl_knoten];
  for (int i = 0; i < anzahl_knoten; i++) {
    besucht[i] = false;
  }
  queue<int> such_que;
  //Überprüfe durch Breiten-Suche, ob von einem Knoten alle anderen Knoten erreichbar sind.
  //Beginne mit Knoten Nr 1;
  such_que.push(0);
  //Wiederhole folgenden Vorgang, bis es keine lokalen Orte mehr existieren.
  do{
    //Hol dir einen Knoten aus der Such-Que
    Knoten n = knotenliste.at(such_que.front());
    such_que.pop();
    //Markiere den Knoten als besucht.
    besucht[n.id] = true;

    //Debug-Array Ausgabe
    #ifdef DEBUG
    string test = "[";
    for(int x = 0; x < anzahl_knoten; x++){
      if(besucht[x] == true){
        test.append("o");
      }else{
        test.append("x");
      }
    }
    test.append("]");
    std::cout << test << "\n";
    #endif

    int incidente = 0;
    //Hol die Kanten, die von dem Knoten ausgehen,
    for (std::vector<Kante>::iterator kante = kantenliste.begin() ; kante != kantenliste.end(); ++kante){
      //Lese Eingangs/Ausgangskante aus.
      if(kante->start == n.id){
        //Wenn eine incidente Kante, zähle hoch
        if(kante->result == 1){
          ++incidente;
        }
        //Schreibe Nachbarkante in die Que, wenn noch nicht besucht
        if(besucht[kante->ziel] == false && kante->result == 1){
          such_que.push(kante->ziel);
        }
      }
      if(kante->ziel == n.id){
        //Wenn eine incidente Kante, zähle hoch
        if(kante->result == 1){
          ++incidente;
        }
        //Schreibe Nachbarkante in die Que, wenn noch nicht besucht
        if(besucht[kante->start] == false && kante->result == 1){
          such_que.push(kante->start);
        }
      }
    }
    //Abschließend überprüfen, dass die Anzahl Kanten
    if(n.restriction < incidente){
      if(schreibe_Fehlertext){
        fehlertext << "Knoten Nr." << n.id << " hat zuviele Kanten: " << incidente << " von " << n.restriction << "\n";
      }
      valide == false;
    }
  } while(!such_que.empty());

  //Wenn keine Restriction gebrochen wurde, 
  //überprüfe im Array, ob alle Knoten besucht wurden.
  for(i = 0; i < anzahl_knoten; i++){
    if(besucht[i] == false){
      if(schreibe_Fehlertext){
        fehlertext << "Knoten Nr." << i << " ist vom Knoten Nr.0 nicht erreichbar!\n"; 
      }
      valide = false;
    }
  }

  return valide;
}

void ausgeben(string path){
  printf("Schreibe Ausgabedatei");
  //Öffne bzw. erstelle Outputdatei
  output_graph.open(output_path, std::ofstream::out | std::ofstream::app);
  //Füge Anzahl Knoten und Kanten ein.
  output_graph << anzahl_knoten << std::endl << anzahl_kanten << std::endl;
  //Füge in einer Schleife nun die Kantenrestriktion der Knoten ein.
  for (auto it = knotenliste.begin(); it != knotenliste.end(); it++){
    output_graph << it->restriction << std::endl;
  }
  //Füge in einer Schleife alle Kanten nun ein: Startknoten Zielknoten Kantenkosten Lösung
  for (auto it = kantenliste.begin(); it != kantenliste.end(); it++){
    output_graph << it->start << " " << it->ziel << " " << it->cost << " " << it->result << std::endl;
  }
  //Schließe die Datei
  output_graph.close();

  printf("Ausgabe abgeschlossen");
}