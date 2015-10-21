r-spantree:src/main.cpp src/header.hpp
	g++ -c src/main.cpp -o bin/main.o
	g++ bin/main.o -o r-spantree
clean:
	rm bin/main.o
	rm r-spantree
testen:
	./r-spantree -in test/instance/01.txt -out test/instance/01_solved.txt
