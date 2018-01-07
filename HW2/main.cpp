/*
 * File:   main.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 8, 2017, 1:00 PM
 * This file include connectfour game implementation
 */


#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <string>
#define MAXSIZE 20
using namespace std;

/* enumarated type for palce of board */
enum Place {
	empty, user1, user2
};

// read from file game information (board, size, order and choice of game)
bool readFromFile(const string fileName, char board[][MAXSIZE], int &size, int &order, char &choice);

// write to file game information 
void writeToFile(const string fileName, const char board[][MAXSIZE], const int &size, const int &order, const char &choice);

// check fullness of board
bool checkBoard(const char board[][MAXSIZE], const int &size);

// take game information from user
void takeInput(char board[][MAXSIZE], const int &size, const int &order, const char &choice, char &move, string &instruction, string &fileName);

// initialize board to '.'
void initializeBoardArray(char board[][MAXSIZE], int size);

// finds suaitable loacation on board for move
void findRowAndColumn(char board[][MAXSIZE], char move, int& row, int& column, int size);

// prinsts board to screen
void printBoard(const char board[][MAXSIZE], const int &size);

// check given move whis is legal or not
bool isMoveLegal(const char board[][MAXSIZE], const char move, const int size); 

// make best move for computer
void makeBestMove(char board[][MAXSIZE], int size, int &row, int &column, int &order);

// checks winner of game
bool checkWinner(char board[][MAXSIZE], int row, int column, int size, int order = 2);

// starts game according to given choice
void startGame(char board[][MAXSIZE], int size, char choice);

// updates board array according to given parameters
void updateBoardArray(char board[][MAXSIZE], int row, int column, int &order);

// plays game 
void playGame(char board[][MAXSIZE], int size, char choice);

int main() {

	char board[MAXSIZE][MAXSIZE], choice;
	int size;
	bool flag = true;

	cout << "Enter the size of the board to play game: ";
	cin >> size;

	// controls input
	while (flag) {
		if (size < 4 || size > 20 || size % 2 == 1) {
			cerr << "Size is must be 4,6,8,10,12,14,16,18 or 20.Enter again:" <<endl;
			cin.clear();
			cin.ignore();
			cin >> size;
		}
		else
			flag = false;
	}
	cout << "Press C for Computer - User." <<endl;
	cout <<	"Press P for User - User." <<endl;
	cin >> choice;

	// control input validity
	while  (choice != 'C' && choice != 'c' && choice != 'P' && choice != 'p') {
		cerr << "You made wrong choice.Try again! ";
		cin.clear();
		cin.ignore();
		cin >> choice;
	}
	// starts game;
	startGame(board, size, choice);
	return 0;
}

void playGame(char board[][MAXSIZE], int size, char choice) {

	auto order = 1;
	auto winner = false;
	int row, column;
	char move;
	string instruction, fileName;

	// the loop continues up to fill game board
	while (checkBoard(board, size)) {
		takeInput(board, size, order, choice, move, instruction, fileName);
		if (instruction == "LOAD" || instruction == "load") {
			if (readFromFile(fileName, board, size, order, choice)) {
				cout << "Game LOADED.\n";
				cout << "LOADED Game Started\n";
				printBoard(board, size);
			}
			else	
				cerr << "File  is not found.\n";
		}
		else if (instruction == "SAVE" || instruction == "save") {
			writeToFile(fileName, board, size, order, choice);
			cout << "Game SAVED.\n";
			cout << "The Game Continues.\n";
			printBoard(board, size);
		}
		else {

			if (choice == 'c' || choice == 'C') {
				findRowAndColumn(board, move, row, column, size);
				updateBoardArray(board, row, column, order);
				// if one of the player wins, game finsih.
				if (checkWinner(board, row, column, size, order)) {
					winner = true;
					break;
				}
				printBoard(board, size);
				makeBestMove(board, size, row, column, order);
				// if computer wins, game finish
				if (checkWinner(board, row, column, size, order)) {
					winner = true;
					break;
				}
				printBoard(board, size);
			}
			else if (choice == 'p' || choice == 'P') {
				findRowAndColumn(board, move, row, column, size);
				updateBoardArray(board, row, column, order);
				// if one of the player wins, game finsih.
				if (checkWinner(board, row, column, size, order)) {
					winner = true;
					break;
				}
				printBoard(board, size);
			}
		}
	}
	// print that wh wins game
	if (winner) {
		printBoard(board, size);
		if (choice == 'c' || choice == 'C') {
			if (order == 2)
				cout << "Game Over. Player won!" << endl;
			else
				cout << "Game Over. Computer won!" << endl;
		}
		else {
			if (order == 2)
				cout << "Game Over. Player1 won!" << endl;
			else
				cout << "Game Over. Player2 won!" << endl;
		}
	}
	else 
		cout << "Game Over. Nobody won!" << endl;
	return;
}

