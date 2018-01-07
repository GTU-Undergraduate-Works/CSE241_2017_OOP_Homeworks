all: connectfour

connectfour: main.o connectfour.o
	g++ main.o connectfour.o -o exe

connectfour.o: connectfour.cpp
	g++ -c connectfour.cpp

clean:
	rm *.o exe


