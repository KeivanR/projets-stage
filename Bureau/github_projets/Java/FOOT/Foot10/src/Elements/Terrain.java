package Elements;

public class Terrain {
	public static int dimX;
	public static int dimY;
	public static int lBut;
	public static int gauche = 0;
	public static int droite = 1;
	public static double ralentissement;
	public Terrain(int dimX, int dimY, int lBut, double ralentissement){
		Terrain.dimX=dimX;
		Terrain.dimY=dimY;
		Terrain.lBut=lBut;
		Terrain.ralentissement=ralentissement;
		
	}
}
