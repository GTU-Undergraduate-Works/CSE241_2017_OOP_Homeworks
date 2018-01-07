all: test

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

GTUSet.o: GTUSet.cpp
	g++ -std=c++11 -c GTUSet.cpp

GTUMap.o: GTUMap.cpp
	g++ -std=c++11 -c GTUMap.cpp


test: main.o GTUSet.o GTUMap.o 
	g++ -std=c++11 -o exe main.o GTUSet.o 

clean:
	rm *.o exe


