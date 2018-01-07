
import java.util.Random;
import java.util.Scanner;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * ConnectFour Cell class
 * @author Efkan Duraklı
 * @since 05-01-2018
 * @version 1.0
 */
public class ConnectFour {
    
    Cell gameCells[][];
    private final int size;
    private int order;
    private final char mode;
    
    /**
     * No parameter constructor
     * creates ConnectFour object
     */
    public ConnectFour() {
        order = 1;
        size = 5;
        mode = 'C';
        gameCells = new Cell[size][size];
        for (int i = 0; i < size; i++)
            gameCells[i] = new Cell[size];
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
                gameCells[i][j] = new Cell(i, j, '.');
        }
    }
    
    /**
     * two parameter constructor
     * creates ConnectFour Object
     * @param theSize size of ConnectFour
     * @param theMode mode of ConnectFour game
     */
    public ConnectFour(int theSize, char theMode) {
        order = 1;
        size = theSize;
        mode = theMode;
        gameCells = new Cell[size][size];
        for (int i = 0; i < size; i++)
            gameCells[i] = new Cell[size];
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
                gameCells[i][j] = new Cell(i, j, '.');
        }
    }
    
    /**
     * copy constructor of ConnectFour class
     * @param other ConnectFour object
     */
    public ConnectFour(ConnectFour other) {
        size = other.size;
        mode = other.mode;
        order = 1;
        gameCells = new Cell[size][size];
        for (int i = 0; i < size; i++)
            gameCells[i] = new Cell[size];
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) 
                gameCells[i][j] = new Cell(i, j, other.gameCells[i][j].getContent());
        }
    }
    
    /**
     * sets order of ConnectFour game
     * @param n order
     */
    public void setOrder(int n) {
        order = n;
    } 
    
    /**
     * gets order of ConnectFour
     * @return order of ConnectFour
     */
    public int getOrder() {
        return order;
    }
    
    /**
     * gets game mode of ConnectFour game
     * @return 
     */
    public char getMode() {
        return mode;
    }
    
    /**
     * changes order of game
     */
    public void changeOrder() {
        if (order == 1)
            order = 2;
        else 
            order = 1;
    }
    
    /**
     * checks fulness of ConnectFour board
     * @return if board i full return true, if not return false
     */
    public boolean isBoardFull() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (gameCells[i][j].getContent() == '.')
                    return false;
            }
        }
        return true;
    }
    
    /**
     * finds suitable row for given column
     * @param column column number of Cell of ConnectFour
     * @return suitable row for given row
     */
    public int findRow(int column) {
        int temp = size-1;
        while(gameCells[temp][column].getContent() != '.')
            temp--;
        return temp;
    }
    
    /**
     * checks legality of given move
     * @param column column number of move
     * @return if move is legal return true, if not return false
     */
    public boolean isMoveLegal(int column) {
        if (column > size-1 || gameCells[0][column].getContent() != '.')
            return false;
        return true;
    }
    
    /**
     * make move for given column for player
     * @param column column number of move
     * @return if game finishes return true, if not return false
     */
    public boolean play(int column) {
        char temp;
        if (order == 1)
            temp = 'X';
        else 
            temp = 'O';
        int row = findRow(column);
        gameCells[row][column].setContent(temp);
        return checkWinner(row, column);
    }
    
    /**
     * checks winner of game
     * @param row row number of last move
     * @param column column number of last move
     * @return if thre is winner return true, if not return false
     */
    @SuppressWarnings("empty-statement")
    public boolean checkWinner(int row, int column) {
        int vertical = 0, horizontal = 0, diagonal1 = 0, diagonal2 = 0, i = 0, j = 0, k = 0, l = 0;
        int[] array1 = new int[7];
        int[] array2 = new int[7];
        char temp, temp2;
        if (order == 1)
            temp = 'X';
        else 
            temp = 'O';
        
        
        temp2 = Character.toLowerCase(temp);
        // check vertical
	for (i = row; i < size && gameCells[i][column].getContent() == temp; i++, vertical++) array1[k++] = i;
        if (vertical >= 4) {
            for (i = 0; i < 4; i++)
                gameCells[array1[i]][column].setContent(temp2);
            return true;
        }
        // check horizontal
        for (i = 0; i < size; i++) {
            j = i;
            horizontal = 0; 
            k = 0;
            while (j < size && gameCells[row][j].getContent() == temp) {
                    
                    array2[k++] = j;
                    horizontal++;
                    j++;
            }
            if (horizontal >= 4) {
                for (i = 0; i < 4; i++)
                    gameCells[row][array2[i]].setContent(temp2);
                return true;
            }
        }
        
        // check diagonal1
        k = 0;
        l = 0;
        for (i = row, j = column; i >= 0 && j < size && gameCells[i][j].getContent() == temp; i--, j++, diagonal1++) {
            array1[k++] = i;
            array2[l++] = j;
        }
        for (i = row, j = column; j >= 0 && i < size && gameCells[i][j].getContent() == temp; i++, j--, diagonal1++) {
            array1[k++] = i+1;
            array2[l++] = j-1;
        }
        if (diagonal1 > 4) {
            for (i = 0; i < 4; i++)
                gameCells[array1[i]][array2[i]].setContent(temp2);
            return true;
        }
        
        // check diagonal2
        k = 0;
        l = 0;
        for (i = row, j = column; i >= 0 && j >= 0 && gameCells[i][j].getContent() == temp; i--, j--, diagonal2++) {
            array1[k++] = i;
            array2[l++] = j;
        }
        for (i = row, j = column; i < size && j < size && gameCells[i][j].getContent() == temp; i++, j++, diagonal2++) {
            array1[k++] = i+1;
            array2[l++] = j+1;
        }
        if (diagonal2 > 4) {
            for (i = 0; i < 4; i++) 
                gameCells[array1[i]][array2[i]].setContent(temp2);
            return true;
        }
        
        return false;
    }
    
    /**
     * resets ConnectFour board
     */
    public void reset() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) 
                gameCells[i][j].setContent('.');
        }
    }
    
    /**
     * make best move for computer
     * @return if game finishes return true, if not return false
     */
    public boolean play() {
         
        int i,j,row;
        boolean flag = false;
        
        ConnectFour copyGame = new ConnectFour(this);
        copyGame.setOrder(2);
        for (i = 0; i < size; i++) {
            if (isMoveLegal(i)) {
                row = findRow(i);
                if (copyGame.play(i)) {
                    if (play(i))
                        return true;
                    flag = true;
                    break;
                }
                copyGame.gameCells[row][i].setContent('.');
            }
        }
        if (!flag) {
            copyGame.setOrder(1);
            for (i = 0; i < size; i++) {
                if (isMoveLegal(i)) {
                    row = findRow(i);
                    if (copyGame.play(i)) {
                        if (play(i))
                            return true;
                        flag = true;
                        break;
                    }
                    copyGame.gameCells[row][i].setContent('.');
                }
            }
        }
        if (!flag) {
            int column;
            Random rand = new Random();
            column = rand.nextInt(size);
            for (i = column; i < size && !flag; i++) {
                if (isMoveLegal(i)) {
                    flag = true;
                    if (play(i))
                        return true;
                    }
            }
            for (i = 0; i < column && !flag; i++) {
                if (isMoveLegal(i)) {
                    flag = true;
                    if (play(i))
                        return true;
                }
            }
        }
        return false;
    }
}
