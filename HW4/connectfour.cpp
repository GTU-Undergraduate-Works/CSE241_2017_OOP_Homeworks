/*
 * File:   connectfour.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on November 7, 2017, 11:00 A.M
 * This file includes implementation of all 
 * member functions of classes, implementation of
 * operator overloading functions and implementation of
 * global functions
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include "connectfour.h"
using namespace std;

int ConnectFour::Cell::count = 0;

// no parameter constructor
// it creates 5 X 5 connectfour game
ConnectFour::ConnectFour()
				:width(5), height(5), order(1)
{
	gameCells = new Cell * [height];
	for (int i = 0; i < height; i++)
		gameCells[i] = new Cell [width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			gameCells[i][j].setPosition(static_cast<char>('a' + j), i);
}

// one parameter constructor
// it reads given filename and creates object according to file inormation.
ConnectFour::ConnectFour(const string & fileName)
				:width(0), height(0), order(1) 
{
	//cout << "\nONE PARAMETER CONSTRUCTOR" << endl;
	ifstream inputFile;
	int tempInt = 0;
	char temp;

	inputFile.open(fileName);
	if (inputFile.fail()) {
		cerr << "Failed to open file " << fileName << endl;
		exit(1);
	}
	inputFile.close();
	readFileAndSetBoard(fileName);
}

// two parameter constructor
// it creates widthValue x heightValue ConnectFour game
ConnectFour::ConnectFour(int widthValue, int heightValue)
				:width(widthValue), height(heightValue), order(1)
{
	gameCells = new Cell * [height];
	for (int i = 0; i < height; i++)
		gameCells[i] = new Cell [width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			gameCells[i][j].setPosition(static_cast<char>('a' + j), i);
}

// copy constructor
// it copies gameObject to member object
ConnectFour::ConnectFour(const ConnectFour & gameObject)
				:width(gameObject.width),height(gameObject.height), 
				 choice(gameObject.choice), order(gameObject.order)
{
	gameCells = new Cell * [height];
	for (int i = 0; i < height; i++)
		gameCells[i] = new Cell [width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			gameCells[i][j] = gameObject.gameCells[i][j];
}

// destructor for ConnectFour class
// it deletes dynamic memory for ConnectFour objects
ConnectFour::~ConnectFour()
{	
	for (int i = 0; i < height; i++) {
		delete [] gameCells[i];
		gameCells[i] = NULL;
	}
	delete [] gameCells;
	gameCells = NULL;
}

// no parameter constructor for Cell class
ConnectFour::Cell::Cell()
			: position('A'), rowNumber(0), content('.')
{ /* intentionally empty */}

// assigment operator for ConnectFour class
ConnectFour & ConnectFour::operator = (const ConnectFour & other)
{
	//cout << "ASSIGMENT" << endl;
	if (this == &other)
		return *this;
	resizeAndSetBoard(other.width, other.height);
	choice = other.choice;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			gameCells[i][j] = other.gameCells[i][j];
	return *this;
}

// == operator for ConnectFour class
// if objects is equal return true, if not return false
bool ConnectFour::operator == (const ConnectFour & other) const 
{
	if (width != other.width || height != height)
		return false;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			if (gameCells[i][j] != other.gameCells[i][j])
				return false;
	}
	return true;
}

// == operator for ConnectFour class
// if objects is not equal return true, if is equal return false
bool ConnectFour::operator != (const ConnectFour & other) const 
{
	return !(*this == other);
}

// == operator for Cell class
// if objects is equal return true, if not return false
bool ConnectFour::Cell::operator == (const Cell & other) const 
{
	return (content == other.content &&
			rowNumber == other.rowNumber &&
			position == other.position);
}

// == operator for Cell class
// if objects is not equal return true, if is equal return false
bool ConnectFour::Cell::operator != (const Cell & other) const 
{
	return !(*this == other);
}

// prefix ++ operator for Cell class
ConnectFour::Cell ConnectFour::Cell::operator ++ ()
{
	if (content == '.')
		content = 'X';
	else if (content == 'X')
		content = 'O';
	else if (content == 'O')
		content = '.';
	return *this;
}

