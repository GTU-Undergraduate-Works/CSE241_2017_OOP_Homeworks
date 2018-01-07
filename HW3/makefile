all: connectfour

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

connectfour.o: connectfour.cpp
	g++ -std=c++11 -c connectfour.cpp

connectfour: main.o connectfour.o
	g++ -std=c++11 -o exe main.o connectfour.o 

clean:
	rm *.o exe


