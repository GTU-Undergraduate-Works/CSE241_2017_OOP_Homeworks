/*
 * File:   connectfour.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 18, 2017, 11:00 PM
 * This file includes all member functions of classes.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include "connectfour.h"
using namespace std;

int ConnectFour::Cell::count = 0;

// no parameter constructor for ConnectFour class
ConnectFour::ConnectFour() 
				:order(1), width(0), height(0), choice('p')
{ /* intentionally empty */}

// two parameter constructor for ConnectFOur  class
ConnectFour::ConnectFour(int widthValue, int heightValue) 
							:width(widthValue), height(heightValue), order(1)
{
	gameCells.resize(height);
	for (int i = 0; i < height; i++)
		gameCells[i].resize(width);
	for (int i = 0; i < height; i++) 
		for (int j = 0; j < width; j++)
			gameCells[i][j].setPosition(static_cast<char>('a'+j), i);
}

// three parameters constructor for Connectr-four class
ConnectFour::ConnectFour(int widthValue, int heightValue, char choiceValue) 
					:width(widthValue), height(heightValue), choice(choiceValue)
{ /* Inetintionally empty */ }

//no parameter constructor for Cell class
ConnectFour::Cell::Cell()
			: position('A'), rowNumber(0), content('.')
{ /* intentionally empty */}


// takes input from user and chec the validity of inputs
// according to given inputs, continues game
void ConnectFour::takeInput(string & instruction, string & fileName, char & move) 
{
	bool flag = true;

	if (getChoice() == 'C' || getChoice() == 'c')
		cout << "Make a move for player: ";
	else if (getChoice() == 'P' || getChoice() == 'p') {
		if (getOrder() == 1)
			cout << "Make a move for Player 1: ";
		else 
			cout << "Make a move for Player 2: ";
	}
	while (flag) {
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> instruction;
		if (instruction == "LOAD" || instruction == "load") {
			cin >> fileName;
			flag = false;
		}
		else if (instruction == "SAVE" || instruction == "save") {
			cin >> fileName;
			flag = false;
		}
		else {
			if (instruction.length() > 1)
				cerr << "Command not found.Enter again: ";
			else {
				move = tolower(instruction.at(0));
				if (isMoveLegal(move)) {
					fileName = "\0";
					flag = false;
				}
				else
					cerr << "Move is not legal.Make move again: ";
			}
		}
	}
	return;
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

// check legality of given move
// if move is legal return true, if not returns false
bool ConnectFour::isMoveLegal(char & move) const 
{
	int temp = move - 'a';
	if (temp > width-1 || gameCells[0][temp].getContent() != '.')
		return false;
	return true;
}

// check board is full or not
// if board is full return true, if not returns false
bool ConnectFour::isBoardFull() const 
{
	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++)
			if (gameCells[i][j].getContent() == '.')
				return false;
	}
	return true;
}

// check there is winner or not on game
// if there is a winner returns true, if not return false
bool ConnectFour::checkWinner(int row, int column) 
{

	int array1[7], array2[7];
	char temp, stat;
	int vertical = 0, horizontal = 0, diagonal1 = 0, diagonal2 = 0, i = 0, j = 0, k = 0, l = 0;

	if (getOrder() == 1)
		stat = 'X';
	else if (getOrder() == 2)
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

// prints board on the screen.
void ConnectFour::printBoard() const 
{
	char temp = 'a';
	for (int i = 0; i < width; i++)
		cout << temp++ << " ";
	cout << endl;

	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++)
			cout << gameCells[i][j].getContent() << " ";
		cout << endl;
	}
}
// compares two games
// if firs game is better than other returns true, if not returns false
bool ConnectFour::compareGames(ConnectFour & other) 
{
	int i, row, column;
	char ch;
	bool flag = false;

	for (i = 0; i < width; i++) {
		ch = 'a' + i;
		if (isMoveLegal(ch)) {
			findMoveStatus(row, column, ch);
			gameCells[row][column].setContent('X');
			if (getOrder() == 2) {
				changeOrder();
				flag = true;
			}
			if (checkWinner(row, column)) {
				gameCells[row][column].setContent('.');
				if (flag)
					changeOrder();
				return true;
			}
			gameCells[row][column].setContent('.');
			if (flag)
				changeOrder();
		}
		else continue;
	}
	flag = false;
	for (i = 0; i < other.getWidth(); i++) {
		ch = 'a' + i;
		if (other.isMoveLegal(ch)) {
			other.findMoveStatus(row, column, ch);
			other.gameCells[row][column].setContent('X');
			if (other.getOrder() == 2) {
				other.changeOrder();
				flag = true;
			}
			if (other.checkWinner(row, column)) {
				other.gameCells[row][column].setContent('.');
				if (flag)
					other.changeOrder();
				return false;
			}
			other.gameCells[row][column].setContent('.');
			if (flag)
				other.changeOrder();
		}
		else continue;
	}
}

