package contrôle;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import Elements.Ballon;
import Elements.Equipe;
import graph.Pan;
import graph.Screen;

public class Jcontrôle implements KeyListener {
    int pMax=1000, pMin=100, puissance=pMin;
    int nbplayers=4;
    public static int joueurSelectionne=0;
    public boolean down,up,right,left,Z,Q,S,D,SPACE;
    public static boolean arrow=false;
    Equipe equipe;
   
    
   public Jcontrôle(Equipe equipe){
	   if(equipe.controlerjoueur)
	   this.equipe=equipe;
   }
    
    public void keyTyped(KeyEvent e) {
       
    }
    
 
    public void keyPressed(KeyEvent e) {
    if (arrow(e)) arrow=true; else arrow=false;
    if(e.getKeyCode()==KeyEvent.VK_UP) up=true;
    if(e.getKeyCode()==KeyEvent.VK_DOWN) down=true; 
    if(e.getKeyCode()==KeyEvent.VK_RIGHT) right=true; 
    if(e.getKeyCode()==KeyEvent.VK_LEFT) left=true; 
    if(e.getKeyCode()==KeyEvent.VK_Z) Z=true; 
    if(e.getKeyCode()==KeyEvent.VK_Q) Q=true;
    if(e.getKeyCode()==KeyEvent.VK_S) S=true;
    if(e.getKeyCode()==KeyEvent.VK_D) D=true;
    if(e.getKeyCode()==KeyEvent.VK_SPACE) SPACE=true;
    if(e.getKeyCode()==KeyEvent.VK_SHIFT) equipe.joueurs.get(joueurSelectionne).setaccelerer(true);
    }
     
    public void keyReleased(KeyEvent e) {
    	    	if(e.getKeyCode()==KeyEvent.VK_UP) up=false; 
    	        if(e.getKeyCode()==KeyEvent.VK_DOWN) down=false;
    	        if(e.getKeyCode()==KeyEvent.VK_RIGHT) right=false;
    	        if(e.getKeyCode()==KeyEvent.VK_LEFT) left=false;
    	        if(e.getKeyCode()==KeyEvent.VK_Z) Z=false; 
    	        if(e.getKeyCode()==KeyEvent.VK_Q) Q=false;
    	        if(e.getKeyCode()==KeyEvent.VK_S) S=false;
    	        if(e.getKeyCode()==KeyEvent.VK_D) D=false;
    	        if(e.getKeyCode()==KeyEvent.VK_SHIFT) equipe.joueurs.get(joueurSelectionne).setaccelerer(false);
    	  
    if (e.getKeyCode()==KeyEvent.VK_SPACE){ 
    	if (equipe.possedeBallon()){	
    	if ((Z)||(Q)||(S)||(D)){
    		if (Z) equipe.joueurs.get(joueurSelectionne).passer(-Math.PI/2,puissance);
    		if (Q) equipe.joueurs.get(joueurSelectionne).passer(Math.PI,puissance);
    		if (S) equipe.joueurs.get(joueurSelectionne).passer(Math.PI/2,puissance);
    		if (D) equipe.joueurs.get(joueurSelectionne).passer(0,puissance);
    	}
		else equipe.joueurs.get(joueurSelectionne).passer(equipe.joueurs.get(joueurSelectionne).getDir(),puissance);
	    puissance=pMin;
    	}
    	else {
	    	equipe.joueurs.get(joueurSelectionne).arret();
			equipe.joueurs.get(joueurSelectionne).setaccelerer(false);
			joueurSelectionne=equipe.joueurBallon();
			equipe.modifjoueuracontrole(joueurSelectionne);
			
    	}
    	SPACE=false;
    }
    	
    
    }
    
    public void accelJoueur(){
    	if ((up)||(down)||(left)||(right)){
	    	if (up) equipe.joueurs.get(joueurSelectionne).courir(-Math.PI/2); 
	    	if (down) equipe.joueurs.get(joueurSelectionne).courir(Math.PI/2); 
	    	if (right) equipe.joueurs.get(joueurSelectionne).courir(0); 
	    	if (left) equipe.joueurs.get(joueurSelectionne).courir(Math.PI); 
	    	if ((up)&&(right)) equipe.joueurs.get(joueurSelectionne).courir(-Math.PI/4); 
	    	if ((up)&&(left)) equipe.joueurs.get(joueurSelectionne).courir(-3*Math.PI/4); 
	    	if ((down)&&(right)) equipe.joueurs.get(joueurSelectionne).courir(Math.PI/4); 
	    	if ((down)&&(left)) equipe.joueurs.get(joueurSelectionne).courir(3*Math.PI/4); 
    	}
    	else equipe.joueurs.get(joueurSelectionne).arret();
    }
   
    
    public  int getjoueur()
    {
    	return joueurSelectionne;
    }
    
    public boolean arrow(KeyEvent e){
    	return (e.getKeyCode()==KeyEvent.VK_LEFT)||(e.getKeyCode()==KeyEvent.VK_DOWN)
    		||(e.getKeyCode()==KeyEvent.VK_RIGHT)||(e.getKeyCode()==KeyEvent.VK_UP);
    }
    
    public void setJoueur(){
    	equipe.joueurs.get(joueurSelectionne).setSelect(false);
    	if (SPACE) {
    		if (puissance<=pMax) puissance+=10 ;
    	}
    	if (Ballon.passe) {
    		equipe.joueurs.get(joueurSelectionne).arret();
    		equipe.joueurs.get(joueurSelectionne).setaccelerer(false);
    		joueurSelectionne=equipe.joueurBallonP(joueurSelectionne);
    		Ballon.passe=false;
    	}
    	if (equipe.possedeBallon()) {
    		equipe.joueurs.get(joueurSelectionne).arret();
    		joueurSelectionne=equipe.joueurBallon();
    	}
    	equipe.joueurs.get(joueurSelectionne).setSelect(true);
    }
    
    public int getpuissance(){
    	return puissance;
    }
    
    }