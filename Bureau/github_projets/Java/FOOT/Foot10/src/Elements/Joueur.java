package Elements;

import java.awt.Color;

import IA.MouvementAuto;
import graph.Screen;
import graph.elements.*;
public class Joueur {
	
	MouvementAuto IA = new MouvementAuto(this);
	
	//variable de positionnement & deplacement
	private double x;
	private double y;
	private double theta;
	
	private double vMax=200;
	private double vMin=100;
	private double v;
	
	private boolean accelerer=false;
	
	//Zone de jeux privilegie
	private Zone zone;
	
	//Dessin du joueur
	private Graphjoueur graphjoueur;
	
	//Etat de contrôle du joueur
	private boolean Undercontrol = false;
	private boolean  select=false;
	
	
	
	//Création d'un joueur
	public Joueur(Zone zone, Color color){
		this.x=zone.xm/2;
		this.y=zone.ym;
		this.zone=zone;
		graphjoueur =new Graphjoueur(color) ;
	}
	
	
	/*
	 * action 
	 */
	
	
	//Changement de zone
	public void update(Zone zone){
		this.x=Terrain.dimX-zone.xm*0.5;
		this.y=zone.ym;
		this.zone=zone;
	}
	//Faire courir un joueur 
	public void courir(double theta){
		this.theta=theta;
		if (accelerer) v=vMax;
		else v=vMin;
	}
	
	//Faire arrêter un joueur
	public void arret(){
		v=0;
	}
	
	//Le joueur possede t-il le ballon
	public boolean possedeBallon(){
		return ((Math.abs(Ballon.x-x)<1)&&(Math.abs(Ballon.y-y)<1));
	}
	
	//Faire passer le ballon
	public void passer(double theta, double v){
		if (possedeBallon()){
		Ballon.x=x+3*Math.cos(theta);
		Ballon.y=y+3*Math.sin(theta);
		Ballon.passe(theta,v);
		}
	}
	
	//Faire passer à l'état suivant
	public void etatSuivant(){
		
		this.x+=v*Math.cos(theta)*Screen.dt;
		this.y+=v*Math.sin(theta)*Screen.dt;
		if (possedeBallon()) {
			Ballon.vX=0;
			Ballon.vY=0;
			Ballon.x=x;
			Ballon.y=y;
		}
	}
	
	
	
	/*
	 * Tout ce qui ocncerne la position du joueur 
	 */
	
	
	//recuperer la coordonnée x 
	public double getx()
	{
		return x;
	}
	//recuperer la coordonnée y
	public double gety()
	{
		return y;
	}
	//recuperer la direction 
		public double getDir(){
			return theta;
		}
	//recupérer la vitesse
	public double getv()
	{
		return v;
	}
	//initialiser la vitesse 
	public void setv(double v0)
	{
		this.v=v0;
	}
	//Recuperer la vitesse minimal 
	public double getvmin()
	{
		return this.vMin;
	}
	//recuperer l'état d'accelaration
	public boolean getaccelerer()
	{
		return this.accelerer;
	}
	//modifier l'etat d'acceleration 
	public void setaccelerer(boolean accelerer)
	{
		this.accelerer= accelerer;
	}
	
	
	/*
	 * Variable de positionnement vis à vis des autres élèents du jeux 
	 *
	 */
	
	
	//La distance du joueur au ballon 
	public double distBallon(){
		return Math.sqrt((x-Ballon.x)*(x-Ballon.x)+(y-Ballon.y)*(y-Ballon.y));
	}
	//La distance du joueur 
	public double distBallonP(){
		return Math.sqrt((x-Ballon.xP)*(x-Ballon.xP)+(y-Ballon.yP)*(y-Ballon.yP));
	}
	// Quel est la zone attribuer du joueur 
	
	public Zone getZone()
	{
		return this.zone;
	}
	
	// Le joeur est il dans sa zone
	public boolean horsX(double x){
		return zone.horsX(x);
	}
	
	public boolean horsY(double y){
		return zone.horsY(y);
	}
	
	public boolean horsZone(){
		return zone.horsX(x)||zone.horsY(y);
	}
	//Changer de zone
	public void bordsOpposés(){
		zone.x1=Terrain.dimX-zone.x1;
		zone.x2=Terrain.dimX-zone.x2;
		zone.xm=(double)(zone.x1+zone.x2)/2;
		update(zone);
	}
	//Revenir dans sa zone 
	public void seReplacer(){
		IA.courir(zone.xm, zone.ym);
	}
	
	
	
	/*
	 * Element relatif aux controle du joueur 
	 */
	
	
	// LE joueur est il controlé
		public boolean isSelect()
	{
		return this.select;
	}
	
	public boolean isUndercontrol()
	{
		return this.Undercontrol;
	}
	//Choisir joueur controle
		public void setSelect( boolean select )
		{
			this.select=select;
		}
	//Prendre le controle du joeuur 
	public void control()
	{
		this.Undercontrol=true;
	}
	//Quitter le controle du joueur
	public void uncontrol()
	{
		this.Undercontrol=false;
	}
	
	
	/*
	 * Element graphique 
	 * 
	 */
	
	
	//Recuperer le graph du joueur 
		public Graphjoueur getgraphjoueur()
	{
		return graphjoueur;
	}
}