// make best move for computer
void ConnectFour::makeBestMove(int & row, int & column) 
{
	ConnectFour tempObje;
	int i, j, temp;
	bool flag = false;
	char ch;

	tempObje.gameCells.resize(height);
	for (i = 0; i < height; i++)
		tempObje.gameCells[i].resize(width);
	for (i = 0; i < height; i++) 
		for (j = 0; j < width; j++)
			tempObje.gameCells[i][j].setPosition(static_cast<char>('a'+j), i);

	for (i = 0; i < height; i++) {

		for (j = 0; j < width; j++)
			tempObje.gameCells[i][j].setContent(gameCells[i][j].getContent());
	}

	tempObje.setWidthAndHeight(width, height);

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
	setWidthAndHeight(tempWidth, tempHeight);
	gameCells.resize(height);
	for (int i = 0; i < height; i++)
		gameCells[i].resize(width);
	setOrder(tempOrder);
	setChoice(tempChoice);
	ConnectFour::Cell::setCount(tempCount);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			inputFile >> temp;
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
	outputFile << getWidth() << " " << getHeight() << " " << getOrder() <<" "<< getChoice() << " " << ConnectFour::Cell::getCount() <<endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) 
			outputFile << gameCells[i][j].getContent() << " ";
		outputFile << endl;
	}
	outputFile.close();
	return;
}

// plays game for moltimode
// ig gme finishs, return true, if not return false
bool ConnectFour::play() {

	string instruction, fileName;
	int row, column;
	char move;
	printBoard();

	for (int i = 0; i < 2; i++) {
		takeInput(instruction, fileName, move);
		if (instruction == "LOAD" || instruction == "load") {
			if (readFromFile(fileName)) {
				cout << "Game LOADED.\n";
				cout << "LOADED Game Started\n";
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
			}
		else	
			cerr << "File  is not found.\n";
		}
		else if (instruction == "SAVE" || instruction == "save") {
			writeToFile(fileName);
			cout << "Game SAVED.\n";
			cout << "The Game Continues.\n";
			printBoard();
			cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
		}
		else {

			if (getChoice() == 'C' || getChoice() == 'c') {
				findMoveStatus(row, column, move);
				gameCells[row][column].setContent('X');
				ConnectFour::Cell::setCount();
				if (checkWinner(row, column)) {
					printBoard();
					cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
					cout << "Winner : Player" << endl;
					return true;
				}
				changeOrder();
				printBoard();
				makeBestMove(row, column);
				if (checkWinner(row, column)) {
					printBoard();
					cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
					cout << "Winner : Computer" << endl;
					return true;
				}
				ConnectFour::Cell::setCount();
				printBoard();
				changeOrder();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
				i++;
			}
			else if (getChoice() == 'P' || getChoice() == 'p') {
				findMoveStatus(row, column, move);
				if (getOrder() == 1) {
					gameCells[row][column].setContent('X');
					ConnectFour::Cell::setCount();
					if (checkWinner(row, column)) {
						printBoard();
						cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
						cout << "Winner : Player1" << endl;
						return true;
					}
				}
				else if (getOrder() == 2) {
					gameCells[row][column].setContent('O');
					ConnectFour::Cell::setCount();
					if (checkWinner(row, column)) {
						printBoard();
						cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
						cout << "Winner : Player2" << endl;
						return true;
					}
					
				}
				changeOrder();
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;

			}
		}
		
	}
	if (isBoardFull()) {
		cout << "Nobody won !" << endl;
		return true;
	}
	return false;

}


