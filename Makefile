r-spantree:src/main.c	
	gcc -c src/main.c -o bin/main.o
	gcc bin/main.o -o r-spantree
clean:
	rm bin/main.o
	rm r-spantree
testen:
	./r-spantree -in test/instance/01.txt -out test/instance/01_solved.txt
