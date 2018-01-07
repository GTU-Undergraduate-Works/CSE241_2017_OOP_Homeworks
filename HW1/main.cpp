/*
 * File:   main.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 1, 2017, 11:00 PM
 * This file include main function and toher functions
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctype.h>
#include "connectfour.h"

using namespace std;

int main(void) {

	char board[MAXSIZE][MAXSIZE];
	int size;
	char ch, choice;
	bool flag1= true, flag2 = true;

	cout << "Enter the size of the board to play game: ";
	cin >> size; 

	// checking board size 
	while (flag2) {
		if (size < 4 || size > 20 || size % 2 == 1) {
			cerr << "Size is must be 4,6,8,10,12,14,16,18 or 20.Enter again:" <<endl;
			cin.clear();
			cin.ignore(1000,'\n');
			cin >> size;
		}
		else
			flag2 = false;
	}
	// initialization of board array
	initializeBoardArray(board, size);

	// user choices which play game 
	cout << "Press C for Computer - User." <<endl;
	cout <<	"Press P for User - User." <<endl;
	cin >> choice;
	
	while (flag1) {

		switch (choice) {

			case 'C':	
			case 'c':
						printBoard(board, size);
						playWithOnepalyer(board, size);
						flag1= false;
						break;
			case 'P':	
			case 'p':
						printBoard(board, size);
						playWithTwoPlayers(board, size);
						flag1= false;
						break;

			default :	
						cerr << "You pressed wrong key.Try again: ";
						cin.clear();
						cin.ignore(1000,'\n');
						cin >> choice;
			}
	}
	return 0;
}

