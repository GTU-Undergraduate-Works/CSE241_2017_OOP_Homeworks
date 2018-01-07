/*
 * File:   ConnectFourDiag.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 23, 2017, 11:00 A.M
 * This file is interface file of ConnectFourDiag class
 */

#ifndef HW5_CONNECTFOURDIAG_H
#define HW5_CONNECTFOURDIAG_H
#include "ConnectFourAbstract.h"

namespace DurakliEfkanConnectFour {

    // this class is derived from ConnectFourAbstract class.
    class ConnectFourDiag : public ConnectFourAbstract {

    public:
        // no parameter constructor
        // initialize board array to 5x5
        ConnectFourDiag();

        // two parameter constructor
        // initialize board array to heightValue x widthValue
        ConnectFourDiag(int heightValue, int widthValue);

        // copy constructor
        ConnectFourDiag(ConnectFourDiag &gameObject);

        // plays game only diagonal mode.
        void playGame();

        // assigment operator
        ConnectFourDiag &operator=(const ConnectFourDiag &other);
    private:
        // takes input from users.
        void takeInput(string &instruction, string &fileName, char &move);

        // make a move for user according to given cellPosition
        bool play(char cellPosition);

        // make best move for computer.
        bool play();

        // finds best move for computer and make move
        void makeBestMove(int &row, int &column);

        // checks winner of game.
        // if there is a winner, return true, if not return false.
        bool checkWinner(int row, int column);
    };
}

#endif //HW5_CONNECTFOURDIAG_H