// postfix ++ operator for Cell class
ConnectFour::Cell ConnectFour::Cell::operator ++ (int ignore)
{
	Cell temp;
	temp.content = content;
	temp.position = position;
	temp.rowNumber = rowNumber;
	if (content == '.')
		content = 'X';
	else if (content == 'X')
		content = 'O';
	else if (content == 'O')
		content = '.';

	return temp;
}

// prefix -- operator for Cell class
ConnectFour::Cell ConnectFour::Cell::operator -- ()
{
	if (content == 'X')
		content = '.';
	else if (content == 'O')
		content = 'X';
	else if (content == '.')
		content = 'O';

	return *this;
}

// postfix operator for Cell class
ConnectFour::Cell ConnectFour::Cell::operator -- (int ignore)
{
	Cell temp;
	temp.content = content;
	temp.position = position;
	temp.rowNumber = rowNumber;
	if (content == 'X')
		content = '.';
	else if (content == 'O')
		content = 'X';
	else if (content == '.')
		content = 'O';

	return temp;
}

// display board on the screen
void ConnectFour::printBoard() const 
{
	char temp = 'a';
	cout << endl;
	for (int i = 0; i < width; i++)
		cout << temp++ << " ";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			cout << gameCells[i][j].getContent() << " ";
		cout << endl;
	}
}

// check the fullsness of game board
// if board is full, returns true, if not returns false
bool ConnectFour::isBoardFull() const
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			if (gameCells[i][j].getContent() == '.')
				return false;
	}
	return true;
}

// setter for Cell class
// it sets position and rowNumber of Cell object to given parameters
void ConnectFour::Cell::setPosition(char newPosition, int newRowNumber) 
{
	position = newPosition;
	rowNumber = newRowNumber;
}

// resize and sets ConnectFour class to given parameters
void ConnectFour::resizeAndSetBoard(int widthValue, int heightValue)
{
	for (int i = 0; i < height; i++) {
		delete [] gameCells[i];
		gameCells[i] = NULL;
	}
	delete [] gameCells;
	gameCells = NULL;

	width = widthValue;
	height = heightValue;

	gameCells = new Cell * [height];
	for (int i = 0; i < height; i++)
		gameCells[i] = new Cell [width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			gameCells[i][j].setPosition(static_cast<char>('a' + j), i);
}

// reads named fileName file and sets ConnectFour class to file information 
bool ConnectFour::readFileAndSetBoard(string fileName)
{
	ifstream inputFile;
	char temp;
	int tempInt = 0, tempWidth = 0, tempHeight = 0;
	string tempString;

	inputFile.open(fileName);
	if (inputFile.fail())
		return false;


	inputFile.get(temp);
	while (temp != '\n') {
		tempWidth++;
		inputFile.get(temp);
	}
	while(!inputFile.eof()) {
		if (temp == '\n')
			tempHeight++;
			inputFile.get(temp);
	}
	inputFile.close();

	inputFile.open(fileName);
	if (inputFile.fail())
		return false;
	resizeAndSetBoard(tempWidth, tempHeight);
	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			inputFile.get(temp);

			if (temp == '\n')
				inputFile.get(temp);
			if (temp  == '*')
				gameCells[i][j].setContent('.');
			else
				gameCells[i][j].setContent(temp);
		}
	}
	inputFile.close();
	return true;
}

// checks the legality of move
// if move is legal, return true, if not return false
bool ConnectFour::isMoveLegal(char move) const
{
	int temp = move - 'a';
	if (temp > width - 1)
		return false;
	else {
		for (int i = 0; i < height; i++) {
			if (gameCells[i][temp].getContent() == '.')
				return true;
		}
	}
	return false;
}

// find suitable row and column on board for given move
// row and column call by reference parameters
void ConnectFour::findMoveStatus(int & row, int & column, char move) const
{
	int temp;
	temp = height;
	column = move - 'a';
	while (gameCells[temp-1][column].getContent() != '.')
		temp--;
	row = temp - 1;
}

