/* Code-File heuristic_1 */
#include "header.hpp"
#include "heuristic_1.hpp"

//Erster heuristischer Versuch eine gute Lösung zu finden.
long optimize(vector<Knoten>* knotenliste, vector<Kante>* kantenliste, int anzahl_knoten, int anzahl_kanten){
  //Variablen-Deklaration
  long best_cost = 0;
  //Bereite HilfsArray für Kanten vor
  int current_solution[anzahl_kanten]; 	//Lösungsmenge
  int kante_untersucht[anzahl_kanten];	//Hilfsflag, ob bereits untersucht
	for(int k = 0; k < anzahl_kanten; k++){
    current_solution[k] = 0;
    kante_untersucht[k] = 0;
  }
  //Bereite HilfsArray für Knoten vor
  int incidente_array[anzahl_knoten];		//Anzahl gewählter Kanten an einem Knoten
  int restriction_array[anzahl_knoten];	//Abkürzung zur restiction
  int verbunden_array[anzahl_knoten];		//Hilfsflag, ob schon angebunden.
  for(int k = 0; k < anzahl_knoten; k++){
    incidente_array[k] = 0;
    restriction_array[k] = knotenliste->at(k).restriction;
    verbunden_array[k] = 0;
  }
 	//Zähler für bereits angeschlossene Kanten.
  int anzahl_knoten_gebunden = 0;

  //Start
  //Nimm einen Start-Knoten:
  Knoten focus = knotenliste->at(0);
  anzahl_knoten_gebunden++;
  verbunden_array[0] = 1;
  //Finde alle incidenten Kanten und lege für jede Kante, 
  // die noch nicht untersucht wurde, einen Eintrag in der pq an.
  for (std::vector<Kante>::iterator kante = kantenliste->begin() ; kante != kantenliste->end(); ++kante){
  	if( kante_untersucht[kante->id] == 0 && (kante->start == focus.id || kante->ziel == focus.id) ){
  		pq.emplace(kante->id, kante->cost);
  	}
  }
  //Testschleife, ob die Que funktioniert.
	/*while(!pq.empty()){
	  	QueItem i = pq.top();
	  	pq.pop();
	  	std::cout << "(" << i.index << ", " << i.cost << ")" << std::endl;
	  }
	 */
	//Solange es noch Kanten gibt in der Que 
	// und noch nicht alle Knoten angebunden sind, tue folgendes:
	while(!pq.empty() && anzahl_knoten_gebunden < anzahl_knoten){
		//Hol dir die nächste günstige Kante aus der Que.
		QueItem item = pq.top(); pq.pop();
		Kante ka_focus = kantenliste->at(item.index);

		//Test-Ausgabe
		std::cout << "pq.length:" << pq.size() << std::endl;
		std::cout << "ka_focus( id:" << ka_focus.id << ", start:" << ka_focus.start << ", ziel:" << ka_focus.ziel << ", cost:" << ka_focus.cost << " )" << std::endl; 
		//Falls die Kante bereits untersucht wurde, dann ignoriere sie.
		if(kante_untersucht[ka_focus.id] == 1)
			continue;
		kante_untersucht[ka_focus.id] = 1;

		//Es folgen eine Reihe von Fallunterscheidungen:

		//Beide Knoten der Kante sind bereits angebunden -> Kante wir wahrscheinlich nicht benötigt
		//Ggf. noch an Beispielen untersuchen...
		if(verbunden_array[ka_focus.start] == 1 && verbunden_array[ka_focus.ziel] == 1)
			continue;

		//Einer der beiden Knoten ist noch nicht nicht angebunden -> Überprüfe, 
		// ob restrictionen nicht gebrochen werden, dann füge Kante hinzu.
		if(verbunden_array[ka_focus.start] == 1 || verbunden_array[ka_focus.ziel] == 1){
			if(restriction_array[ka_focus.start] > incidente_array[ka_focus.start] &&
					restriction_array[ka_focus.ziel] > incidente_array[ka_focus.ziel] ){
				current_solution[ka_focus.id] = 1;
				//Hilfsvariablen anpassen nicht vergessen!
				incidente_array[ka_focus.start]++;
				incidente_array[ka_focus.ziel]++;
				best_cost += ka_focus.cost;
				//Außerdem:
				//Finde herraus, welcher Knoten frisch hinzukam
				focus = verbunden_array[ka_focus.start] != 0? knotenliste->at(ka_focus.ziel) : knotenliste->at(ka_focus.start);
				//und füge seine inzidenten, noch nicht-untersuchten Kanten in die Que.
				for (std::vector<Kante>::iterator kante = kantenliste->begin() ; kante != kantenliste->end(); ++kante){
  				if( kante_untersucht[kante->id] == 0 && (kante->start == focus.id || kante->ziel == focus.id) ){
  					pq.emplace(kante->id, kante->cost);
  				}
  			}
  			//Der Knoten ist nun angebunden:
  			verbunden_array[ka_focus.start] = 1;
				verbunden_array[ka_focus.ziel] = 1;
				anzahl_knoten_gebunden++;
			}
		}
	}

	//Test-Ausgabe: Zwischenergebnisse
	std::cout << "Zwischenergebnisse" << std::endl;
	for(int i = 0; i < anzahl_knoten; i++){
		Knoten test = knotenliste->at(i);
		std::cout << "(id:" << i << ", inci:" << incidente_array[i] << ", restr: " << restriction_array[i] << ", bound:" << verbunden_array[i] << std::endl;
	}

	//Wenn nicht alle Knoten gefunden wurden, dann beginne mit der rekursiven Problemlösung.
	if(anzahl_knoten != anzahl_knoten_gebunden){
		//Zuvor noch das "untersucht"-Array clearen, um es als "lock"-Array zu verwerten.
		for(int j = 0; j < anzahl_kanten; j++){
			kante_untersucht[j] = 0;
		}
		//Wenn der Solver fehlschlägt, dann gib '-1' zurück.
		if(recursiv_solver(knotenliste, kantenliste, anzahl_knoten, anzahl_kanten,
					incidente_array, restriction_array, verbunden_array, current_solution, 
					kante_untersucht, best_cost) == false)
			return -1;
	}

	//Abschließende Auswertung
	//wenn alle Knoten angebunden sind, war die Suche erfolgreich:
	for(int i = 0; i < anzahl_kanten; i++){
		kantenliste->at(i).result = current_solution[i];
	}
  //Ende
  return best_cost;
}

