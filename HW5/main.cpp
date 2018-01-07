/*
 * File:   main.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on November 23, 2017, 11:00 A.M
 * This file is driver file of Connectfour game 
 */

#include <iostream>
#include "Cell.h"
#include "ConnectFourAbstract.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlus.h"
#include "ConnectFourPlusUndo.h"
using namespace std;
using namespace DurakliEfkanConnectFour;


int main() {

    char type;
    bool  flag = true;
    int height, width;
    cout << "Enter game type to start game: ";
    cin >> type;
    if (cin.eof())
        endOfInput();
    while (flag) {

        if (type == 'P' || type == 'p' ||
                type == 'D' || type == 'd' ||
                type == 'U' || type == 'u')
            flag = false;
        else {
            cerr << "You made wrong choice!Enter again:\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> type;
            if (cin.eof())
                endOfInput();
        }
    }
    cout << "Enter height of game board: ";
    cin >> height;
    if (cin.eof())
        endOfInput();
    while (height < 4) {
        cerr << "Height must be greater than 4!Enter again:\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> height;
        if (cin.eof())
            endOfInput();
    }
    cout << "Enter width of game board: ";
    cin >> width;
    if (cin.eof())
        endOfInput();
    while (width < 4 || width > 26) {
        cerr << "Width must be between 4 and 26!Enter again:\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> width;
        if (cin.eof())
            endOfInput();
    }
    if (type == 'P' || type == 'p') {
        ConnectFourPlus game(height, width);
        game.playGame();
    }
    else if (type == 'D' || type == 'd') {
        ConnectFourDiag game(height, width);
        game.playGame();
    }
    else {
        ConnectFourPlusUndo game(height, width);
        game.playGame();
    }
    return 0;
}