// check there is winner or not on game
// if there is a winner returns true, if not return false
bool ConnectFour::checkWinner(int row, int column) 
{

	int array1[7], array2[7];
	char temp, stat;
	int vertical = 0, horizontal = 0, diagonal1 = 0, diagonal2 = 0, i = 0, j = 0, k = 0, l = 0;

	if (order == 1)
		stat = 'X';
	else if (order == 2)
		stat = 'O';

	temp = tolower(stat);
	// check vertical
	for (i = row; i < height && gameCells[i][column].getContent() == stat; i++, vertical++) array1[k++] = i;
	if (vertical >= 4) {
		for (i = 0; i < 4; i++)
			gameCells[array1[i]][column].setContent(temp);
		return true;
	}
	// check horizontal
	for (i = 0; i < width; i++) {
		j = i;
		horizontal = 0; 
		k = 0;
		while (gameCells[row][j].getContent() == stat) {
			array2[k++] = j;
			horizontal++;
			j++;
		}
		if (horizontal >= 4) {
			for (i = 0; i < 4; i++)
				gameCells[row][array2[i]].setContent(temp);
			return true;
		}
	}
	// check diagonal1
	k = 0;
	l = 0; 
	for (i = row, j = column; i >= 0 && j < width && gameCells[i][j].getContent() == stat; i--, j++, diagonal1++) {
		array1[k++] = i;
		array2[l++] = j;
	}
	for (i = row, j = column; j >= 0 && i < height && gameCells[i][j].getContent() == stat; i++, j--, diagonal1++) {
		array1[k++] = i+1;
		array2[l++] = j-1;
	}
	if (diagonal1 > 4) {
		for (i = 0; i < 4; i++)
			gameCells[array1[i]][array2[i]].setContent(temp);
		return true;
	}
	// check diagonal2
	k = 0; 
	l = 0; 
	for (i = row, j = column; i >= 0 && j >= 0 && gameCells[i][j].getContent() == stat; i--, j--, diagonal2++) {
		array1[k++] = i;
		array2[l++] = j;
	}

	for (i = row, j = column; i < height && j < width && gameCells[i][j].getContent() == stat; i++, j++, diagonal2++) {
		array1[k++] = i+1;
		array2[l++] = j+1;
	}

	if (diagonal2 > 4) {
		for (i = 0; i < 4; i++) 
			gameCells[array1[i]][array2[i]].setContent(temp);
		return true;
	} 
	return false;
}

// make best move for computer
void ConnectFour::makeBestMove(int & row, int & column) 
{
	ConnectFour tempObje(*this);
	int i, j, temp;
	bool flag = false;
	char ch;


	tempObje.setOrder(2);
	for (i = 0; i < width; i++) {
		ch = 'a' + i;
		if (isMoveLegal(ch)) {
			findMoveStatus(row, column, ch);
			tempObje.gameCells[row][column].setContent('O');
			if (tempObje.checkWinner(row, column)) {
				flag = true;
				cout << "Computer's move is " << static_cast<char>('a'+column) <<endl;
				gameCells[row][column].setContent('O');
				break;
			}
			tempObje.gameCells[row][column].setContent('.');
	
		}
		else continue;
	}
	if (!flag) {
		tempObje.setOrder(1);
		for (i = 0; i < width; i++) {
			ch = 'a' + i;
			if (isMoveLegal(ch)) {
				findMoveStatus(row, column, ch);
				tempObje.gameCells[row][column].setContent('X');
				if (tempObje.checkWinner(row, column)) {
					flag = true;
					cout << "Computer's move is " << static_cast<char>('a'+column) <<endl;
					gameCells[row][column].setContent('O');
					break;
				}
				tempObje.gameCells[row][column].setContent('.');
			

			}
			else continue;
		}
	}
	while (!flag) {
		srand(time(NULL));
		temp = rand() % width;
		ch = 'a' + temp;
		if (isMoveLegal(ch)) {
			flag = true;
			findMoveStatus(row, column, ch);
			cout << "Computer's move is " << static_cast<char>('a'+column) << endl;
			gameCells[row][column].setContent('O');
		} 
	}
}

