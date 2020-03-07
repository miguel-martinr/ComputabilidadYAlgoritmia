calc: lenguaje.o calculadora.o mainl.o
	g++ -o mainl lenguaje.o calculadora.o mainl.o

lenguaje.o: lenguaje.h lenguaje.cpp
	g++ -c lenguaje.cpp

calculadora.o: calculadora.h calculadora.cpp
	g++ -c calculadora.cpp

mainl.o: mainl.cpp
	g++ -c mainl.cpp
	
	
.PHONY: clean
clean:
	rm -rf *.o

	
