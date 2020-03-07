main_scanner: scanner.o scanner_main.o
	g++ -o main_scanner scanner.o scanner_main.o

scanner.o: scanner.h scanner.cpp
	g++ -c scanner.cpp

scanner_main.o: scanner_main.cpp
	g++ -c scanner_main.cpp
	
	
.PHOMY: clean
clean:
	rm -rf *.o
