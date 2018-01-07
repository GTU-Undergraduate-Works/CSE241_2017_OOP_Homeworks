/*
 * File:   main.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on November 7, 2017, 11:00 A.M
 * This file include main function and other golabal functions
 */

#include <iostream>
#include "connectfour.h"
using namespace std;

// global function for Multi Mode Game
void playMultiMode();

// global function for Single Mode
void playSingleMode();

int main() {

	char mode;
	string fileName;
	bool flag = true;
	cout << "\nWELCOME TO CONNECTFOUR GAME\n"
		 << "\nSELECT GAME MODE TO START GAME.\n"
		 << "Press S for SINGLE MODE\n"
		 << "Press M for MULTI MODE" << endl;
	cin >> mode;
	if (cin.eof())
		endOfInput();
	while (flag) {
		switch(mode) {

			case 'S':
			case 's':
						playSingleMode();
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
						cerr << "\nYou made wrong choice! Try again: ";
						cin >> mode;
						if (cin.eof())
							endOfInput();
		}
	}
	return 0;
}


// global function that plays game for Multimode
// created 5 ConnectFour object
void playMultiMode() 
{
	ConnectFour array[5];
	int width, height, i, index, counter1 = 0, counter2 = 0, tempInt, arr[5];
	char temp;
	string fileName;

	for (i = 0; i < 5; i++)
		arr[i] = 1;

	for (i = 0; i < 5; i++) {
		cout << "\nObject" << i+1 << ":" << endl;
		cout << "Enter filename: ";
		cin >> fileName;
		if (cin.eof())
			endOfInput();
		while (!array[i].readFileAndSetBoard(fileName)) {
			cerr << "\nFile is not found.Enter again: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> fileName;
			if (cin.eof())
				endOfInput();
		}
		cout << "player | computer : ";
		cin >> temp;
		if (cin.eof())
			endOfInput();
		while (temp != 'C' && temp != 'c' && temp != 'P' && temp != 'p') {
			cerr << "\nYou  made wrong choice. Try again: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> temp;
			if (cin.eof())
				endOfInput();
		}
		array[i].setChoice(temp);
	}
	while (counter2 < 5) {
		cout << "\nSelect object: ";
		cin >> index;
		if (cin.eof())
			endOfInput();
		while (index > 5 || index < 1) {
			cerr << "\nNumber must be between 1 and 5! Enter again: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> index;
			if (cin.eof())
				endOfInput();
		}
		if (arr[index-1] == -1) {
			cout << "Object" << index << "'s game is over! " << endl;
			continue;
		}
		if (array[index-1].playOneStep()) {
			arr[index-1] = -1;
			counter2++;
		}
		if (counter1 > 0 && tempInt != index-1 && arr[tempInt] != -1) {
			if (array[index-1] == array[tempInt])
				cout << "\nObject" << index << " = Object" << tempInt+1 << endl;
			else
				cout << "\nObject" << index << " != Object" << tempInt+1 << endl;		
		}
		counter1++;
		tempInt = index-1;
	}
	cout << "All object's game is over!\n"
	     << "Program is closing..." << endl;
	return;
}

// global function that plays game for single mode
void playSingleMode() {
	
	ConnectFour game;
	game.playGame();
}