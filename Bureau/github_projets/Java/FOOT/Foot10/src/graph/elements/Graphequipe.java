package graph.elements;

import java.awt.Color;
import java.awt.Graphics;

import Elements.Equipe;

public class Graphequipe implements Graphelements {

	
	Equipe equipe;
	
	public Graphequipe(Equipe equipe)
	{
		this.equipe=equipe;
	}
	@Override
	public void paint(Graphics g, double ordonnee, double abscisse, int echelle) {
		// TODO Auto-generated method stub
        this.paint(g, ordonnee, abscisse,1, echelle);
	}

	@Override
	public void paint(Graphics g, double ordonnee, double abscisse, int size, int echelle) {
		// TODO Auto-generated method stub
		

	      for(int i=0;i<equipe.joueurs.size();i++)
	      {   
	        
	         equipe.joueurs.get(i).getgraphjoueur().paint(g,equipe.joueurs.get(i).getx(),equipe.joueurs.get(i).gety(), echelle);

	}

}
}