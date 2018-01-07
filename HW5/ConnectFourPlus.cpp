/*
 * File:   ConnectFourPlus.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on November 23, 2017, 11:00 A.M
 * This file is implemetation file ConnectFourPlus class 
 */

#include <iostream>
#include "ConnectFourPlus.h"
#include "Cell.h"
using namespace std;

namespace DurakliEfkanConnectFour {

    // one parameter constructor
    // initialize game board to  5x5
    ConnectFourPlus::ConnectFourPlus()
            : ConnectFourAbstract() { /* intentionally empty */}

    // two parameter constructor
    // initialize game board to heightValue x widthValue
    ConnectFourPlus::ConnectFourPlus(int heigtValue, int widthValue)
            : ConnectFourAbstract(heigtValue, widthValue) { /* inetentionally empty */}

    // copy constructor
    ConnectFourPlus::ConnectFourPlus(ConnectFourPlus &gameObject)
            : ConnectFourAbstract(gameObject) { /* inetntionally empty */}

    // find best move for computer and make these move
    void ConnectFourPlus::makeBestMove(int &row, int &column) {

        ConnectFourPlus tempObje(*this);
        int i, temp;
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
                    cout << "Computer's move is " << static_cast<char>('a' + column) << endl;
                    gameCells[row][column].setContent('O');
                    break;
                }
                tempObje.gameCells[row][column].setContent('.');

            } else continue;
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
                        cout << "Computer's move is " << static_cast<char>('a' + column) << endl;
                        gameCells[row][column].setContent('O');
                        break;
                    }
                    tempObje.gameCells[row][column].setContent('.');


                } else continue;
            }
        }
        while (!flag) {
            srand(time(NULL));
            temp = rand() % width;
            ch = 'a' + temp;
            if (isMoveLegal(ch)) {
                flag = true;
                findMoveStatus(row, column, ch);
                cout << "Computer's move is " << static_cast<char>('a' + column) << endl;
                gameCells[row][column].setContent('O');
            }
        }
    }

    // checks winners of game diagonally
    // if there is winner return true, if not return false
    bool ConnectFourPlus::checkWinner(int row, int column) {
        int array1[7], array2[7];
        char temp, stat;
        int vertical = 0, horizontal = 0, i, j, k = 0;

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


        return false;
    }

    // make move for computer
    bool ConnectFourPlus::play() {
        int row, column;
        makeBestMove(row, column);
        if (checkWinner(row, column))
            return true;
        return false;
    }

    // make move for users according to given cellPosition parameter
    bool ConnectFourPlus::play(char cellPosition) {
        int row, column;
        findMoveStatus(row, column, cellPosition);
        if (order == 1)
            gameCells[row][column].setContent('X');
        else if (order == 2)
            gameCells[row][column].setContent('O');
        if (checkWinner(row, column))
            return true;
        return false;
    }

    // tkes input from users
    void ConnectFourPlus::takeInput(string &instruction, string &fileName, char &move) {
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
            } else if (instruction == "SAVE" || instruction == "save") {
                cin >> fileName;
                if (cin.eof())
                    endOfInput();
                flag = false;
            } else {
                if (instruction.length() > 1)
                    cerr << "\nCommand not found.Enter again: ";
                else {
                    move = tolower(instruction.at(0));
                    if (isMoveLegal(move)) {
                        fileName = "\0";
                        flag = false;
                    } else
                        cerr << "\nMove is not legal.Make move again: ";
                }
            }
        }
        return;
    }

    // plays game until game finished
    void ConnectFourPlus::playGame() {
        char move, temp;
        bool winner = false;
        string instruction, fileName;

         cout << "\nPress C for Computer - User." << endl;
        cout << "Press P for User - User." << endl;
        cin >> temp;
        if (cin.eof())
            endOfInput();
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
                } else
                    cerr << "File is not found.\n";
            } else if (instruction == "SAVE" || instruction == "save") {

                writeToFile(fileName);
                cout << "Game SAVED.\n";
                cout << "The Game Continues.\n";
                printBoard();
            } else {

                if (choice == 'c' || choice == 'C') {
                    if (play(move)) {
                        winner = true;
                        break;
                    }
                    changeOrder();
                    printBoard();
                    if (play()) {
                        winner = true;
                        break;
                    }
                    printBoard();
                    changeOrder();
                } else if (choice == 'p' || choice == 'P') {
                    if (play(move)) {
                        winner = true;
                        break;
                    }
                    changeOrder();
                    printBoard();
                }
            }
        }
        if (winner) {
            printBoard();
            if (choice == 'c' || choice == 'C') {
                if (order == 1)
                    cout << "Game Over. Player won!" << endl;
                else if (order == 2)
                    cout << "Game Over. Computer won!" << endl;
            } else {
                printBoard();
                if (order == 1)
                    cout << "Game Over. Player1 won!" << endl;
                else if (order == 2)
                    cout << "Game Over. Player2 won!" << endl;
            }
        } else
            cout << "Game Over. Nobody won!" << endl;
        return;
    }

    // assigment operator for ConnectFourPlus
    ConnectFourPlus &ConnectFourPlus::operator=(const ConnectFourPlus &other) {
        ConnectFourAbstract::operator=(other);
        return *this;
    }
}
