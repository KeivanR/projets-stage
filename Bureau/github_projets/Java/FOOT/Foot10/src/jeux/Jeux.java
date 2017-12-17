package jeux;
import java.awt.Color;

import Elements.Ballon;
import Elements.Equipe;
import Elements.Terrain;
import graph.Pan;
import graph.Screen;

public class Jeux {

	Etat etat; 
	
	public Jeux()
	{
		etat= new Etat();
		etat.getscreen().modifPan(new Pan(etat.getequipe1(),etat.getequipe2(),etat.getballon(),1,etat.getscreen().getjccontrôle().getjoueur()));
	}
 	public void lancerjeux()
 	{
       
		
		
		
		while(!etat.getballon().but(etat.getterrain().droite)){	
		//etat.getscreen().update();
		((Pan) etat.getscreen().getPan()).refreshplayerposition(etat.getequipe1(),etat.getequipe2(),etat.getballon());
		etat.getscreen().refresh();
		try {
			Thread.sleep(1);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		etat.nextEtat();
		
		}
		
	
 	}
}
