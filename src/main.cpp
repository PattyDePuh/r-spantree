#include <stdio.h>
#include <time.h>
#include "header.h"


int main(int argc, char* argv[]){
	
	//Eingabe-Validierung
  if( argc != 5 && argc != 3){
  	printf("Unzulässige Anzahl an Argumenten: %d \n", argc);
  	showUsage();
  	return 1;
  }

  //Vorbereitung
  
	printf("Moin, dies ist der Aufruf von r-spantree.\n");

  // hier einlesen
  for( i = 1; i < argc - 1; i++ ){
    if(argv[i] == "-in"){
      einlesen(argv[i+1]);
    }
  }
  
  //Start
  start_zeit = clock();

  //TODO hier ausarbeiten

  end_zeit = clock();

  //Ausgabe
  printf("%d\t%ld\n", -1, ((end_zeit - start_zeit) * 1000) / CLOCKS_PER_SEC );
  return 0;
}

void showUsage(){
	printf("Aufrufschema: './rspantree -in <path/to/input> -out <path/to/output>'\n");
	printf("Bzw: './r-spantree -eval <path/to/instance>' für Evaluierung");
}

void einlesen(char* path){
  printf("Ich lese ein von %s ...\n", path);
}
