package Elements;

import graph.Screen;
import graph.elements.Graphballon;
import graph.elements.Graphjoueur;

public class Ballon {
	
	//Variable de position et déplacement 
	public static double x;
	public static double y;
	
	public static double xP=x;
	public static double yP=y;
	
	public static double vX;
	public static double vY;
	
	//Etat ballon 
	public static boolean passe=false;
	public static int butsDroite=0, butsGauche=0;
	
	//grpahique ballon 
	public Graphballon graphballon;
	
	public Ballon(double x, double y){
		Ballon.x=x;
		Ballon.y=y;
		graphballon=new Graphballon();
	}
	
	
	public static void passe(double theta, double v){
		double t=0.06 ;
		 vX =  v*Math.cos(theta);
		 vY =  v*Math.sin(theta);
		 xP=x+vX*t;
		 yP=y+vY*t; 
		 passe=true;
	}
	
	public boolean but(int camp){
		if (camp==Terrain.gauche) return ((Ballon.x<1)&&(Ballon.y>Terrain.dimY/2-Terrain.lBut/2)&&(Ballon.y<Terrain.dimY/2+Terrain.lBut/2));
		else return ((Ballon.x>Terrain.dimX-1)&&(Ballon.y>Terrain.dimY/2-Terrain.lBut/2)&&(Ballon.y<Terrain.dimY/2+Terrain.lBut/2));
	}
	public boolean sortieSM(){
		return sortieSM(Terrain.gauche)||sortieSM(Terrain.droite);
	}
	public boolean sortieSM(int camp){
		if (camp==Terrain.gauche) return ((Ballon.x<1)&&!but(Terrain.gauche));
		else return ((Ballon.x>Terrain.dimX-1)&&!but(Terrain.droite));
	}
	
	public boolean sortieT(){
		return (Ballon.y<0)||(Ballon.y>Terrain.dimY);
	}
	
	public void touche(double camp){
		vX=0;
		vY=0;
	}
	
	public void sixMetres(double camp){
		vX=0; vY=0;
		Ballon.y=Terrain.dimY/2;
		if (camp==Terrain.gauche) Ballon.x=6;
		else Ballon.x=Terrain.dimX-6;
	}
	
	public void coupEnvoi(){
		vX=0; vY=0;
		Ballon.x=Terrain.dimX/2;
		Ballon.y=Terrain.dimY/2;
	}
	
	public Ballon etatSuivant(){
		if (Math.abs(vX)-Math.abs(Terrain.ralentissement*Screen.dt*Math.cos(getDir()))<0) vX=0;
		else vX+=Terrain.ralentissement*Screen.dt*Math.cos(getDir());
		if (Math.abs(vY)-Math.abs(Terrain.ralentissement*Screen.dt*Math.sin(getDir()))<0) vY=0;
		else vY+=Terrain.ralentissement*Screen.dt*Math.sin(getDir());
		Ballon.x+=vX*Screen.dt;
		Ballon.y+=vY*Screen.dt;
		if (sortieSM()){
			if (sortieSM(Terrain.gauche)) sixMetres(Terrain.gauche);
			else sixMetres(Terrain.droite);
		}
		if (sortieT()){
			touche(0);
		}
		if (but(Terrain.gauche)){
			butsDroite++;
			coupEnvoi();
			System.out.println("La droite a marqué !!\n"+butsGauche+"-"+butsDroite);
		}
		if (but(Terrain.droite)){
			butsGauche++;
			coupEnvoi();
			System.out.println("La gauche a marqué !!\n"+butsGauche+"-"+butsDroite);
		}
		return this;
	}
	
	//Ajout accesseurs
	
	public double getx()
	{
		return x;
	}
	
	public double gety()
	{
		return y;
	}
	
	public static double getv()
	{
		return Math.sqrt(vX*vX+vY*vY);
	}
	
	public double getvY()
	{
		return vY;
	}
	
	public static double getDir(){
		double theta;
		if (Math.abs(vX)>0.01) theta=Math.atan(vY/vX);
		else {
			 if (vY<0) theta=-Math.PI/2;
			 else theta=Math.PI/2;
		}
		if (vX<0) theta+=Math.PI;
		return theta;
	}
}
