import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JFrame;


public class Corps extends JFrame {
	
	double masse;
	//OPTIONS
	public double rayon=10;
	public double thetaMoteur=0;
	public double  vitesseX=0, vitesseY=0;
	public double accelX=0,accelY=0;
	public double posMoteurX=0,posMoteurY=0;
	public double x,y;
	public Color couleurF=Color.GREEN;
	static final long serialVersionUID = 1;
	int i;
	public Corps(double x, double y, double rayon, double vitesseX, double vitesseY) {
			this.rayon=rayon;
			this.x=x;
			this.y=y;
			this.masse=Math.pow(rayon,3);
			this.vitesseX=vitesseX;
			this.vitesseY=vitesseY;
			}
	
	public void dessiner(Graphics g, double zoom, int zoomX, int zoomY){
		g.setColor(couleurF);
		g.fillOval((int)(zoomX+(x-rayon-zoomX)*zoom),(int)(zoomY+(y-rayon-zoomY)*zoom),(int)(2*rayon*zoom),(int)(2*rayon*zoom));  
		
	}
	public void fleche(Graphics g, double zoom, int zoomX, int zoomY){
		double taille=5;
		g.setColor(Color.RED);
		if ((vitesseY!=0)||(vitesseX!=0)){
		double theta=Math.atan(vitesseY/vitesseX); if (vitesseX<0) theta+=Math.PI;
		g.fillRect((int)(zoomX+(x+(rayon-taille)*Math.cos(theta)-zoomX)*zoom-taille/2),(int)(zoomY+(y+(rayon-taille)*Math.sin(theta)-zoomY)*zoom-taille/2),(int)(taille),(int)(taille));  
		}
		else g.fillRect((int)(zoomX+(x-zoomX)*zoom-taille/2),(int)(zoomY+(y-zoomY)*zoom-taille/2),(int)(taille),(int)(taille)); 
	}
	
	public void accel(Graphics g, double zoom, int zoomX, int zoomY){
		double taille=4;
		g.setColor(Color.BLUE);
		if ((accelX!=0)||(accelY!=0)){
		double theta=Math.atan(accelY/accelX); if (accelX<0) theta+=Math.PI;
		g.fillRect((int)(zoomX+(x+(rayon-taille)*Math.cos(theta)-zoomX)*zoom-taille/2),(int)(zoomY+(y+(rayon-taille)*Math.sin(theta)-zoomY)*zoom-taille/2),(int)(taille),(int)(taille));  
		}
		else g.fillRect((int)(zoomX+(x-zoomX)*zoom-taille/2),(int)(zoomY+(y-zoomY)*zoom-taille/2),(int)(taille),(int)(taille)); 
	}
	
	public void moteur(Graphics g, double zoom, int zoomX, int zoomY){
		double ray=3;
		g.setColor(Color.YELLOW);
		g.fillRect((int)(zoomX+(x+(rayon+ray)*Math.cos(thetaMoteur)-zoomX)*zoom-ray),(int)(zoomY+(y+(rayon+ray)*Math.sin(thetaMoteur)-zoomY)*zoom-ray),(int)(2*ray),(int)(2*ray));  
	}
	
	public void agrandir(double r){
		this.rayon+=r;
		this.masse=Math.pow(this.rayon, 3);
	}
}