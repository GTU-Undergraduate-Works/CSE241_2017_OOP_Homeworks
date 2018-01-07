
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import static sun.audio.AudioPlayer.player;

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
 * {@inheritDoc}
 */
public class ConnectFourGUI extends JPanel {
    
    private final String redBall;
    private final String blueBall;
    private final String yellowBall;
    private final int size;
    JButton cell[];
    JPanel boardPanel;
    JLabel player1;
    JLabel player2;
    ConnectFour board;
    
    /**
     * 
     * @param theSize size of ConnectFour
     * @param mode mode of ConnectFour game
     */
    ConnectFourGUI(int theSize, char mode) {
        
        super(new BorderLayout());
        setPreferredSize(new Dimension(800,700));
        setLocation(0, 0);
        size = theSize;
        if (size >= 5 && size < 23) {
            redBall = "images/red2.png";
            blueBall = "images/blue2.png";
            yellowBall = "images/yellow2.png";
        }
        else {
            redBall = "images/red1.png";
            blueBall = "images/blue1.png";
            yellowBall = "images/yellow1.png";
        }
        board = new ConnectFour(size, mode);
        boardPanel = new JPanel(new GridLayout(size,size));
        cell = new JButton[size*size];
        int k = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cell[k] = new JButton();
                cell[k].setSize(50, 50);
                cell[k].setBackground(Color.CYAN);
                cell[k].setBorder(BorderFactory.createLineBorder(Color.BLACK));
                if (board.gameCells[i][j].getContent() == 'X') {
                    try 
                    {
                        Image img = ImageIO.read(getClass().getResource(blueBall));
                        cell[k].setIcon(new ImageIcon(img));
                    } catch (IOException ex) {}
                }
                else if (board.gameCells[i][j].getContent() == 'O') {
                    try 
                    {
                        Image img = ImageIO.read(getClass().getResource(redBall));
                        cell[k].setIcon(new ImageIcon(img));
                    } catch (IOException ex) {}
                }
                cell[k].addActionListener(new Action());
                boardPanel.add(cell[k]);
                k++;
            }
            
        }
        add(boardPanel, BorderLayout.CENTER);
        
        JPanel informationPanel = new JPanel(new GridBagLayout());
        GridBagConstraints a = new GridBagConstraints();
        informationPanel.setPreferredSize(new Dimension(180,200));
        
        JLabel red = new JLabel();
        JLabel blue = new JLabel();
        try 
        {
            Image img = ImageIO.read(getClass().getResource(redBall));
            red.setIcon(new ImageIcon(img));
        } catch (IOException ex) {}
        try 
        {
            Image img = ImageIO.read(getClass().getResource(blueBall));
            blue.setIcon(new ImageIcon(img));
        } catch (IOException ex) {}
        
        player1 = new JLabel();
        player2 = new JLabel(); 
        if (board.getMode() == 'C' || board.getMode() == 'c') {
            player1.setText(" Player ");
            player2.setText(" Computer ");
        }
        else if (board.getMode() == 'P' || board.getMode() == 'p') {
            player1.setText(" Player1 ");
            player2.setText(" Player2 ");
        }
        
        player1.setFont(new Font("Serif", Font.BOLD, 22));
        player2.setFont(new Font("Serif", Font.BOLD, 22));          
        a.gridx = 0;
        a.gridy = 1;
        informationPanel.add(blue, a);  
        a.gridx = 1;
        a.gridy = 1;
        informationPanel.add(player1,a);
        
        
        a.gridx = 0;
        a.gridy = 2;
        informationPanel.add(red, a);  
        a.gridx = 1;
        a.gridy = 2;
        informationPanel.add(player2,a);
              
        add(informationPanel, BorderLayout.EAST);
                    
    }
    /**
     * private inner class that handles user events
     */
    private class Action implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            
            int k = 0;
            boolean flag = true;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    
                    if (e.getSource() == cell[k]) {
                        
                        if (board.getMode() == 'C' || board.getMode() == 'c') {
                            
                            flag = true;
                            if (board.isMoveLegal(k%size)) {
                                if (board.play(k%size)) {
                                    loadBall();
                                    JOptionPane.showMessageDialog(null,"Player Win!","Game Over",JOptionPane.PLAIN_MESSAGE);
                                    board.reset();
                                    flag = false;
                                    loadBall();
                                }
                                if (board.isBoardFull()) {
                                    loadBall();
                                    JOptionPane.showMessageDialog(null,"Nobody Win!","Game Over",JOptionPane.PLAIN_MESSAGE);
                                    flag = false;
                                    board.reset();
                                    loadBall();
                                }
                                loadBall();
                                board.changeOrder();
                                if (flag) {
                                    if (board.play()) {
                                        loadBall();
                                        JOptionPane.showMessageDialog(null,"Computer Win!","Game Over",JOptionPane.PLAIN_MESSAGE);
                                        board.reset();
                                        loadBall();
                                    }
                                }
                                if (board.isBoardFull()) {
                                    loadBall();
                                    JOptionPane.showMessageDialog(null,"Nobody Win!","Game Over",JOptionPane.PLAIN_MESSAGE);
                                    //board.changeOrder();
                                    board.reset();
                                    loadBall();
                                    
                                    
                                }
                                loadBall();
                                board.changeOrder();
                            }
                        }
                        else if (board.getMode() == 'P' || board.getMode() == 'p') {
                            
                            if (board.isMoveLegal(k%size)) {
                                if (board.play(k%size)) {
                                    loadBall();
                                    if (board.getOrder() == 1) {
                                        JOptionPane.showMessageDialog(null,"Player1 Win!","Game Over",JOptionPane.PLAIN_MESSAGE);
                                        board.reset();
                                        loadBall();
                                        board.changeOrder();
                                    }
                                    else {
                                        JOptionPane.showMessageDialog(null,"Player2 Win!","Game Over",JOptionPane.PLAIN_MESSAGE);
                                        board.reset();
                                        loadBall();
                                    }
                                }
                                if (board.isBoardFull()) {
                                    loadBall();
                                    JOptionPane.showMessageDialog(null,"Nobody Win!","Game Over",JOptionPane.PLAIN_MESSAGE);
                                    board.reset();
                                    loadBall();
                                    if (size % 2 == 1)
                                        board.changeOrder();
                                }
                                loadBall();
                                board.changeOrder();
                            }
                        }
                    }
                    k++;
                }
            }
        }
    }
    /**
     * loads Ball to panel
     */   
    private void loadBall() {
        
        int k = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board.gameCells[i][j].getContent() == 'X') {
                    try 
                    {
                        Image img = ImageIO.read(getClass().getResource(blueBall));
                        cell[k].setIcon(new ImageIcon(img));
                    } catch (IOException ex) {}

                }
                else if (board.gameCells[i][j].getContent() == 'O') {
                    try 
                    {
                        Image img = ImageIO.read(getClass().getResource(redBall));
                        cell[k].setIcon(new ImageIcon(img));
                    } catch (IOException ex) {}

                }
                
                else if (board.gameCells[i][j].getContent() == 'x' || board.gameCells[i][j].getContent() == 'o') {
                    try 
                    {
                        Image img = ImageIO.read(getClass().getResource(yellowBall));
                        cell[k].setIcon(new ImageIcon(img));
                    } catch (IOException ex) {}
                }
                
                else if (board.gameCells[i][j].getContent() == '.') 
                    cell[k].setIcon(null);
                k++;
            }
        }
    }
}
