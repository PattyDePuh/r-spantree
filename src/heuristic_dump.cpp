/* Code-File heuristic_dump */
#include "header.hpp"
#include "heuristic_dump.hpp"

//Erster Versuch eine Lösung zu finden.
long optimize(vector<Knoten>* knotenliste, vector<Kante>* kantenliste, int anzahl_knoten, int anzahl_kanten){
  //Start

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
    restriction_array[k] = knotenliste->at(k).restriction;
  }
  int anzahl_kanten_picked = 0;
  long current_cost = 0;
  long best_cost = FAIL;

  //Initiales Einfügen
  //Füge die n-günstigsten Kanten ein ohne Prüfung (logische Mindestanzahl)
  while(anzahl_kanten_picked < anzahl_knoten-1){
    //Füge dem Graphen eine Kante hinzu
    kante_setzen(current_solution, kante_untersucht, incidente_array, restriction_array, kantenliste, &current_cost);
  }
  //Anschließend füge solange Kanten hinzu, bis der Graph valide ist.
  while(!validate_graph(knotenliste, kantenliste, anzahl_knoten, anzahl_kanten)){
    kante_setzen(current_solution, kante_untersucht, incidente_array, restriction_array, kantenliste, &current_cost);
  }

  //Ende

  //return true, wenn eine valide Lösung gefunden wurde. 
  if(best_cost == FAIL){
    return -1;
  }else{
    return best_cost;
  }
}

//Sucht nach der nächst-günstigen Kante und versucht diese einzufügen.
void kante_setzen(int current_solution[], int kante_untersucht[], int incidente_array[], int restriction_array[], std::vector<Kante>* kantenliste, long* current_cost){

  int min_cost = FAIL;
  int min_candidat = -1;
  for(auto it = kantenliste->begin(); it != kantenliste->end(); it++){
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
  Kante kante = kantenliste->at(min_candidat);
  //Markiere die Kante, dass sie untersucht wird.
  kante_untersucht[kante.id] = 1;
  //Überprüfe, ob die Kante von den Knoten tragbar ist.
  if(incidente_array[kante.start] < restriction_array[kante.start] &&
    incidente_array[kante.ziel] < restriction_array[kante.ziel]){
    //Es passt! Füge die Kante der Lösung hinzu.
    current_solution[kante.id] = 1;
    kante.result = 1;
    *current_cost += kante.cost;
    //Passe das entsprechen incidente_array an.
    ++incidente_array[kante.start];
    ++incidente_array[kante.ziel];
  }
  //ggf TODO - Schleife bauen, wenn die Kante nicht hinzugefügt wurde.
}

//Überprüfe die Lösung des Graphen, ob diese gültig ist.
bool validate_graph(vector<Knoten>* knotenliste, vector<Kante>* kantenliste, int anzahl_knoten, int anzahl_kanten){
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
    Knoten n = knotenliste->at(such_que.front());
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
    for (std::vector<Kante>::iterator kante = kantenliste->begin() ; kante != kantenliste->end(); ++kante){
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
      valide = false;
    }
  } while(!such_que.empty());

  //Wenn keine Restriction gebrochen wurde, 
  //überprüfe im Array, ob alle Knoten besucht wurden.
  for(int i = 0; i < anzahl_knoten; i++){
    if(besucht[i] == false){
      valide = false;
    }
  }

  return valide;
}