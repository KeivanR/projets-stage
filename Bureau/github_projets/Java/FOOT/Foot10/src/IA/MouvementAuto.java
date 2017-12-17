package IA;

import Elements.*;

public class MouvementAuto {
	public Joueur joueur;
	public MouvementAuto(Joueur joueur){
		this.joueur=joueur;
	}
	
	public double theta(double x1, double y1, double x2, double y2){
		double theta;
		if (Math.abs((x2-x1))>0.01) theta=Math.atan((y2-y1)/(x2-x1));
		else {
			 if ((y2-y1)<0) theta=-Math.PI/2;
			 else theta=Math.PI/2;
		}
		if ((x2-x1)<0) theta+=Math.PI;
		return theta;
	}
	public void courir(){
		double theta=theta(joueur.getx(),joueur.gety(),Ballon.x,Ballon.y);
		theta+=Math.PI/2;
		joueur.setv(joueur.getvmin());
		joueur.courir(theta);
	}
	
	public void courir(double xDest, double yDest){
		double theta=theta(joueur.getx(),joueur.gety(),xDest,yDest);
		joueur.setv(joueur.getvmin());
		joueur.courir(theta);
	}
	
	public void courirVersBallon(){
		double theta=theta(joueur.getx(),joueur.gety(),Ballon.x,Ballon.y);
		joueur.setv(joueur.getvmin());
		joueur.courir(theta);
	}
	
}
