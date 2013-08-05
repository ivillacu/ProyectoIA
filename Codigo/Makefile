make:
	g++ funciones.cpp -c
	g++ fc.cpp -c
	g++ main.cpp -o main funciones.o fc.o
	rm funciones.o fc.o
debug:
	g++ funciones.cpp -c
	g++ -g main.cpp -o main funciones.o
	rm funciones.o

run:
	./main
