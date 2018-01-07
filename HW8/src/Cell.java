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
public class Cell {
    
    private int rowNumber;
    private int columnNumber;
    private char content;
    
    
    public Cell() {
        
        rowNumber = 0;
        columnNumber = 0;
        content = '.';
    }
    
    /**
     * creates Cell objects
     * 
     * @param row row number of Cell
     * @param column column number of Cell 
     * @param cont conetent of cell
     */
    public Cell(int row, int column, char cont) {
        
        rowNumber = row;
        columnNumber = column;
        content = cont;
    }
    /**
     * gets row number of Cell
     * @return row number of Cell
     */
    public int getRowNumber() {
        return rowNumber;
    }
    
    /**
     * gets column number of Cell
     * @return column number of Cell
     */
    public int getColumnNumber() {
        return columnNumber;
    }
    
    /**
     * gets content of Cell
     * @return content of Cell
     */
    public char getContent() {
        return content;
    }
    
    /**
     * sets row number of Cell to row
     * @param row row number of Cell
     */
    public void setRowNumber(int row) {
        rowNumber = row;
    }
    
    /**
     * sets column number of Cell to column
     * @param column column number of Cell
     */
    public void setColumnNumber(int column) {
        columnNumber = column;
    }
    
    /** 
     * sets content of Cell to content 
     * @param theContent content of Cell
     */
    public void setContent(char theContent) {
        content = theContent;
    }
}
