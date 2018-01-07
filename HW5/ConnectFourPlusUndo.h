/*
 * File:   ConnectFourPlusundo.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 23, 2017, 11:00 A.M
 * This file is interface file of ConnectFourPlusundo class
 */

#ifndef HW5_CONNECTFOURPLUSUNDO_H
#define HW5_CONNECTFOURPLUSUNDO_H

#include <vector>
#include "ConnectFourPlus.h"

namespace DurakliEfkanConnectFour {

    // struct for moves of users and computer.
    struct Undo_t {
        int row;
        int column;
    };
    // this class is derived from ConnectFourPlus class.
    class ConnectFourPlusUndo : public ConnectFourPlus {

    public:
        // no parameter constructor
        // initialize board array to 5x5
        ConnectFourPlusUndo();

        // two parameter constructor
        // initialize board array to heightValue x widthValue
        ConnectFourPlusUndo(int heightValue, int widthValue);

        // copy constructor
        ConnectFourPlusUndo(ConnectFourPlusUndo &gameObject);

        // plays game on horizontal and vertical mode.
        // game has undo feature
        void playGame();

        // assigment operator
        ConnectFourPlusUndo &operator=(const ConnectFourPlusUndo &other);
    private:
        // Undo_t vector to save moves of game
        vector<Undo_t> moves;
        // make a move for user according to given cellPosition
        bool play(char cellPosition);

        // make best move for computer.
        bool play();

        // finds best move for computer and make move
        void makeBestMove(int &row, int &column);

        // redefinition of function
        bool readFromFile(string fileName);

        // redefinition of function.
        void writeToFile(string fileName);

        // takes input from users.
        void takeInput(string &instruction, string &fileName, char &move);

        // take back the move made.
        bool undo();
    };
}

#endif //HW5_CONNECTFOURPLUSUNDO_H
