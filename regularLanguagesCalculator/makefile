bin/regLangCalc: bin/lenguaje.o bin/calculadora.o src/main.cpp
	g++ -g -o bin/regLangCalc bin/lenguaje.o bin/calculadora.o src/main.cpp

bin/lenguaje.o: include/lenguaje.h src/lenguaje.cpp
	g++ -g -c -o bin/lenguaje.o src/lenguaje.cpp

bin/calculadora.o: include/calculadora.h src/calculadora.cpp
	g++ -g -c -o bin/calculadora.o src/calculadora.cpp

	
	
.PHONY: clean
clean:
	rm -rf bin/*.o

	
