# r-spantree
C program to find solution for a minimum spanning tree with maximum edge restrictions on the nodes.

# Aufbau der Testinstanzen
- Zeile 1:                Anzahl Knoten (n)
- Zeile 2:                Anzahl Kanten (m)
- Zeile 3 bis (2+n):      Ziffer der maximalen Kantenrestriktion
- Zeile (3+n) - (2+n+m):  Startknoten; Endknoten; Kantengewicht; (optional Lösung [0/1])

# ToDo's
- Solver schreiben
  - 2 Heuristiken bis Anfang Dezember
  - 1 Integerprogramm Ansatz bis Januar
  - ein weiterer, beliebiger Ansatz bis Februar
  - ggf. Spezial-Validator für Solver schreiben
  - 

# Projekt kompilieren mit CMake
mkdir build
cd build
cmake ..
make

