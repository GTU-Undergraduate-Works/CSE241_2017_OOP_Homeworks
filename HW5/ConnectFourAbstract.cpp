/*
 * File:   ConnectFourAbstract.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on November 23, 2017, 11:00 A.M
 * This file is implemetation file abstract ConnectFourAbstract class 
 */

#include <iostream>
#include <fstream>
#include "ConnectFourAbstract.h"
using namespace std;

namespace DurakliEfkanConnectFour {

	// one parameter constructor
    // initialize game board to  5x5
    ConnectFourAbstract::ConnectFourAbstract()
            : height(5), width(5), order(1) {
        gameCells = new Cell *[height];
        for (int i = 0; i < height; i++)
            gameCells[i] = new Cell[width];

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                gameCells[i][j].setPosition(static_cast<char>('a' + j));
                gameCells[i][j].setRowNumeber(i);
            }
    }

    // two parameter constructor
    // initialize game board to heightValue x widthValue
    ConnectFourAbstract::ConnectFourAbstract(int heightValue, int widthValue)
            : height(heightValue), width(widthValue), order(1) {
        gameCells = new Cell *[height];
        for (int i = 0; i < height; i++)
            gameCells[i] = new Cell[width];

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                gameCells[i][j].setPosition(static_cast<char>('a' + j));
                gameCells[i][j].setRowNumeber(i);
            }
        }
    }
	
	// copy constructor
    ConnectFourAbstract::ConnectFourAbstract(ConnectFourAbstract &gameObject)
            : width(gameObject.width), height(gameObject.height),
              choice(gameObject.choice), order(gameObject.order) {
        gameCells = new Cell *[height];
        for (int i = 0; i < height; i++)
            gameCells[i] = new Cell[width];

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                gameCells[i][j] = gameObject.gameCells[i][j];
    }

    // destructor
    // deletes dynamic memory
    ConnectFourAbstract::~ConnectFourAbstract() {

        for (int i = 0; i < height; i++) {
            delete[] gameCells[i];
            gameCells[i] = NULL;
        }
        delete[] gameCells;
        gameCells = NULL;
    }

    // prints cuurent game board on screen
    void ConnectFourAbstract::printBoard() {

        char temp = 'a';
        cout << endl;
        for (int i = 0; i < width; i++)
            cout << temp++ << " ";
        cout << endl;
		for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                cout << gameCells[i][j].getContent() << " ";
            cout << endl;
        }
    }

    // finds status of given move in board.
    void ConnectFourAbstract::findMoveStatus(int &row, int &column, char move) const {
        int temp;
        temp = height;
        column = move - 'a';
        while (gameCells[temp - 1][column].getContent() != '.')
            temp--;
        row = temp - 1;
    }

    // checks legality of givem move
    // if move is legal return true, if not return false.
    bool ConnectFourAbstract::isMoveLegal(char move) const {

        int temp = move - 'a';
        if (temp > width - 1 || gameCells[0][temp].getContent() != '.')
            return false;
        return true;
    }

    // changes order
    void ConnectFourAbstract::changeOrder() {

        if (order == 1)
            order = 2;
        else if (order == 2)
            order = 1;
    }

    // resize and sets board according to given parameters
    bool ConnectFourAbstract::resizeAndSetBoard(int heightValue, int widthValue) {


        for (int i = 0; i < height; i++) {
            delete[] gameCells[i];
            gameCells[i] = NULL;
        }
        delete[] gameCells;
        gameCells = NULL;

        width = widthValue;
        height = heightValue;

        gameCells = new Cell *[height];
        for (int i = 0; i < height; i++)
            gameCells[i] = new Cell[width];

        for (int i = 0; i < height; i++) {

            for (int j = 0; j < width; j++) {
                gameCells[i][j].setPosition(static_cast<char>('a' + j));
                gameCells[i][j].setRowNumeber(i);
            }
        }
    }

    // checks fullnes of game board
    // if board is full return true, if not return false.
    bool ConnectFourAbstract::isBoardFull() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                if (gameCells[i][j].getContent() == '.')
                    return false;
        }
        return true;
    }

    // reads file information and set object according to file information
    bool ConnectFourAbstract::readFromFile(string fileName) {

        ifstream inputFile;
        char temp, tempChoice;
        int tempWidth, tempHeight, tempOrder, tempCount;

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
        inputFile.close();
        return true;
    }

    // write game information to file
    void ConnectFourAbstract::writeToFile(string fileName) {

        ofstream outputFile;
        outputFile.open(fileName);
        outputFile << width << " " << height << " " << order << " " << choice << " " << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                outputFile << gameCells[i][j].getContent() << " ";
            outputFile << endl;
        }
        outputFile.close();
    }

    // assigment operator for ConnectFourAbstract class
    ConnectFourAbstract &ConnectFourAbstract::operator=(const ConnectFourAbstract &other) {

        if (this == &other)
            return *this;
        resizeAndSetBoard(other.width, other.height);
        choice = other.choice;
        order = other.order;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                gameCells[i][j] = other.gameCells[i][j];
        return *this;
    }

    // if inputs come to end of file exits program
    void endOfInput() {
        cout << "\nEnd of input file.Program is closing..." << endl;
        exit(1);
    }
}