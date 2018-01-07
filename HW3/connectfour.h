/*
 * File:   connectfour.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 18, 2017, 11:00 PM
 * This file includes all class definition
 */

#ifndef CONNECTFOUR_H__
#define	CONNECTFOUR_H__

using namespace std;
#include <vector>

class ConnectFour
{
public:
	// constructors
	ConnectFour();
	ConnectFour(int widthValue, int heightValue);
	ConnectFour(int widthValue, int heightValue, char choiceValue);
	// getter functions
	inline int getWidth() const  { return width; }
	inline int getHeight() const { return height; }

	// setter functions
	inline void setChoice(char newChoice) { choice = newChoice; }
	void setWidthAndHeight(int newWidth, int newHeight);
	void resizeAndSetBoard(int widthValue, int heightValue);

	// helper functions
	void findMoveStatus(int & row, int & column, char move) const;
	void takeInput(string & instruction, string & fileName, char & move);
	void makeBestMove(int & row, int & column);
	bool isMoveLegal(char & move) const;
	bool isBoardFull() const;
	bool checkWinner(int row, int column);
	void printBoard() const;
	bool compareGames(ConnectFour & other);
	bool readFromFile(string fileName);
	void writeToFile(string fileName) const;
	
	// plays game for multimode
	bool play();

	// plays game for single mode
	void playGame();

private:
	class Cell
	{
	public:
		Cell();
		//getter functions
		inline char getContent() const { return content; }
		inline char getPosition() const { return position; }
		inline int getRowNumber() const { return rowNumber; }
		// static getter functions
		static int getCount() { return count; }
		// getter functions
		void setPosition(char newPosition, int newRowNumber);
		inline void setContent(char newContent) { content = newContent; }
		// satatic getter functions
		static void setCount() { count++; }
		static void setCount(int newCount) { count += (newCount - count); }
		
		
	private:
		char position;
		int rowNumber;
		char content;
		static int count;
	};
	int width;
	int height;
	int order;
	char choice;
	vector< vector<Cell> > gameCells;
	// private getter functions
	int getOrder() const { return order; }
	void setOrder(int newOrder) { order = newOrder; }
	char getChoice() const { return choice; }
	// private helper functions.
	void changeOrder();

};

#endif
