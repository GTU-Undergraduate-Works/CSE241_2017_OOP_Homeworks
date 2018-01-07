/*
 * File:   Cell.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on November 23, 2017, 11:00 A.M
 * This file is implemetation file of Cell class 
 */

#include "Cell.h"

Cell::Cell()
        :rowNumber(0), position('a'), content('.')
{ /* Intentionally empty */}

Cell::Cell(int rowValue, char positionValue, char contentValue)
        :rowNumber(rowValue), position(positionValue), content(contentValue)
{ /* Intentionally empty */}
