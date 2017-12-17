


class Jouer { 
Fenetre maFenetre = new Fenetre();
boolean collision=false;
Jouer() { 
	maFenetre.setVisible(true);
}
	
	
	


	 
public void repeindre(){	
	 //LANCEMENT
	
			try {
					maFenetre.monUnivers.repaint();
					Thread.sleep(1);    
			}

				
						
			catch (InterruptedException ie) {if (Thread.interrupted()) Thread.currentThread().interrupt();}	
	   } 

public void mouvement(Univers monUnivers, int precision){
	
	int i,j;
	double dt=(double)1/(double)precision;
	double xi, yi; 
	double thetai;
	double dcarrei;
	for (i=0;i<monUnivers.mesCorps.size();i++){monUnivers.mesCorps.get(i).accelX=0;monUnivers.mesCorps.get(i).accelY=0;}
	for (i=0;i<monUnivers.mesCorps.size();i++){
		xi=monUnivers.mesCorps.get(i).x;
		yi=monUnivers.mesCorps.get(i).y;
		for (j=i+1;j<monUnivers.mesCorps.size();j++){
			dcarrei=(monUnivers.mesCorps.get(j).y-yi)*(monUnivers.mesCorps.get(j).y-yi)+(monUnivers.mesCorps.get(j).x-xi)*(monUnivers.mesCorps.get(j).x-xi);
			if (dcarrei>Math.pow(monUnivers.mesCorps.get(i).rayon+monUnivers.mesCorps.get(j).rayon,2)){
				thetai=Math.atan((monUnivers.mesCorps.get(j).y-yi)/(monUnivers.mesCorps.get(j).x-xi));
				if (monUnivers.mesCorps.get(j).x<xi) thetai+=Math.PI;
				monUnivers.mesCorps.get(i).accelX+=monUnivers.G*monUnivers.mesCorps.get(j).masse/dcarrei*dt*Math.cos(thetai);
				monUnivers.mesCorps.get(i).accelY+=monUnivers.G*monUnivers.mesCorps.get(j).masse/dcarrei*dt*Math.sin(thetai);
				monUnivers.mesCorps.get(j).accelX+=monUnivers.G*monUnivers.mesCorps.get(i).masse/dcarrei*dt*Math.cos(thetai+Math.PI);
				monUnivers.mesCorps.get(j).accelY+=monUnivers.G*monUnivers.mesCorps.get(i).masse/dcarrei*dt*Math.sin(thetai+Math.PI);
			}	
		}
		
		if (i==monUnivers.iMoteur){
			if (monUnivers.moteur==1) {monUnivers.mesCorps.get(monUnivers.iMoteur).accelX+=0.05*Math.cos(monUnivers.mesCorps.get(monUnivers.iMoteur).thetaMoteur+Math.PI);monUnivers.mesCorps.get(monUnivers.iMoteur).accelY+=0.05*Math.sin(monUnivers.mesCorps.get(monUnivers.iMoteur).thetaMoteur+Math.PI);}
			if (monUnivers.moteur==-1) {monUnivers.mesCorps.get(monUnivers.iMoteur).accelX-=0.05*Math.cos(monUnivers.mesCorps.get(monUnivers.iMoteur).thetaMoteur+Math.PI);monUnivers.mesCorps.get(monUnivers.iMoteur).accelY-=0.05*Math.sin(monUnivers.mesCorps.get(monUnivers.iMoteur).thetaMoteur+Math.PI);}
		}
		monUnivers.mesCorps.get(i).vitesseX+=monUnivers.mesCorps.get(i).accelX;
		monUnivers.mesCorps.get(i).vitesseY+=monUnivers.mesCorps.get(i).accelY;
		
	}
	if (monUnivers.iRef>=0){
		for (i=0;i<monUnivers.mesCorps.size();i++){
			monUnivers.mesCorps.get(i).vitesseX+=monUnivers.vRefX; monUnivers.mesCorps.get(i).vitesseY+=monUnivers.vRefY;
		}
		monUnivers.vRefX=monUnivers.mesCorps.get(monUnivers.iRef).vitesseX;
		monUnivers.vRefY=monUnivers.mesCorps.get(monUnivers.iRef).vitesseY;
	}
	for (i=0;i<monUnivers.mesCorps.size();i++){
		if (monUnivers.iRef>=0){
			monUnivers.mesCorps.get(i).vitesseX-=monUnivers.vRefX; monUnivers.mesCorps.get(i).vitesseY-=monUnivers.vRefY;
		}
		monUnivers.mesCorps.get(i).x+=monUnivers.mesCorps.get(i).vitesseX*dt;
		monUnivers.mesCorps.get(i).y+=monUnivers.mesCorps.get(i).vitesseY*dt;
	}

}



  public static void main(String[] argv) {
	Jouer monJeu = new Jouer();
	Corps newCorps;
	int i;
	int precision=2000;
	double dt=1/precision;
	while (true){
		precision=(int)(2000/Math.pow((double)(monJeu.maFenetre.monUnivers.mesCorps.size()+1),2));
		if (precision==0) precision=1;
		dt=1/(double)precision;
		for (i=0;i<precision;i++){
			monJeu.mouvement(monJeu.maFenetre.monUnivers,precision);
			monJeu.maFenetre.monUnivers.moteur=0;
			if (monJeu.maFenetre.pressed) {
				newCorps=monJeu.maFenetre.monUnivers.mesCorps.get(monJeu.maFenetre.monUnivers.mesCorps.size()-1);
				newCorps.x-=newCorps.vitesseX*dt;
				newCorps.y-=newCorps.vitesseY*dt;
				newCorps.vitesseX=0;
				newCorps.vitesseY=0;
				monJeu.maFenetre.monUnivers.mesCorps.set(monJeu.maFenetre.monUnivers.mesCorps.size()-1,newCorps);
			}
		}
		
		for (i=0;i<monJeu.maFenetre.monUnivers.mesCorps.size();i++){
			if (monJeu.maFenetre.pressed) {
				monJeu.maFenetre.monUnivers.mesCorps.get(monJeu.maFenetre.monUnivers.mesCorps.size()-1).agrandir(1/monJeu.maFenetre.monUnivers.zoom/Math.pow((double)(monJeu.maFenetre.monUnivers.mesCorps.size()+1),2));	
			}
			if (monJeu.maFenetre.gauche) monJeu.maFenetre.monUnivers.mesCorps.get(i).x+=1/monJeu.maFenetre.monUnivers.zoom;
			if (monJeu.maFenetre.droite) monJeu.maFenetre.monUnivers.mesCorps.get(i).x-=1/monJeu.maFenetre.monUnivers.zoom;
			if (monJeu.maFenetre.haut) monJeu.maFenetre.monUnivers.mesCorps.get(i).y+=1/monJeu.maFenetre.monUnivers.zoom;
			if (monJeu.maFenetre.bas) monJeu.maFenetre.monUnivers.mesCorps.get(i).y-=1/monJeu.maFenetre.monUnivers.zoom;
		}
		monJeu.repeindre();
		//monJeu.maFenetre.monUnivers.afficheAccel=monJeu.maFenetre.monListener.accel;
		//monJeu.maFenetre.monUnivers.afficheVitesse=monJeu.maFenetre.monListener.vitesse;
   }  
}
  }