// plays game for single mode
void ConnectFour::playGame() {

	
	char move, temp;
	int row, column;
	bool winner = false, flag = true;
	string instruction, fileName;

	
	cout << "Enter width and height of game board to start game\n";
	cin >> width >> height;
	while (width < 4 || height < 4 || width > 26) {
		cin.clear();
		cin.ignore(1000, '\n');
		cerr << "You entered wrong width or wrong height.\n"
			 << "Width and height must be greater than 4 and width must be smaller than 27.\n"
			 << "Enter width and height again: ";
		cin >> width >> height;
	}
	cout << "\nPress C for Computer - User." <<endl;
	cout <<	"Press P for User - User." <<endl;
	cin >> temp;
	setChoice(temp);
	// control input validity
	while  (getChoice() != 'C' && getChoice() != 'c' && getChoice() != 'P' && getChoice() != 'p') {
		cin.clear();
		cin.ignore(1000, '\n');
		cerr << "You made wrong choice.Try again! ";
		cin >> temp;
		setChoice(temp);
	}

	resizeAndSetBoard(width, height);
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
				cerr << "File  is not found.\n";
		}
		else if (instruction == "SAVE" || instruction == "save") {
			writeToFile(fileName);
			cout << "Game SAVED.\n";
			cout << "The Game Continues.\n";
			printBoard();
			cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
		}
		else {

			if (getChoice() == 'c' || getChoice() == 'C') {

				setOrder(1);
				findMoveStatus(row, column, move);
				gameCells[row][column].setContent('X');
				ConnectFour::Cell::setCount();
				if (checkWinner(row, column)) {
					winner = true;
					break;
				}
				changeOrder();
				printBoard();
				makeBestMove(row, column);
				ConnectFour::Cell::setCount();
				if (checkWinner(row, column)) {
					winner = true;
					break;
				}
				printBoard();
				cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
				changeOrder();

			}
			else if (getChoice() == 'p' || getChoice() == 'P') {
				findMoveStatus(row, column, move);
				if (getOrder() == 1) {
					gameCells[row][column].setContent('X');
					ConnectFour::Cell::setCount();
				}
				else if (getOrder() == 2) {
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
		if (getChoice() == 'c' || getChoice() == 'C') {
			if (order == 1)
				cout << "Game Over. Player won!" << endl;
			else if (order == 2)
				cout << "Game Over. Computer won!" << endl;
		}
		else {
			printBoard();
			cout << "Living Cells: " << ConnectFour::Cell::getCount() << endl;
			if (getOrder() == 1)
				cout << "Game Over. Player1 won!" << endl;
			else if (getOrder() == 2)
				cout << "Game Over. Player2 won!" << endl;
		}
	}
	else 
		cout << "Game Over. Nobody won!" << endl;

	return;
}

// according to given parameters, resize vector and set member of object
void ConnectFour::resizeAndSetBoard(int widthValue, int heightValue) 
{
	setWidthAndHeight(widthValue, heightValue);
	gameCells.resize(heightValue);
	for (int i = 0; i < heightValue; i++)
		gameCells[i].resize(widthValue);

	for (int i = 0; i < heightValue; i++) 
		for (int j = 0; j < widthValue; j++)
			gameCells[i][j].setPosition(static_cast<char>('a'+j), i);
}

// according to given parameters sets position of cell object
void ConnectFour::Cell::setPosition(char newPosition, int newRowNumber) 
{
	position = newPosition;
	rowNumber = newRowNumber;
}

// set width and height member of object according to given parameter
void ConnectFour::setWidthAndHeight(int newWidth, int newHeight) 
{	
	width = newWidth;
	height = newHeight;
}

// changes order
void ConnectFour::changeOrder() 
{
	if (getOrder() == 1)
		setOrder(2);
	else if (order == 2)
		setOrder(1);
}