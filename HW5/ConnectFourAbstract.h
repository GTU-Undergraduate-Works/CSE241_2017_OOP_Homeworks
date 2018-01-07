/*
 * File:   ConnectFourAbstract.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 23, 2017, 11:00 A.M
 * This file is interface file of abstarct ConnectFourAbstract class
 */

#ifndef HW5_CONNECTFOURABSTRACT_H
#define HW5_CONNECTFOURABSTRACT_H

#include <iostream>
#include "Cell.h"
using namespace std;

namespace DurakliEfkanConnectFour {

    class ConnectFourAbstract {
    public:
        ConnectFourAbstract();
        ConnectFourAbstract(int heightValue, int widthVlaue);
        ConnectFourAbstract(ConnectFourAbstract &gameObject); // copy construtor
        ~ConnectFourAbstract();

        // GETTERS
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        int getOrder() const { return order; }
        int getChoice() const { return choice; }

        // SETTERS
        void setWidth(int newWidth) { width = newWidth; }
        void setHeight(int newHeight) { height = newHeight; }
        void setOrder(int newOrder) { order = newOrder; }
        void setChoice(int newChoice) { choice = newChoice; }

        // VIRTUAL FUNCTIONS
        virtual bool checkWinner(int row, int column) = 0;
        virtual void makeBestMove(int &row, int &column) = 0;
        virtual bool play() = 0;
        virtual bool play(char cellPosition) = 0;
        virtual void playGame() = 0;
        virtual void takeInput(string &instruction, string &fileName, char &move) = 0;

        // PURE VIRTUAL FUNCTIONS
        virtual bool readFromFile(string fileName);
        virtual void writeToFile(string fileName);
        
        // assigment operator
        ConnectFourAbstract &operator=(const ConnectFourAbstract &other);

    protected:
        Cell **gameCells;
        int height;
        int width;
        int order;
        char choice;
        // PRIVATE HELPER FUNCTIONS
        void printBoard();
        void findMoveStatus(int &row, int &column, char move) const;
        bool resizeAndSetBoard(int heightValue, int widthValue);
        bool isMoveLegal(char move) const;
        void changeOrder();
        bool isBoardFull();

    };

    // global fuction that exit from program, when input goes to end of file.
    void endOfInput();
}

#endif //HW5_CONNECTFOURABSTRACT_H
