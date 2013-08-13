CXX = g++
CXXFLAGS = -pg -lboost_program_options
OBJ = funciones.o fc.o utils.o

all: main

main: main.cpp $(OBJ)

clean:
	@rm -f *.o
distclean: clean
	@rm -f main
run:
	./main
