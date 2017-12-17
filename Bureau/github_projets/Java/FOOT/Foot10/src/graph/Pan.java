package graph;
import java.awt.Graphics;
import javax.swing.JPanel;

import Elements.*;
import graph.elements.GraphTerrain;

import java.awt.*;



public class Pan extends JPanel { 
	
	
	Equipe equipe1;
	Equipe equipe2;
	Ballon ballon;
	int equipeacontrolée;
	int joueuracontrolée;
	int puissancej;
	GraphTerrain graphterrain = new GraphTerrain();
	
	public Pan(Equipe equipe1, Equipe equipe2, Ballon ballon ,int equipeacontrolée, int j)
	{
		
		this.equipe1=equipe1;
		this.equipe2=equipe2;
		this.ballon=ballon;
		this.equipeacontrolée=equipeacontrolée=1;
		
	}
	public void updatejoueurcontrolée(int joueur)
	{
		this.joueuracontrolée=joueur;
	}
	
	public void updatepuissancej(int puissance){
		puissancej=puissance;
	}
	

	public void paintComponent(Graphics g){
	  
	  int u= 8; //taille des joueurs
	  
    //Vous verrez cette phrase chaque fois que la méthode sera invoquée
    Graphics2D g2d = (Graphics2D)g;    
    
    GradientPaint gp = new GradientPaint(0, 0, new Color(46,191,94), 25,0, new Color(9,168,59), true);                
    GradientPaint gp2 = new GradientPaint(0, 0, new Color(/*0*/255,255,255), 0,0, new Color(0,0,0), true);
 
    this.graphterrain.paint(g,0,0,200);
    
   equipe1.getgraphcursor().paint(g,0,0,10);
   equipe1.getgraph().paint(g, 0,0,10);
   equipe2.getgraph().paint(g,0,0,10);
   ballon.graphballon.paint(g2d, ballon.getx(),ballon.gety(),10);

	  
	  if (puissancej!=0){
		  g2d.setPaint(new GradientPaint(0,0,new Color(255,255,255), puissancej/10,0,new Color(0,0,0), true));
		  g2d.fillRect(170+360-5,50+5, puissancej/10,5);
	  }
  }         
  
  
  
  public void refreshplayerposition(Equipe equipe1, Equipe equipe2, Ballon ballon)
  {
		this.equipe1=equipe1;
		this.equipe2=equipe2;
		this.ballon=ballon;
  }
  
}