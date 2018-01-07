all: connectfour

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

ConnectFourAbstract.o: ConnectFourAbstract.cpp
	g++ -std=c++11 -c ConnectFourAbstract.cpp

ConnectFourPlus.o: ConnectFourPlus.cpp
	g++ -std=c++11 -c ConnectFourPlus.cpp

ConnectFourDiag.o: ConnectFourDiag.cpp
	g++ -std=c++11 -c ConnectFourDiag.cpp

ConnectFourPlusUndo.o: ConnectFourPlusUndo.cpp
	g++ -std=c++11 -c ConnectFourPlusUndo.cpp

Cell.o: Cell.cpp
	g++ -std=c++11 -c Cell.cpp

connectfour: main.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o Cell.o
	g++ -std=c++11 -o exe main.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o Cell.o

clean:
	rm *.o exe


