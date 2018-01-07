/*
 * File:   connectfour.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 7, 2017, 11:00 A.M
 * This file includes all class definition and function definitions
 */

#ifndef CONNECTFOUR_H__
#define	CONNECTFOUR_H__

using namespace std;

class ConnectFour
{
public:

	// CONSTRUCTORS
	// creates 5 x 5 game board.
	ConnectFour();

	// creates widthValue x heightValue board.
	ConnectFour(int widthValue, int heightValue);

	// creates game board according to file information
	ConnectFour(const string & fileName);
	
	ConnectFour(const ConnectFour &); // copy constructor

	// destructor
	~ConnectFour(); 

	// GETTERS
	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

	// SETTERS
	void setChoice(char newChoice) { choice = newChoice; }

	// HELPER FUNCTIONS

	// play game for singular mode
	void playGame();

	// play game for one step
	bool playOneStep();

	// reads file and set board according to file information
	bool readFileAndSetBoard(string fileName);

	// resize and set board according to given parameters
	void resizeAndSetBoard(int widthValue, int heightValue);
	void printBoard() const;


	// OPERATOR OVERLOADINGS
	bool operator == (const ConnectFour & other) const;
	ConnectFour & operator = (const ConnectFour & other); // assigment operator
	bool operator != (const ConnectFour & other) const;

private:
	class Cell
	{
	public:
		// initialize position to 'A', rowNumber to 0 and content to '.'
		Cell(); // no parameter constructor

		// GETTERS
		char getContent() const { return content; }
		char getPosition() const { return position; }
		int getRowNumber() const { return rowNumber; }

		// SETTERS
		void setPosition(char newPosition, int newRowNumber);
		void setContent(char newContent) { content = newContent;} 

		// static functions to count living cells
		static void setCount() { count++; }
		static void setCount(int newCount) { count += (newCount - count); }
		static int getCount() { return count; }

		// OERATOR OVERLOADINGS
		bool operator == (const Cell & other) const;
		bool operator != (const Cell & other) const;
		ConnectFour::Cell operator ++ ();
		ConnectFour::Cell operator ++ (int ignore);
		ConnectFour::Cell operator -- ();
		ConnectFour::Cell operator -- (int ignore);

		// FRIEND FUNCTIONS
		friend istream & operator >> (istream & inputStream, Cell & cellObject);
		friend ostream & operator << (ostream & outStream, Cell & cellObject);
	private:
		char position;
		int rowNumber;
		char content;
		static int count;
	};
	// FRIEND FUNCTIONS
	friend istream & operator >> (istream & inputStream, ConnectFour::Cell & cellObject);
	friend ostream & operator << (ostream & outStream, const ConnectFour::Cell & cellObject);
	// private members
	int width;
	int height;
	char choice;
	int order;
	Cell **gameCells;

	// private helper functions
	void setOrder(int newOrder) { order = newOrder; }
	void changeOrder();
	bool isBoardFull() const;
	void makeBestMove(int & row, int & column);
	bool readFromFile(string fileName);
	void writeToFile(string fileName) const;
	void takeInput(string & instruction, string & fileName, char & move);
	bool checkWinner(int row, int column);
	bool isMoveLegal(char move) const;
	void findMoveStatus(int & row, int & column, char move) const;
	bool play();
	bool play(char cellPosition);
};

// global function to exit program
void endOfInput();

#endif // CONNECTFOUR_H__