// read from file game information and resize vector and set member value to file information.
bool ConnectFour::readFromFile(string fileName)
{
	ifstream inputFile;
	char temp, tempChoice;
	int tempWidth, tempHeight, tempOrder, tempCount;

	inputFile.open(fileName);
	if (inputFile.fail())
		return false;
	inputFile >> tempWidth >> tempHeight >> tempOrder >> tempChoice >> tempCount;
	inputFile.get(temp);
	resizeAndSetBoard(tempWidth, tempHeight);
	order = tempOrder;
	choice = tempChoice;
	ConnectFour::Cell::setCount(tempCount);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			inputFile.get(temp);
			if (temp == '\n')
				inputFile.get(temp);
			gameCells[i][j].setContent(temp);
		}
	}
	inputFile.close();
	return true;
}

// write game information to given file
void ConnectFour::writeToFile(string fileName) const
{
	ofstream outputFile;

	outputFile.open(fileName);
	outputFile << width << " " << height << " " << order <<" "<< choice << " " << " " << ConnectFour::Cell::getCount() << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) 
			outputFile << gameCells[i][j].getContent();
		outputFile << endl;
	}
	outputFile.close();
	return;
}

// changes player order
void ConnectFour::changeOrder()
{
	if (order == 1)
		order = 2;
	else if (order == 2)
		order = 1;
	return;
}

// takes input from user and chec the validity of inputs
// according to given inputs, continues game
void ConnectFour::takeInput(string & instruction, string & fileName, char & move) 
{
	bool flag = true;

	if (choice == 'C' || choice == 'c')
		cout << "Make a move for player: ";
	else if (choice == 'P' || choice == 'p') {
		if (order == 1)
			cout << "Make a move for Player 1: ";
		else 
			cout << "Make a move for Player 2: ";
	}
	while (flag) {
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> instruction;
		if (cin.eof())
			endOfInput();
		if (instruction == "LOAD" || instruction == "load") {
			cin >> fileName;
			if (cin.eof())
				endOfInput();
			flag = false;
		}
		else if (instruction == "SAVE" || instruction == "save") {
			cin >> fileName;
			if (cin.eof())
				endOfInput();
			flag = false;
		}
		else {
			if (instruction.length() > 1)
				cerr << "\nCommand not found.Enter again: ";
			else {
				move = tolower(instruction.at(0));
				if (isMoveLegal(move)) {
					fileName = "\0";
					flag = false;
				}
				else
					cerr << "\nMove is not legal.Make move again: ";
			}
		}
	}
	return;
}

// plays game for single mode
void ConnectFour::playGame()
{
	char move, temp;
	int row, column;
	bool winner = false, flag = true;
	string instruction, fileName, fileName2;
	ifstream inputFile;

	cout << "Enter filename to start game." << endl;
	cin >> fileName2;
	if (cin.eof())
		endOfInput();
	while (!readFileAndSetBoard(fileName2)) {
		cerr << "\nFile is not found.Enter again: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> fileName2;
		if (cin.eof())
			endOfInput();
	}
	cout << "\nPress C for Computer - User." << endl;
	cout << "Press P for User - User." << endl;
	cin >> temp;
	if (cin.eof())
		endOfInput();
	cout << temp << endl;
	while (temp != 'C' && temp != 'c' && temp != 'P' && temp != 'p') {
		cerr << "\nYou made wrong choice.Try again! ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> temp;
		if (cin.eof())
			endOfInput();
	}
	choice = temp;
	printBoard();
	while (!isBoardFull()) {
		takeInput(instruction, fileName, move);
		if (instruction == "LOAD" || instruction == "load") {
			if (readFromFile(fileName)) {
				cout << "Game LOADED.\n";
				cout << "LOADED Game Started\n";
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
			}
			else 
				cerr << "File is not found.\n";
		}
		else if (instruction == "SAVE" || instruction == "save") {
			writeToFile(fileName);
			cout << "Game SAVED.\n";
			cout << "The Game Continues.\n";
			printBoard();
			cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
		}
		else {

			if (choice == 'c' || choice == 'C') {
				order = 1;
				if (play(move)) {
					winner = true;
					break;
				}
				changeOrder();
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
				if (play()) {
					winner = true;
					break;
				}
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
				changeOrder();
			}
			else if (choice == 'p' || choice == 'P') {
				findMoveStatus(row, column, move);
				if (order == 1) {
					gameCells[row][column].setContent('X');
					ConnectFour::Cell::setCount();
				}
				else if (order == 2) {
					gameCells[row][column].setContent('O');
					ConnectFour::Cell::setCount();
				}

				if (checkWinner(row, column)) {
					winner = true;
					break;
				}
				changeOrder();
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
			}
		}
	}
	if (winner) {
		printBoard();
		cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
		if (choice == 'c' || choice == 'C') {
			if (order == 1)
				cout << "Game Over. Player won!" << endl;
			else if (order == 2)
				cout << "Game Over. Computer won!" << endl;
		}
		else {
			printBoard();
			cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
			if (order == 1)
				cout << "Game Over. Player1 won!" << endl;
			else if (order == 2)
				cout << "Game Over. Player2 won!" << endl;
		}
	}
	else
		cout << "Game Over. Nobody won!" << endl;
	return;
}

