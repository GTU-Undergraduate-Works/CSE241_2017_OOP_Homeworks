/*
 * File:   connectfour.h
 * Author: EFKAN DURAKLI - 161044086
 *
* Created on October 1, 2017, 11:00 PM
 * This file include function prototypies, constant values and enumareted types.
 */

#ifndef CONNECTFOUR_H__
#define	CONNECTFOUR_H__

#define MAXSIZE 20

// enumarted tpye for place of board
enum Place {
	empty, user1, user2
};

// intialize board array to '.'
void initializeBoardArray(char board[][MAXSIZE], int size); 

// print board array to screen
void printBoard(char board[][MAXSIZE], int size); 

// put 'X' or 'O' to given row and column on board array.
void updateBoardArray(char board[][MAXSIZE], int row, int column, Place location); 

// check the legality of move, if move is legal return true, if not legal return false
bool isMoveLegal(char board[][MAXSIZE], char move, int size); 

// find laegal row and column of given move
void findRowAndColumn(char board[][MAXSIZE], char move, int& row, int& column, int size); 

// takes move input from user1
void takeInputFromUSer1(char board[][MAXSIZE], char& move, int size); 

// takes move input from user2
void takeInputFromUSer2(char board[][MAXSIZE], char& move, int size); 

// takes move from user
void takeInputFromUSer(char board[][MAXSIZE], char& move, int size); 

// plays game with user1 and user2
void playWithTwoPlayers(char board[][MAXSIZE], int size); 

// check the connected four move, if there is winner return false, if not return false
bool checkWinner(char board[][MAXSIZE], int row, int column, int size, Place location);

// select best computer move and make a move for computer
void makeBestMove(char board[][MAXSIZE], int size, int &row, int &column);

// plays game with computer and user
void playWithOnepalyer(char board[][MAXSIZE], int size); 

#endif