// read from file game information to call by reference parameters to load new game
// if file open fails return false, if not return true
bool readFromFile(const string fileName, char board[][MAXSIZE], int &size, int &order, char &choice) {

	ifstream inputFile;

	inputFile.open(fileName);
	if (inputFile.fail())
		return false;
	inputFile >> size >> choice >> order;
	for (int i = 0; i < size; i++) 
		for (int j = 0; j < size; j++) 
			inputFile >> board[i][j];

	inputFile.close();
	return true;
}

// write to game information to given file to save game
void writeToFile(const string fileName, const char board[][MAXSIZE], const int &size, const int &order, const char &choice) {

	ofstream outputFile;

	outputFile.open(fileName);
	outputFile << size << " " << choice << " " << order << endl;
	for (int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++)
			outputFile << board[i][j] << " ";
		outputFile << endl;
	}
	outputFile.close();
	return;
}

// check the fullnes of game board
// if board is full retyrn false, if not return true
bool checkBoard(const char board[][MAXSIZE], const int &size) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == '.')
				return true;
		}
	}
	return false;
}

// takes input from user according to given constant call by reference parameters
void takeInput(char board[][MAXSIZE], const int &size, const int &order, const char &choice, char &move, string &instruction, string &fileName) {

	auto flag = true;

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
		cin.ignore();
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
				if (isMoveLegal(board, move, size)) {
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

// anitialize board array to '.'
void initializeBoardArray(char board[][MAXSIZE], int size) {

	for (int i = 0; i < size; ++i) 
		for (int j = 0; j < size; ++j)
			board[i][j] = '.';
	return;
}

// prints size*size board matrix on screen
void printBoard(const char board[][MAXSIZE], const int &size) {

	int i,j;
	auto temp = 'a';
	cout << endl;
	for (i = 0; i < size; ++i) {
		temp = 'a' + i;
		cout <<temp<<" ";
	}
	cout <<endl;
	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j)
			cout << board[i][j] <<" ";
		cout<<endl;
	}
	cout<<endl;
	return;
}

// finds row and column of given move
// row and column call by reference parameter
void findRowAndColumn(char board[][MAXSIZE], char move, int& row, int& column, int size) {

	column = move - 'a';
	while (board[size-1][column] != '.')
		size--;
	row = size-1;
	return;
}

// check the legality of move
// if move is legal return ture, if is not legal return false
bool isMoveLegal(const char board[][MAXSIZE], const char move, const int size) {

	decltype(move - 'a') temp = move - 'a';
	if (temp > size-1 || board[0][temp] != '.')
		return false;
	return true;
}

