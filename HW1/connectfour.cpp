/*
 * File:   connectfour.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 1, 2017, 11:00 PM
 * This file includes implemamtion of functions
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctype.h>
#include "connectfour.h"

using namespace std;


// prints size*size board matrix on screen
void printBoard(char board[][MAXSIZE], int size) {

	int i,j;
	char temp = 'a';
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

// anitialize board array to '.'
void initializeBoardArray(char board[][MAXSIZE], int size) {

	int i,j;
	for (i = 0; i < size; ++i) 
		for (j = 0; j < size; ++j)
			board[i][j] = '.';
	return;
}

void updateBoardArray(char board[][MAXSIZE], int row, int column, Place location) {

	switch (location) {

		case user1 :
					board[row][column] = 'X';
					break;

		case user2 :		
					board[row][column] = 'O';
					break;
	}
	return;
} 

void playWithTwoPlayers(char board[][MAXSIZE], int size) {

	char move1, move2;
	int i, row1, row2, column1, column2;
	bool winner1 = false, winner2 = false;

	for (i = 0; i < pow(size,2)/2; i++) {
		takeInputFromUSer1(board, move1, size);
		findRowAndColumn(board, move1, row1, column1, size);
		updateBoardArray(board, row1, column1, user1);
		printBoard(board, size);
		// check player 1 won game, if player 1 won game, game finishes 
		if (checkWinner(board, row1, column1, size, user1)) {
			winner1 = true;
			break;
		}
		// check player 1 won game, if player 1 wins game, game finishes 
		takeInputFromUSer2(board, move2, size);
		findRowAndColumn(board, move2, row2, column2, size);
		updateBoardArray(board, row2, column2, user2);
		printBoard(board, size);
		if (checkWinner(board, row2, column2, size, user2)) {
			winner2 = true;
			break;
		}
	}
	printBoard(board, size);
	if (winner1)
		cout << "Game Over. Player1 won !" <<endl;
	else if (winner2)
		cout << "Game Over. Player2 won !" <<endl;
	else
		cout << "Game Over. Nobody won !" <<endl;
	
	return;
}

// check the legality of move
// if move is legal return ture, if is not legal return false
bool isMoveLegal(char board[][MAXSIZE], char move, int size) {

	int temp;
	temp = move - 'a';
	if (temp > size-1 || board[0][temp] != '.')
		return false;
	return true;
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

// takes input from user1
// if input is not legal, takes input again.
void takeInputFromUSer1(char board[][MAXSIZE], char& move, int size) {

	bool flag = true;
	cout << "Make a move for Player1:";

	while (flag) {
		cin >> move;
		move = tolower(move);
		if (isMoveLegal(board, move, size))
			flag = false;
		else
			cerr << "Move is not legal for Player1.Make move again:";
	}
	return;
}

// takes input from user2
// if input is not legal, takes input again.
void takeInputFromUSer2(char board[][MAXSIZE], char& move, int size) {

	bool flag = true;
	cout << "Make a move for Player2:";

	while (flag) {
		cin >> move;
		move = tolower(move);
		if (isMoveLegal(board, move, size))
			flag = false;
		else {
			cerr << "Move is not legal for Player2.Make move again:";
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}
	return;
}

// takes input from user
// if input is not legal, takes input again.
void takeInputFromUSer(char board[][MAXSIZE], char& move, int size) {

	bool flag = true;
	cout << "Make a move for Player:";

	while (flag) {
		cin >> move;
		move = tolower(move);
		if (isMoveLegal(board, move, size))
			flag = false;
		else {
			cerr << "Move is not legal for player.Make move again:";
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}
	return;
}

// checks winner of game
// if there is winner return true, if not return false
bool checkWinner(char board[][MAXSIZE], int row, int column, int size, Place location) {

	int i = 0,j = 0, k = 0, l = 0, vertical = 0, horizontal = 0, diagonal1 = 0, diagonal2 = 0;
	int array1[7], array2[7];
	char ch, temp;

	if (location == user1)
		ch = 'X';
	else if (location == user2)
		ch = 'O';

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

// play with computer
// if there is winner, finish game and print winner on screen
void playWithOnepalyer(char board[][MAXSIZE], int size) {

	char move;
	int i, row1, row2, column1, column2;
	bool winner1 = false, winner2 = false;

	for (i = 0; i < pow(size,2)/2; i++) {
		takeInputFromUSer(board, move, size);
		findRowAndColumn(board, move, row1, column1, size);
		updateBoardArray(board, row1, column1, user1);
		printBoard(board, size);
		if (checkWinner(board, row1, column1, size, user1)) {
			winner1 = true;
			break;
		}
		makeBestMove(board, size, row2, column2);
		printBoard(board, size);
		if (checkWinner(board, row2, column2, size, user2)) {
			winner2 = true;
			break;
		}
	}
	printBoard(board, size);
	if (winner1)
		cout << "Game Over. Player won !" <<endl;
	else if (winner2)
		cout << "Game Over. Computer won !" <<endl;
	else
		cout << "Game Over. Nobody won !" <<endl;

	return;
}

// select best move of computer
// row and column call by reference parameters
void makeBestMove(char board[][MAXSIZE], int size, int &row, int &column) {

	int i,j, temp;
	char tempArray[MAXSIZE][MAXSIZE], ch;
	bool flag = false;

	// copy real array to tem array
	for (i = 0; i < size; i++) 
		for (j = 0; j < size; j++)
			tempArray[i][j] = board[i][j];

	for (i = 0; i < size; i++) {
		ch = 'a' + i;
		if (isMoveLegal(board, ch, size)) {
			findRowAndColumn(tempArray, ch, row, column, size);
			tempArray[row][column] = 'O';
			if (checkWinner(tempArray, row, column, size, user2)) {
				flag = true;
				cout << "Computer's move is " << static_cast<char>('a'+column) <<endl;
				updateBoardArray(board, row, column, user2);
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
				if (checkWinner(tempArray, row, column, size, user1)) {
					flag = true;
					cout << "Computer's move is " << static_cast<char>('a'+column) << endl;
					updateBoardArray(board, row, column, user2);
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
			updateBoardArray(board, row, column, user2);
		} 
	}
	return;
}
