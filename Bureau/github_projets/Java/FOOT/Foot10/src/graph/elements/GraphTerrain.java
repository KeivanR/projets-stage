package graph.elements;

import java.awt.Color;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;

public class GraphTerrain implements Graphelements{

	public GraphTerrain()
	{
		
	}
	
	public void paint(Graphics g,double  ordonnee,double  abscisse, int echelle)
	{
		this.paint(g,( int ) ordonnee,(int) abscisse,8, echelle);
	}
	
	
public void paint(Graphics g,double  ordonnee,double  abscisse, int size,  int echelle)
{
	 int t = 2; //Largeur des bandes du terrain
	  int longueur=echelle*5;
	  int largeur = echelle*3;
	  
   Graphics2D g2d = (Graphics2D)g;    
   
   GradientPaint gp = new GradientPaint(0, 0, new Color(46,191,94), 25,0, new Color(9,168,59), true);                
   GradientPaint gp2 = new GradientPaint(0, 0, new Color(/*0*/255,255,255), 0,0, new Color(0,0,0), true);
   
   //Fond Terrain 
   g2d.setPaint(gp);
   g2d.fillRoundRect((int) abscisse, ( int ) ( int ) ordonnee,longueur, largeur, 10, 10);
   
   //Rond centrale
   int diametre =(int) Math.floor(largeur*(((float)130)/((float) 360)));
   g2d.setPaint(gp2);
   g2d.fillOval((int) abscisse+(longueur-diametre)/2, ( int ) ordonnee+(largeur-diametre)/2, diametre,diametre);
   g2d.setPaint(gp);
   g2d.fillOval((longueur-diametre)/2+(int) abscisse+t, ( int ) ordonnee+(largeur-diametre)/2+t, diametre-2*t,diametre-2*t);
   g2d.setPaint(gp2);   
   g2d.fillRect((int) abscisse + longueur/2-t, ( int ) ordonnee, t, largeur);
   g2d.fillRect((int) abscisse, ( int ) ordonnee, t, largeur);
   //g2d.fillRect((int) abscisse+longueur-t, ( int ) ordonnee, t, largeur);
   //g2d.fillRect((int) abscisse, ( int ) ordonnee, longueur, t);
   
   //Surface de réparation gauche
  
   int largeursup =(int) Math.floor(largeur*(((float)140)/((float) 360)));
   
   g2d.fillRect((int) abscisse, ( int ) ordonnee+largeur/6, largeursup, t);
   g2d.fillRect((int) abscisse+largeursup-t,( int ) ordonnee+largeur/6 , t,(4*largeur)/6);
   g2d.fillRect((int) abscisse, ( int ) ordonnee+largeur-largeur/6, largeursup, t);
   
   //6 m de gauche 
   int largeur6m =(int) Math.floor(largeur*(((float)50)/((float) 360)));
   g2d.fillRect((int) abscisse, ( int ) ordonnee+largeur/3, largeur6m, t);
   g2d.fillRect((int) abscisse+largeur6m-t,( int ) ordonnee+largeur/3, t,largeur/3);
   g2d.fillRect((int) abscisse, ( int ) ordonnee+largeur-largeur/3, largeur6m, t);
   
   
   
   //Surface de réparation droite 
    g2d.fillRect((int) abscisse+longueur-largeursup-t, ( int ) ordonnee+largeur/6, largeursup, t);
    g2d.fillRect((int) abscisse+longueur-largeursup-t,( int ) ordonnee+largeur/6 , t, (4*largeur)/6);
     g2d.fillRect((int) abscisse+longueur-largeursup-t, ( int ) ordonnee+largeur-largeur/6, largeursup, t);
   
   //6 m de droite
     g2d.fillRect((int) abscisse+longueur-largeur6m, ( int ) ordonnee+largeur/3, largeur6m, t);
     g2d.fillRect((int) abscisse-t+longueur-largeur6m,( int ) ordonnee+largeur/3, t,largeur/3);
     g2d.fillRect((int) abscisse+longueur-largeur6m, ( int ) ordonnee+largeur-largeur/3, largeur6m, t);
}
}
