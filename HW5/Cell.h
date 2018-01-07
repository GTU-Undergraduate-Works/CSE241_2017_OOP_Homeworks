/*
 * File:   Cell.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on October 23, 2017, 11:00 A.M
 * This file is interface file of Cell class
 */

#ifndef HW5_CELL_H
#define HW5_CELL_H


class Cell {
public:
    // one parameter constructor
    Cell();

    // thre parameter constructor
    Cell(int rowValue, char positionValue, char contentValue);

    // getter functions;
    int getRowNumber() const { return rowNumber; }
    char getPosition() const { return position; }
    char getContent() const  { return content; }

    // Setter functions
    void setRowNumeber(int rowValue) {rowNumber = rowValue;}
    void setPosition(char positionValue) {position = positionValue;}
    void setContent(char contentValue) {content = contentValue;}

private:
    // private members
    int rowNumber;
    char position;
    char content;
};

#endif //HW5_CELL_H
