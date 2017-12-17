package graph.elements;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

import Elements.Equipe;

public class Graphcursor implements Graphelements {

	int joueurac;
	Equipe equipe; 
	
	public Graphcursor(Equipe equipe)
	{
		
		this.equipe=equipe;
		joueurac = equipe.getjoueuracontroler();
		
	}
	@Override
	public void paint(Graphics g, double ordonnee, double abscisse, int echelle) {
		// TODO Auto-generated method stub
     this.paint(g,ordonnee,abscisse,8, echelle);
	}

	@Override
	public void paint(Graphics g, double ordonnee, double abscisse, int size, int echelle) {
		// TODO Auto-generated method stub

		Graphics2D g2d = (Graphics2D) g;
		 g2d.setPaint(new Color(0,0,0));
   	  
         Integer I =(int) (Math.floor(echelle*(equipe.joueurs.get(equipe.getjoueuracontroler()).getx())-size/2-1));
   	     Integer J =(int) (Math.floor(echelle*(equipe.joueurs.get(equipe.getjoueuracontroler()).gety())-size/2-1));
   	     g2d.fillOval(I,J , size+2, size+2);
	}

}
