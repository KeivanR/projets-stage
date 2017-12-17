package jeux;
import java.awt.Color;

import Elements.Ballon;
import Elements.Equipe;
import Elements.Terrain;
import graph.Screen;
import graph.elements.Graphcursor;

public class Etat {
	
	Equipe equipe1;
	Equipe equipe2;
	Ballon ballon;
	Terrain terrain;
	int equipeac;
	int joueurac;
	int puissancejac;
	Screen s0;
	static double time;
	static double dt=0.01;
	Graphcursor graphcursor;
	
	public Etat()
	{
		time=0;
		terrain=new Terrain(100,60,8,-4000);
		ballon = new Ballon((int)Terrain.dimX/2,(int)Terrain.dimY/2);
		equipe1 = new Equipe(Terrain.gauche,true, new Color(255,255,255));
		equipe1.ajouterexistejoueuracontroler(true);
		equipe2 = new Equipe(Terrain.droite,false,new Color(0,0,255));
		s0 = new Screen(equipe1);
		graphcursor = new Graphcursor(equipe1);
	}
	
	
	
	public Etat nextEtat()
	{
		
		Etat.time=Etat.time+Etat.dt;
		terrain=new Terrain(100,60,8,-4000);
		ballon = new Ballon((int)Terrain.dimX/2,(int)Terrain.dimY/2);
		this.setequipe1(this.getequipe1().etatSuivant());
		this.setequipe2(this.getequipe2().etatSuivant());
		this.setballon(this.getballon().etatSuivant());
		s0.update();
		return this;
	}
	
	
	
	public void setequipe1(Equipe equipe1)
	{
		this.equipe1=equipe1;
	}
	
	public void setequipe2(Equipe equipe2)
	{
		this.equipe2=equipe2;
	}
	public void setballon(Ballon ballon)
	{
		this.ballon=ballon;
	}
	
	
	public Equipe getequipe1()
	{
		return equipe1;
	}
	
	public Equipe getequipe2()
	{
		return equipe2;
	}
	public Ballon getballon()
	{
		return ballon;
	}
	public Terrain getterrain()
	{
		return terrain;
	}
	public int getequipeac()
	{
		return equipeac;
	}
	public int getjoueurac()
	{
		return joueurac;
	}
	public int getpuissancejac()
	{
		return puissancejac;
	}
	public double gettime()
	{
		return time;
	}
	public Screen getscreen()
	{
		return s0;
	}
}