// plays for computer
bool ConnectFour::play() 
{
	int row, column;
	makeBestMove(row, column);
	ConnectFour::Cell::setCount();
	if (checkWinner(row, column))
		return true;
	return false;
}

// plays for player1 or player acccording to given parameter
bool ConnectFour::play(char cellPosition)
{
	int row, column;
	findMoveStatus(row, column, cellPosition);
	if (order == 1)
		gameCells[row][column].setContent('X');
	else if (order == 2)
		gameCells[row][column].setContent('O');
	ConnectFour::Cell::setCount();
	if (checkWinner(row, column))
		return true;
	return false;
}

// plays game for multimode on one step
// if game finishs, return true, if not return false
bool ConnectFour::playOneStep()
{
	string instruction, fileName;
	char move;
	printBoard();
	for (int i = 0; i < 2; i++) {
		takeInput(instruction, fileName, move);
		if (instruction == "LOAD" || instruction == "load") {
			if (readFromFile(fileName)) {
				cout << "Game LOADED.\n";
				cout << "LOADED Game Started.\n";
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
			}
			else
				cerr << "\nFile is not found.\n";
		}
		else if (instruction == "SAVE" || instruction == "save") {
			writeToFile(fileName);
			cout << "Game SAVED.\n";
			cout << "The Game Continues.\n";
			printBoard();
			cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
		}
		else {
			if (choice == 'C' || choice == 'c') {
				if (play(move)) {
					printBoard();
					cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
					cout << "Winner : Player" << endl;
					return true;
				}
				changeOrder();
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
				if (play()) {
					printBoard();
					cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
					cout << "Winner : Computer" << endl;
					return true;
				}
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
				changeOrder();
				i++;
			}
			else if (choice == 'P' || choice == 'p') {
				if (play(move)) {
					printBoard();
					cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
					if (order == 1)
						cout << "Winner : Player1" << endl;
					else if (order == 2)
						cout << "Winner : Player2" << endl;
					return true;
				}
				changeOrder();
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
			}
		}
	}
	if (isBoardFull()) {
		cout << "Nobody won!" << endl;
		return true;
	}
	return false;
}

// stream insertion operator for Cell class
istream & operator >> (istream & inputStream,  ConnectFour::Cell & cellObject)
{
	cout << "Enter Position of Cell: ";
	inputStream >> cellObject.position; 
	cout << "Enter Row Number of Cell: ";
	inputStream >> cellObject.rowNumber; 
	cout << "Enter Content of Cell: ";
	inputStream >> cellObject.content; 
	return inputStream;
}

// stream extraction for Cell class
ostream & operator << (ostream & outStream, const  ConnectFour::Cell & cellObject)
{

	outStream << "Position of Cell = " << cellObject.getPosition() << endl;
	outStream << "Row number of Cell = " << cellObject.getRowNumber() << endl;
	outStream << "Content of Cell = " << cellObject.getContent() << endl;
	return outStream;
}

// if inputs come to end of file exits program
void endOfInput()
{
	cout << "\nEnd of input file.Program is closing..." << endl;
	exit(1);
}