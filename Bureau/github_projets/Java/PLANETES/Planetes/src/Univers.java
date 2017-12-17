import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JPanel;


public class Univers extends JPanel{
	
	private static final long serialVersionUID = 1L;
	public boolean afficheAccel=false, afficheVitesse=false;
	public double zoom=1;
	public int zoomX=200;
	public int zoomY=200;
	public int iMoteur=0, iRef=-1, moteur=0;
	public double vRefX=0,vRefY=0;
	public double G=0.005;
	int i;
	ArrayList<Corps> mesCorps=new ArrayList<Corps>();
	Univers(int dimX, int dimY){
		setBackground(Color.BLACK);
		setPreferredSize(new Dimension(dimX, dimY));
		setVisible(true);
	}
	 public void paintComponent(Graphics g) {
			super.paintComponent(g);
			for (i=0;i<mesCorps.size();i++) {
				mesCorps.get(i).dessiner(g,zoom,zoomX,zoomY);
				if (i==iMoteur) mesCorps.get(i).moteur(g,zoom,zoomX,zoomY);
				if (afficheVitesse) mesCorps.get(i).fleche(g,zoom,zoomX,zoomY);
				if (afficheAccel) mesCorps.get(i).accel(g,zoom,zoomX,zoomY);}
		 }
}
