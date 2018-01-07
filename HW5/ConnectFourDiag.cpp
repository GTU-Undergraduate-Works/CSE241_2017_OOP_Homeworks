/*
 * File:   ConnectFourDiag.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on November 23, 2017, 11:00 A.M
 * This file is implemetation file of ConnectFourDiag class 
 */

#include <iostream>
#include "ConnectFourDiag.h"

namespace DurakliEfkanConnectFour {

    // one parameter constructor
    // initialize game board to  5x5
    ConnectFourDiag::ConnectFourDiag()
            : ConnectFourAbstract() { /* intentionally emty */}

    // two parameter constructor
    // initialize game board to heightValue x widthValue
    ConnectFourDiag::ConnectFourDiag(int heightValue, int widthValue)
            : ConnectFourAbstract(heightValue, widthValue) { /* inetentianally empty */}

    // copy constructor
    ConnectFourDiag::ConnectFourDiag(ConnectFourDiag &gameObject)
            : ConnectFourAbstract(gameObject) {}

    // checks winners of game diagonally
    // if there is winner return true, if not return false
    bool ConnectFourDiag::checkWinner(int row, int column) {

        int array1[7], array2[7];
        char temp, stat;
        int diagonal1 = 0, diagonal2 = 0, i = 0, j = 0, k = 0, l = 0;

        if (order == 1)
            stat = 'X';
        else if (order == 2)
            stat = 'O';

        temp = tolower(stat);

        // check diagonal1
        k = 0;
        l = 0;
        for (i = row, j = column; i >= 0 && j < width && gameCells[i][j].getContent() == stat; i--, j++, diagonal1++) {
            array1[k++] = i;
            array2[l++] = j;
        }
        for (i = row, j = column; j >= 0 && i < height && gameCells[i][j].getContent() == stat; i++, j--, diagonal1++) {
            array1[k++] = i + 1;
            array2[l++] = j - 1;
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

        for (i = row, j = column;
             i < height && j < width && gameCells[i][j].getContent() == stat; i++, j++, diagonal2++) {
            array1[k++] = i + 1;
            array2[l++] = j + 1;
        }

        if (diagonal2 > 4) {
            for (i = 0; i < 4; i++)
                gameCells[array1[i]][array2[i]].setContent(temp);
            return true;
        }
        return false;
    }

    // plays game for computer
    bool ConnectFourDiag::play() {
        int row, column;
        makeBestMove(row, column);
        if (checkWinner(row, column))
            return true;
        return false;
    }

    // plays game for users accorsing to given parameter cellPosition
    bool ConnectFourDiag::play(char cellPosition) {
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

    // takes input from user
    void ConnectFourDiag::takeInput(string &instruction, string &fileName, char &move) {
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
    void ConnectFourDiag::playGame() {
        char move, temp;
        int row, column;
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
                    order = 1;
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
                    findMoveStatus(row, column, move);
                    if (order == 1) {
                        gameCells[row][column].setContent('X');
                    } else if (order == 2)
                        gameCells[row][column].setContent('O');


                    if (checkWinner(row, column)) {
                        winner = true;
                        break;
                    }
                    changeOrder();
                    printBoard();
                }
            }
        }
        // prints information who wins game
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

    // find best move for computer and make these move
    void ConnectFourDiag::makeBestMove(int &row, int &column) {

        ConnectFourDiag tempObje(*this);
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
    // assigment operator for ConnectFourDiag class
    ConnectFourDiag &ConnectFourDiag::operator=(const ConnectFourDiag &other) {
        ConnectFourAbstract::operator=(other);
        return *this;
    }
}