// select best move of computer
// row and column call by reference parameters
void makeBestMove(char board[][MAXSIZE], int size, int &row, int &column, int &order) {

	int i,j, temp;
	char tempArray[MAXSIZE][MAXSIZE], ch;
	auto flag = false;

	// copy real array to tem array
	for (i = 0; i < size; i++) 
		for (j = 0; j < size; j++)
			tempArray[i][j] = board[i][j];

	for (i = 0; i < size; i++) {
		ch = 'a' + i;
		if (isMoveLegal(board, ch, size)) {
			findRowAndColumn(tempArray, ch, row, column, size);
			tempArray[row][column] = 'O';
			if (checkWinner(tempArray, row, column, size, user1)) {
				flag = true;
				cout << "Computer's move is " << static_cast<char>('a'+column) <<endl;
				updateBoardArray(board, row, column, order);
				break;
			}
			tempArray[row][column] = '.';
		}
		else continue;
	}
	if (!flag) {
		for (i = 0; i < size; i++) {
			ch = 'a' + i;
			if (isMoveLegal(board, ch, size)) {
				findRowAndColumn(tempArray, ch, row, column, size);
				tempArray[row][column] = 'X';
				if (checkWinner(tempArray, row, column, size, user2)) {
					flag = true;
					cout << "Computer's move is " << static_cast<char>('a'+column) << endl;
					updateBoardArray(board, row, column, order);
					break;
				}
				tempArray[row][column] = '.';
			}
			else continue;
		}
	}
	while (!flag) {
		srand(time(NULL));
		temp = rand() % size;
		ch = 'a' + temp;
		if (isMoveLegal(board, ch, size)) {
			flag = true;
			findRowAndColumn(tempArray, ch, row, column, size);
			cout << "Computer's move is " << static_cast<char>('a'+column) << endl;
			updateBoardArray(board, row, column, order);
		} 
	}
	return;
}

// checks winner of game
// if there is winner return true, if not return false
bool checkWinner(char board[][MAXSIZE], int row, int column, int size, int order) {

	auto i = 0, j = 0, k = 0, l = 0, vertical = 0, horizontal = 0, diagonal1 = 0, diagonal2 = 0;
	int array1[7], array2[7];
	char ch, temp;

	if (order == 1)
		ch = 'O';
	else if (order == 2)
		ch = 'X';

	temp = tolower(ch);
	// check vertical
	for (i = row; board[i][column] == ch && i < size; i++, vertical++) array1[k++] = i;
	if (vertical >= 4) {
		for (i = 0; i < 4; i++) 
			board[array1[i]][column] = temp;
		return true;
	}

	// check horizontal
	for (i = 0; i < size; i++) {
		j = i;
		horizontal = 0;
		k = 0; 
		while (board[row][j] == ch) {
			array2[k++] = j;
			horizontal++;
			j++;
		}
		if (horizontal >= 4) {
			for (i = 0; i < 4; i++)
				board[row][array2[i]] = temp;
			break;
		}
	}
	if (horizontal >= 4)
		return true;

	// check diagogal 1
	k = 0; 
	l = 0;
	for (i = row, j = column; board[i][j] == ch && i >= 0 && j < size; i--, j++, diagonal1++) {
		array1[k++] = i;
		array2[l++] = j;
	}
	for (i = row, j = column; board[i][j] == ch && i < size && j >= 0; i++, j--, diagonal1++) {
		array1[k++] = i+1;
		array2[l++] = j-1;
	}
	if (diagonal1 > 4) {
		for (i = 0; i < 4; i++) 
			board[array1[i]][array2[i]] = temp;
		return true;
	}
	// check diagonal2
	k = 0;
	l = 0;
	for (i = row, j = column; board[i][j] == ch && i >= 0 && j >= 0; i--, j--, diagonal2++) {
		array1[k++] = i;
		array2[l++] = j;
	}
	for (i = row, j = column; board[i][j] == ch && i < size && j < size; i++, j++, diagonal2++) {
		array1[k++] = i+1;
		array2[l++] = j+1;
	}
	if (diagonal2 > 4) {
		for (i = 0; i < 4; i++)
			board[array1[i]][array2[i]] = temp;
		return true;
	}
	return false;
}

// starts game
void startGame(char board[][MAXSIZE], int size, char choice) {

	initializeBoardArray(board, size);
	printBoard(board, size);
	playGame(board, size, choice);
	return;
}

// update game board given row, column and order
// after update board, turn order
void updateBoardArray(char board[][MAXSIZE], int row, int column, int &order) {

	switch (order) {
		
		case 1 :
					board[row][column] = 'X';
					order = 2;
					break;
		case 2 :		
					board[row][column] = 'O';
					order = 1;
					break;
	}
	return;
} 







