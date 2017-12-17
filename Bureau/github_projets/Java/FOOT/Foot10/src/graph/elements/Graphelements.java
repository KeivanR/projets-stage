package graph.elements;

import java.awt.Graphics;

public interface Graphelements {
  
	public void paint(Graphics g,double ordonnee, double abscisse, int echelle);
	public void paint(Graphics g, double ordonnee, double abscisse, int size, int echelle );
}
