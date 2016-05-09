import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.*;
import javax.swing.*;
import MazeGenerator;
public class Navigator implements KeyListener{
   
	Player p;
	Maze m;
    public Navigator(Player p){
    	this.p = p;
    	JPanel thingy /* = something*/;
    	thingy.addKeyListener(this);
    }
    

     public void keyPressed(KeyEvent e) {
        int keyCode = e.getKeyCode();
        int curX = p.getXPos;
    	int curY = p.getYPos;
        switch( keyCode ) { 
            case KeyEvent.VK_UP:
                if(!m.HasWall(curY,curX,m.UP)) p.move(0,-1);
                break;
            case KeyEvent.VK_DOWN:
            	if(!m.HasWall(curY,curX,m.DOWN)) p.move(0,1);
                break;
            case KeyEvent.VK_LEFT:
            	if(!m.HasWall(curY,curX,m.LEFT)) p.move(-1,0);
                break;
            case KeyEvent.VK_RIGHT :
            	if(!m.HasWall(curY,curX,m.RIGHT)) p.move(1,0);
                break;
         }
        

    }
     
     /** Handle the key typed event from the text field. */
     public void keyTyped(KeyEvent e) {
     	
     }
     
    
    /** Handle the key released event from the text field. */
    public void keyReleased(KeyEvent e) {
    	
    }
   
}