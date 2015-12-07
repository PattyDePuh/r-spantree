#include "header.hpp"
#include "main.hpp"

#ifdef HEURISTIK_0
#include "heuristic_dump.hpp"
#endif

#ifdef HEURISTIK_1
#include "heuristic_1.hpp"
#endif

#ifdef HEURISTIK_2
#include "heuristic_2.hpp"
#endif

int main(int argc, char* argv[]){
//./r-spantree -in path/to/file/ -out (path
	
	//Eingabe-Validierung
  if( argc != 5 && argc != 3){
  	printf("Unzulässige Anzahl an Argumenten: %d \n", argc);
  	showUsage();
  	return 2;
  }
  printf("Moin, dies ist der Aufruf von r-spantree.\n");
  //Parameter filtern
  eval_parameter = false;
  for(int i = 1; i < argc - 1; i++ ){
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
    
  //Hier soll später das Ergebnis gespeichert werden.
  long best_cost = -1;

  //Parameter Bearbeitung/Validierung
  einlesen(input_path);
  if(eval_parameter == true){
    //Führe Validierung
    bool erfolg = validate();
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
    //---------------------------------------------------
    //HIER werden die Optimierungsansätze eingefügt bzw.
    //Optimierungsmethoden Aufruf findet HIER statt.

    //Führe Optimierung durch
    start_zeit = clock();
    best_cost = optimize(&knotenliste, &kantenliste, anzahl_knoten, anzahl_kanten);
    end_zeit = clock();
    //Wenn die Optimierung erfolgreich war, 
    if(best_cost != -1){
      //Schreibe das Ergebnis in die Ausgabedatei raus
      ausgeben(output_path);
    }

    //-------------------------------------------------
  }

  //'best_cost' immer mit den errechneten Kosten der Lösung belegen.
  //ODER -1 bei Fehlschlag
  printf("%ld\t%ld\n", best_cost, ((end_zeit - start_zeit) * 1000) / CLOCKS_PER_SEC );
  return 0;
}


//Bei unangebrachtem Aufruf des Programms folgende "Gebrauchsanweisung" ausgeben.
void showUsage(){
	printf("Aufrufschema: './rspantree -in <path/to/input> -out <path/to/output>'\n");
	printf("Bzw: './r-spantree -eval <path/to/instance>' für Evaluierung");
}

//Lese den Graphen ein aus der Datei 'file'
void einlesen(string file_path){
  std::cout << "Lese "<< file_path << " ein ...\n";
  //Initialisierung Stream
  input_graph.open(file_path);
  //Lese Kanten und Knotenanzahl aus.
  string input_knoten;
  string input_kanten;
  getline(input_graph, input_knoten);
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

//Überprüfe die Lösung des Graphen, ob diese gültig ist.
bool validate(){
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
        fehlertext << "Knoten Nr." << n.id << " hat zuviele Kanten: " << incidente << " von " << n.restriction << "\n";      
      valide = false;
    }
  } while(!such_que.empty());

  //Wenn keine Restriction gebrochen wurde, 
  //überprüfe im Array, ob alle Knoten besucht wurden.
  for(int i = 0; i < anzahl_knoten; i++){
    if(besucht[i] == false){
        fehlertext << "Knoten Nr." << i << " ist vom Knoten Nr.0 nicht erreichbar!\n"; 
      valide = false;
    }
  }

  return valide;
}

//Schreibe Graphen incl. Lösung in Datei aus
void ausgeben(string file_path){
  //printf("Schreibe Ausgabedatei\n");

  //Öffne bzw. erstelle Outputdatei
  output_graph.open(file_path, std::ofstream::out | std::ofstream::app);
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

  //printf("Ausgabe abgeschlossen\n");
}
