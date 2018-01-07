/*
 * File:   ConnectFourPlusUndo.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on November 23, 2017, 11:00 A.M
 * This file is implemetation file of ConnectFourPlusUndo class 
 */

#include <fstream>
#include "ConnectFourPlusUndo.h"

namespace  DurakliEfkanConnectFour {

    // one parameter constructor
    // initialize game board to  5x5
    ConnectFourPlusUndo::ConnectFourPlusUndo()
            : ConnectFourPlus() { /* intentionally empty */}

    // two parameter constructor
    // initialize game board to heightValue x widthValue
    ConnectFourPlusUndo::ConnectFourPlusUndo(int heightValue, int widthValue)
            : ConnectFourPlus(heightValue, widthValue) { /* intentioanally empty */}

    // copy constructor
    ConnectFourPlusUndo::ConnectFourPlusUndo(ConnectFourPlusUndo &gameObject)
            : ConnectFourPlus(gameObject) { /* inetentionally empty */}

    // find best move for computer and make these move
    void ConnectFourPlusUndo::makeBestMove(int &row, int &column) {

        ConnectFourPlusUndo tempObje(*this);
        int i, temp;
        bool flag = false;
        char ch;
        Undo_t tempMoves;

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
                    tempMoves.row = row;
                    tempMoves.column = column;
                    moves.push_back(tempMoves);
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
                        tempMoves.row = row;
                        tempMoves.column = column;
                        moves.push_back(tempMoves);
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
                tempMoves.row = row;
                tempMoves.column = column;
                moves.push_back(tempMoves);
            }
        }
    }

    // make move for computer
    bool ConnectFourPlusUndo::play() {
        int row, column;
        makeBestMove(row, column);
        if (checkWinner(row, column))
            return true;
        return false;
    }

    // make move for users according to given cellPosition parameter
    bool ConnectFourPlusUndo::play(char cellPosition) {
        int row, column;
        Undo_t tempMoves;
        findMoveStatus(row, column, cellPosition);
        tempMoves.row = row;
        tempMoves.column = column;
        moves.push_back(tempMoves);
        if (order == 1)
            gameCells[row][column].setContent('X');
        else if (order == 2)
            gameCells[row][column].setContent('O');
        if (checkWinner(row, column))
            return true;
        return false;
    }

    // reads file information and set object according to file information
    bool ConnectFourPlusUndo::readFromFile(string fileName) {
        ifstream inputFile;
        char temp, tempChoice;
        int tempWidth, tempHeight, tempOrder, tempCount;
        Undo_t tempMoves;

        inputFile.open(fileName);
        if (inputFile.fail())
            return false;
        inputFile >> tempWidth >> tempHeight >> tempOrder >> tempChoice;
        resizeAndSetBoard(tempHeight, tempWidth);
        order = tempOrder;
        choice = tempChoice;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                inputFile >> temp;
                gameCells[i][j].setContent(temp);
            }
        }
        moves.clear();
        while (!inputFile.eof()) {
            inputFile >> tempMoves.row >> tempMoves.column;
            moves.push_back(tempMoves);
        }
        inputFile.close();
        return true;

    }

    // write file information to file
    void ConnectFourPlusUndo::writeToFile(string fileName) {

        ofstream outputFile;
        outputFile.open(fileName);
        outputFile << width << " " << height << " " << order << " " << choice << " " << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                outputFile << gameCells[i][j].getContent() << " ";
            outputFile << endl;
        }
        for (int i = 0; i < moves.size(); i++)
            outputFile << moves[i].row << " " << moves[i].column << endl;
        outputFile.close();
    }

    //  takes input from user
    void ConnectFourPlusUndo::takeInput(string &instruction, string &fileName, char &move) {

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
            } else if (instruction == "UNDO" || instruction == "undo")
                flag = false;
            else {
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
    }

    // takes back the move made
    bool ConnectFourPlusUndo::undo() {

        bool flag = false;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (gameCells[i][j].getContent() == 'X' || gameCells[i][j].getContent() == 'O')
                    flag = true;
            }
        }
        if (flag) {
            int row, column;
            row = moves[moves.size() - 1].row;
            column = moves[moves.size() - 1].column;
            gameCells[row][column].setContent('.');
            moves.pop_back();
        }
        return flag;
    }

    // plays game until game finished
    void ConnectFourPlusUndo::playGame() {

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
            } else if (instruction == "UNDO" || instruction == "undo") {

                if (undo()) {
                    printBoard();

                    if (choice == 'c' || choice == 'C') {
                        play();
                        changeOrder();
                        printBoard();
                    }
                    changeOrder();
                } else
                    cerr << "You can not Undo!\n" << endl;
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

    // assigment operator for ConnectFourPlusUndo class
    ConnectFourPlusUndo &ConnectFourPlusUndo::operator=(const ConnectFourPlusUndo &other) {
        Undo_t tempMoves;
        ConnectFourPlus::operator=(other);
        moves.clear();
        for (int i = 0; i < moves.size(); i++) {
            tempMoves.row = other.moves[i].row;
            tempMoves.column = other.moves[i].column;
            moves.push_back(tempMoves);
        }
        return *this;
    }
}

