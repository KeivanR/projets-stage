package Elements;

import java.awt.Color;
import java.util.ArrayList;

import contrôle.Jcontrôle;
import graph.elements.GraphTerrain;
import graph.elements.Graphcursor;
import graph.elements.Graphequipe;

public class Equipe {
	public ArrayList<Joueur> joueurs = new ArrayList<Joueur>();
	public static int nbJoueurs = 12;
	public boolean utilisée;
	private Graphequipe graphequipe;
	private Graphcursor graphcursor;
	public boolean controlerjoueur=false;
	public int joueuracontrole=0;
	public Equipe(int camp, boolean b, Color color){
		utilisée=b;
			joueurs.add(new Joueur(new Zone("GB"),color));
			joueurs.add(new Joueur(new Zone("DC"),color));
			joueurs.add(new Joueur(new Zone("DD"),color));
			joueurs.add(new Joueur(new Zone("DG"),color));
			joueurs.add(new Joueur(new Zone("MDF"),color));
			joueurs.add(new Joueur(new Zone("MC"),color));
			joueurs.add(new Joueur(new Zone("MD"),color));
			joueurs.add(new Joueur(new Zone("MG"),color));
			joueurs.add(new Joueur(new Zone("MO"),color));
			joueurs.add(new Joueur(new Zone("AC"),color));
			joueurs.add(new Joueur(new Zone("AG"),color));
			joueurs.add(new Joueur(new Zone("AD"),color));
		graphequipe = new Graphequipe(this);
		graphcursor = new Graphcursor(this);
		if (camp==Terrain.droite) bordsOpposés();
	}
	public Equipe etatSuivant(){
		int i;
		for (i=0;i<Equipe.nbJoueurs;i++){
			if (!possedeBallon()&&(!joueurs.get(i).isSelect())) joueurs.get(i).IA.courirVersBallon();
			if (!joueurs.get(i).possedeBallon()&&(joueurs.get(i).isSelect())&&(!Jcontrôle.arrow)) joueurs.get(i).IA.courirVersBallon();
			
			if ((!joueurs.get(i).isSelect())&&(joueurs.get(i).horsZone())) joueurs.get(i).seReplacer();
			joueurs.get(i).etatSuivant();
		}
		return this;
	}
	 
	public ArrayList<Joueur> getEquipe()
	{
		return joueurs;
	}
	
	public boolean possedeBallon(){
		int i;
		for (i=0;i<nbJoueurs;i++){
			if (joueurs.get(i).possedeBallon()) return true;
		}
		return false;
	}
	
	public int joueurBallon(){
		int i,iMin=0;
		double dMin=joueurs.get(0).distBallon();
		for (i=1;i<nbJoueurs;i++){
			if (joueurs.get(i).distBallon()<dMin) {
				dMin=joueurs.get(i).distBallon();
				iMin=i;
			}
		}
		return iMin;
	}
	
	public int joueurBallonP(int j){
		int i,iMin=0;
		double dMin;
		if (j!=0) dMin=joueurs.get(0).distBallonP();
		else dMin=joueurs.get(1).distBallonP();
		for (i=1;i<nbJoueurs;i++){
			if (i!=j){
				if (joueurs.get(i).distBallonP()<dMin) {
					dMin=joueurs.get(i).distBallonP();
					iMin=i;
				}
			}
		}
		return iMin;
	}
	

	public void bordsOpposés(){
		int i;
		for (i=0;i<nbJoueurs;i++){
			joueurs.get(i).bordsOpposés();
			
			joueurs.get(i).update(joueurs.get(i).getZone());
		}
	}
	
	public Graphequipe getgraph()
	{
		return graphequipe;
	}
	
	public void ajouterexistejoueuracontroler(boolean controlejoueur)
	{
	   this.controlerjoueur=controlejoueur;	
	}
	
	public void modifjoueuracontrole(int joueuracontrole)
	{   this.joueurs.get(this.joueuracontrole).setSelect(false);
		this.joueurs.get(this.joueuracontrole).uncontrol();
		this.joueuracontrole=joueuracontrole;
		this.joueurs.get(this.joueuracontrole).control();
		this.joueurs.get(this.joueuracontrole).setSelect(true);
	}
	
	public int getjoueuracontroler()
	{
		return joueuracontrole;
	}
	
	public Graphcursor getgraphcursor() {
		// TODO Auto-generated method stub
		return this.graphcursor;
	}
	public void setexistejoueuracontrole(int joueurSelectionne) {
		// TODO Auto-generated method stub
		this.joueuracontrole=joueurSelectionne;
	}
}
