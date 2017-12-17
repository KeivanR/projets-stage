package graph.elements;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

public class Graphballon implements Graphelements {

	@Override
	public void paint(Graphics g, double ordonnee, double abscisse, int echelle) {
		// TODO Auto-generated method stub
      this.paint(g, ordonnee, abscisse,8 ,  echelle);
	}

	@Override
	public void paint(Graphics g, double ordonnee, double abscisse, int size , int echelle) {
		// TODO Auto-generated method stub

		Graphics2D g2d = (Graphics2D) g;
		g2d.setPaint(new Color(255,0,0));;
		  
	      Integer I =(int) (Math.floor(echelle*(ordonnee)-(size-1)/2));
		  Integer J =(int) (Math.floor(echelle*(abscisse)-(size-1)/2));
		  g2d.fillOval(I,J , size-1, size-1);
	}

}