bool recursiv_solver(vector<Knoten>* knotenliste, vector<Kante>* kantenliste, int& anzahl_knoten, int& anzahl_kanten,
					int incidente_array[], int restriction_array[], int verbunden_array[], int current_solution[], 
					int locked_edge[], long& current_cost){
	std::cout << "Rundenbeginn Solver:" << std::endl;
	//Eine neue Runde Solver.
	//Resette das verbunden-Array zuerst
	for(int f = 0; f < anzahl_knoten; f++){
		verbunden_array[f] = 0;
	}
	//------------------------
	//beginne Breitensuche ...
	queue<int> such_que;
	such_que.push(0);
	do{
    //Hol dir einen Knoten aus der Such-Que
    Knoten n = knotenliste->at(such_que.front());
    such_que.pop();
    //Markiere den Knoten als besucht.
    verbunden_array[n.id] = true;

    //Hol die Kanten, die von dem Knoten ausgehen,
    for (std::vector<Kante>::iterator kante = kantenliste->begin() ; kante != kantenliste->end(); ++kante){
      //Lese Eingangs/Ausgangskante aus.
      	//Schreibe Nachbarkante in die Que, wenn noch nicht besucht
      if(kante->start == n.id && verbunden_array[kante->ziel] == false && current_solution[kante->id] == 1){
          such_que.push(kante->ziel);
      }
      if(kante->ziel == n.id && verbunden_array[kante->start] == false && current_solution[kante->id] == 1){
        such_que.push(kante->start);
      }
    }
  } while(!such_que.empty());
  //Ende Breitensuche
  //-------------------------

  //Erste Auswertung:
  //Wenn alle Knoten miteinander verbunden sind -> return 'true'
  bool valide = true;
  for(int b = 0; b < anzahl_knoten; b++){
  	if(verbunden_array[b] == 0){
  		valide = false;
  		break;
  	}
  }
  if(valide){
  	return true;
  }

  //Ab hier haben wird der Fall bearbeitet, dass der Graph getrennt ist...
  //Suche alle Kanten, die den bestehenden, gebundenen Graphen mit dem Rest verbinden könnten.
  //Sortiere sie aufsteigend nach ihren Kosten.
  std::priority_queue<QueItem, vector<QueItem>, CompareItem> kandidaten_que;
  for (std::vector<Kante>::iterator kante = kantenliste->begin() ; kante != kantenliste->end(); ++kante){
  	if(  ( (verbunden_array[kante->start] == 1 && verbunden_array[kante->ziel] == 0) ||
  				 (verbunden_array[kante->start] == 0 && verbunden_array[kante->ziel] == 1) )  && 
  					locked_edge[kante->id] != 1){ //Die Kante darf außerdem von vorherigen Rekurstionen nicht gesperrt sein!
  		kandidaten_que.emplace(kante->id, kante->cost);
  	}
  } 
  std::cout << "Anzahl Kandidaten: " << kandidaten_que.size() << std::endl;
  //Arbeite die Kanten ab:
  while(!kandidaten_que.empty()){
  	//Nimm die Kante mit den nächst-geringsten Kosten
  	QueItem item = kandidaten_que.top(); kandidaten_que.pop();
  	Kante kandidat = kantenliste->at(item.index);
  	std::cout << "kandidat( id:" << kandidat.id << ", start:" << kandidat.start << ", ziel:" << kandidat.ziel << ", cost:" << kandidat.cost << " ) rein" << std::endl; 
  	std::cout << "incidente( left:" << incidente_array[kandidat.start] << "->" << incidente_array[kandidat.start]+1 << "/" << restriction_array[kandidat.start] << ", right:" << incidente_array[kandidat.ziel] << "->" << incidente_array[kandidat.ziel]+1 << "/" << restriction_array[kandidat.ziel] << ")" << std::endl;
  	//Logge die Kante ein
  	current_solution[kandidat.id] = 1;
  	locked_edge[kandidat.id] = 1;
  	current_cost += kandidat.cost;
  	incidente_array[kandidat.start]++;
  	incidente_array[kandidat.ziel]++;

  	//Wenn die Restriction überschritten wurde, müssen andere Kanten wieder verschwinden.
  	bool left_overflow = incidente_array[kandidat.start] > restriction_array[kandidat.start];
  	if(left_overflow)
  		std::cout << "LeftOverflow" << std::endl;
  	bool right_overflow = incidente_array[kandidat.ziel] > restriction_array[kandidat.ziel];
  	if(right_overflow)
  		std::cout << "RightOverflow" << std::endl;
  	//Container
  	vector<int> left_edges;
  	vector<int> right_edges;
  	//Entdecke alle inzidente Kanten der überfüllten Knoten, die genutzt werden und nicht gelockt sind.
  	for (std::vector<Kante>::iterator kante = kantenliste->begin() ; kante != kantenliste->end(); ++kante){
  		if( (kante->start == kandidat.start || kante->ziel == kandidat.start) && left_overflow && current_solution[kante->id] == 1 && locked_edge[kante->id] == 0)	
  			left_edges.push_back(kante->id);
  		if( (kante->start == kandidat.ziel || kante->ziel == kandidat.ziel) && right_overflow  && current_solution[kante->id] == 1 && locked_edge[kante->id] == 0)
  			right_edges.push_back(kante->id);
  	}
   	//Arbeite die Kombinationen ab:
   	//Spezialfall, beide Seiten sind überfüllt, dann alle Fällle abarbeiten
  	if(left_overflow && right_overflow){
  		std::cout << "->Doppelter Overflow:" << std::endl;
  		//Doppelte For-Schleife über alle zweier Kombinationen zwischen den Kanten
  		for(std::vector<int>::iterator l = left_edges.begin() ; l != left_edges.end(); l++){
  			for(std::vector<int>::iterator r = right_edges.begin() ; r != right_edges.end(); r++){
  				std::cout << "kanten( id:" << kantenliste->at(*l).id << ", start:" << kantenliste->at(*l).start << ", ziel:" << kantenliste->at(*l).ziel << ", cost:" << kantenliste->at(*l).cost << " ) und (" 
  				  	<< "( id:" << kantenliste->at(*r).id << ", start:" << kantenliste->at(*r).start << ", ziel:" << kantenliste->at(*r).ziel << ", cost:" << kantenliste->at(*r).cost << " ) raus" << std::endl; 

  				//Entferne beide Kanten, ziehe die Kosten ab und mache sie fest.
  				current_solution[*l] = 0;
  				current_solution[*r] = 0;
  				current_cost -= kantenliste->at(*l).cost;
  				current_cost -= kantenliste->at(*r).cost;
  				incidente_array[kantenliste->at(*l).start]--;
  				incidente_array[kantenliste->at(*r).start]--;
  			  incidente_array[kantenliste->at(*l).ziel]--;
  				incidente_array[kantenliste->at(*r).ziel]--;
  				locked_edge[*l] = 1;
  				locked_edge[*r] = 1;

					//Rekursionsstufe runtergehen
  				if(recursiv_solver(knotenliste, kantenliste, anzahl_knoten, anzahl_kanten,
						incidente_array, restriction_array, verbunden_array, current_solution, 
						locked_edge, current_cost))
  					return true;
  				//Änderung rückgängig machen
  				current_solution[*l] = 1;
  				current_solution[*r] = 1;
  				current_cost += kantenliste->at(*l).cost;
  				current_cost += kantenliste->at(*r).cost;
  				incidente_array[kantenliste->at(*l).start]++;
  				incidente_array[kantenliste->at(*r).start]++;
  			  incidente_array[kantenliste->at(*l).ziel]++;
  				incidente_array[kantenliste->at(*r).ziel]++;
  				locked_edge[*l] = 0;
  				locked_edge[*r] = 0;
  			}
  		}
  	}else if(left_overflow || right_overflow){
  		//Fall: arbeite left_edges oder right edges separat ab.
  		for(std::vector<int>::iterator k = left_edges.begin() ; k != left_edges.end(); k++){
  			std::cout << "Kante( id:" << kantenliste->at(*k).id << ", start:" << kantenliste->at(*k).start << ", ziel:" << kantenliste->at(*k).ziel << ", cost:" << kantenliste->at(*k).cost << " ) raus" << std::endl;
  			//Entferne die Kante, ziehe die Kosten ab und mache sie fest.
  			current_solution[*k] = 0;
  			incidente_array[kantenliste->at(*k).start]--;
  			incidente_array[kantenliste->at(*k).ziel]--;
  			current_cost -= kantenliste->at(*k).cost;
  			locked_edge[*k] = 1;
  			//Rekursionsstufe runtergehen
  			if(recursiv_solver(knotenliste, kantenliste, anzahl_knoten, anzahl_kanten,
					incidente_array, restriction_array, verbunden_array, current_solution, 
					locked_edge, current_cost))
  				return true;
  			//Gelöschte Kante wiederherstellen und freigeben  		
  			current_solution[*k] = 1;
  			incidente_array[kantenliste->at(*k).start]++;
  			incidente_array[kantenliste->at(*k).ziel]++;
  			current_cost += kantenliste->at(*k).cost;
  			locked_edge[*k] = 0;
  		}
  		//Nochmal für right_edges;
  		for(std::vector<int>::iterator k = right_edges.begin() ; k != right_edges.end(); k++){
  			std::cout << "Kante( id:" << kantenliste->at(*k).id << ", start:" << kantenliste->at(*k).start << ", ziel:" << kantenliste->at(*k).ziel << ", cost:" << kantenliste->at(*k).cost << " ) raus" << std::endl;
  			//Entferne die Kante, ziehe die Kosten ab und mache sie fest.
  			current_solution[*k] = 0;
  			current_cost -= kantenliste->at(*k).cost;
  			incidente_array[kantenliste->at(*k).start]--;
  			incidente_array[kantenliste->at(*k).ziel]--;
  			locked_edge[*k] = 1;
  			//Rekursionsstufe runtergehen
  			if(recursiv_solver(knotenliste, kantenliste, anzahl_knoten, anzahl_kanten,
					incidente_array, restriction_array, verbunden_array, current_solution, 
					locked_edge, current_cost))
  				return true;
  			//Gelöschte Kante wiederherstellen und freigeben  		
  			current_solution[*k] = 1;
  			current_cost += kantenliste->at(*k).cost;
  			incidente_array[kantenliste->at(*k).start]++;
  			incidente_array[kantenliste->at(*k).ziel]++;
  			locked_edge[*k] = 0;
  		}
  	} else {
  		//Es müssen keine Kanten entfernt werden: ohne Abnahme in die Rekursion runtergehen.
  		if(recursiv_solver(knotenliste, kantenliste, anzahl_knoten, anzahl_kanten,
				incidente_array, restriction_array, verbunden_array, current_solution, 
				locked_edge, current_cost))
  			return true;
  	}

  	//Abschließend wieder die Kante freigeben
  	current_solution[kandidat.id] = 0;
  	locked_edge[kandidat.id] = 0;
  	current_cost -= kandidat.cost;
  	incidente_array[kandidat.start]--;
  	incidente_array[kandidat.ziel]--;
  }



  //Wir haben keine Lösung gefunden -> return false;
  return false;
}