/*
 * File:   ConnectFourPlus.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 23, 2017, 11:00 A.M
 * This file is interface file of ConnectFourPlus class
 */

#ifndef HW5_CONNECTFOURPLUS_H
#define HW5_CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"

namespace DurakliEfkanConnectFour {

    // this class is derived from ConnectFourAbstract class.
    class ConnectFourPlus : public ConnectFourAbstract {
    public:
        // no parameter constructor
        // initialize board array to 5x5
        ConnectFourPlus(); 

        // two parameter constructor
        // initialize board array to heightValue x widthValue
        ConnectFourPlus(int heigtValue, int widthValue); 

        // copy constructor
        ConnectFourPlus(ConnectFourPlus &gameObject); 

        // plays game on horizontal and vertical mode.
        void playGame();

        // assigment operator.
        ConnectFourPlus &operator=(const ConnectFourPlus &other);

        // checks winner of game.
        // if there is a winner, return true, if not return false.
        bool checkWinner(int row, int column);
    private:
        // takes input from users.
        void takeInput(string &instruction, string &fileName, char &move);

        // make a move for user according to given cellPosition
        bool play(char cellPosition);

        // make best move for computer.
        bool play();

        // finds best move for computer and make move
        void makeBestMove(int &row, int &column);

    };
}

#endif //HW5_CONNECTFOURPLUS_H
