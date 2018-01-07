
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.IOException;
import java.rmi.activation.ActivationInstantiator;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author efkan
 */
public class ConnectFourFrame extends JFrame {
    
    private JPanel panel;
    
    public ConnectFourFrame() {
        super("CONNECTFOUR - Developed by Efkan Duraklı");
        setLayout(new BorderLayout());
        //Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        //int height = screenSize.height;
        //int width = screenSize.width;
    
        //setSize(100, 100);
        
        
        setLocationRelativeTo(null);
        
        int size;
        String str1 = JOptionPane.showInputDialog("Enter size between 5 and 30");
        
        
        if (str1 == null)
            System.exit(1);
        
        size = Integer.parseInt(str1);
        while (size < 5 || size > 30) {
            JOptionPane.showMessageDialog(null,"You entered wrong size","Error",JOptionPane.ERROR_MESSAGE);
            str1 = JOptionPane.showInputDialog("Enter size again.\nSize must be between 5 and 30.");
            if (str1 == null)
                System.exit(1);
            size = Integer.parseInt(str1);
        }
        
        String str2 = JOptionPane.showInputDialog("Enter mode.\nEnter 1 for One Player.\nEneter 2 for Two Player.");
        
        if (str2 == null)
            System.exit(1);
        int a;
        a = Integer.parseInt(str2);
        while (a != 1 && a != 2) {
            JOptionPane.showMessageDialog(null,"You entered wrong mode.","Error",JOptionPane.ERROR_MESSAGE);
            str2 = JOptionPane.showInputDialog("Enter mode again.\nEnter 1 for One Player.\nEneter 2 for Two Player.");
            if (str2 == null) 
                System.exit(1);
            a = Integer.parseInt(str2);
        }
        
        if (a == 1)
            panel = new ConnectFourGUI(size, 'C');
        else
            panel = new ConnectFourGUI(size, 'P');
        add(panel, BorderLayout.CENTER);
        
        setSize(size*100+50, size*100);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(true);
        setVisible(true);
        
    }
}
