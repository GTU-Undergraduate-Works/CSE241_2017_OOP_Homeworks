/*
 * File:   main.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 18, 2017, 11:00 PM
 * This file include main function and other golabal functions
 */

#include <iostream>
#include "connectfour.h"
using namespace std;

// Global function that play moltimode game
void playMultiMode();

int main() {

	char mode;
	bool flag = true;
	ConnectFour game;
	cout << "\nWELCOME TO CONNECTFOUR GAME\n"
		 << "\nSELECT GAME MODE TO START GAME.\n"
		 << "Press S for SINGLE MODE\n"
		 << "Press M for MULTI MODE" << endl;
	cin >> mode;
	while (flag) {
		switch (mode) {

			case 'S':
			case 's':
						game.playGame();
						flag = false;
						break;

			case 'M':
			case 'm':
						playMultiMode();
						flag = false;
						break;

			default:	
						cin.clear();
						cin.ignore(1000, '\n');
						cerr << "You made wrong choice! Try again: ";
						cin >> mode;

		}
	}
	return 0;
}


// play game for multimode
void playMultiMode() {

	ConnectFour array[5];
	int width, height, i, index, counter1 = 0, counter2 = 0, tempInt, arr[5];
	char temp;
	// arrray for object that game finished.
	for (i = 0; i < 5; i++)
		arr[i] = 1;

	// take object information from user
	for (i = 0; i < 5; i++) {
		cout << "\nObject" << i+1 << ":" << endl;
		cout << "Enter width: ";
		cin >> width;
		cout << "Enter height: ";
		cin >> height;
		while (width < 4 || height < 4 || width > 26) {
			cin.clear();
			cin.ignore(1000, '\n');
			cerr << "You entered wrong width and height!\n"
				 << "Enter width again: ";
			cin >> width;
			cerr << "Enter height again:";
			cin >> height;
		}
		// according to given inputs, resize vector and set object members
		array[i].resizeAndSetBoard(width, height);
		cout << "player | computer : ";
		cin >> temp;
		while (temp != 'P' && temp != 'p' && temp != 'C' && temp != 'c') {
			cin.clear();
			cin.ignore(1000, '\n');
			cerr << "You made wrong choice. Try again: ";
			cin >> temp;
		}
		array[i].setChoice(temp);
	}
	// loop continues up to finish all games
	while (counter2 < 5) {
		cout << "\nSelect object: ";
		cin >> index;
		while (index > 5 || index < 1) {
			cin.clear();
			cin.ignore(1000, '\n');
			cerr << "Number must be between 1 and 5! Enter again: ";
			cin >> index;
		}
		if (arr[index-1] == -1) {
			cerr << "Object" << index << "'s game is over! " << endl;
			continue; 
		}
		if (array[index-1].play()) {
			arr[index-1] = -1;
			counter2++;
		}
		if (counter1 > 0 && tempInt != index-1 && arr[tempInt] != -1) {
			if (array[index-1].compareGames(array[tempInt]))
				cout << "Object" << index << " > Object" << tempInt+1 << endl;
			else
				 cout << "Object" << tempInt+1 << " > Object" << index <<endl;
		}
		counter1++;
		tempInt = index-1;
	}
	cout << "All object's game is over!\n"
		 << "Program is closing..." << endl;
	return; 
}