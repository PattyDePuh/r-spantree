r-spantree: bin/main.o
  gcc bin/main.o r-spantree
main.o: src/main.c
	gcc -c src/main.c -o bin/main.o
clean:
	rm bin/main.o
	rm r-spantree
