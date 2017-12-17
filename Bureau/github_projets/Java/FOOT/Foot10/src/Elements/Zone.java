package Elements;

public class Zone {
	
	public int x1,y1,x2,y2;
	public double xm,ym;
	
	public Zone(String poste){
		int x0=Terrain.dimX;
		int y0=Terrain.dimY;
		if (poste=="GB") bords(0,y0/2-Terrain.lBut/2,5,y0/2+Terrain.lBut/2);
		if (poste=="DD") bords(0,2*y0/3,x0/3,y0);
		if (poste=="DG") bords(0,0,x0/3,y0/3);
		if (poste=="DC") bords(0,y0/3,2*x0/6,2*y0/3);
		if (poste=="MDF") bords(x0/3,y0/3,x0/2,2*y0/3);
		if (poste=="MG") bords(x0/3,0,4*x0/6,y0/3);
		if (poste=="MD") bords(x0/3,2*y0/3,4*x0/6,y0);
		if (poste=="MC") bords(x0/2,y0/3,4*x0/6,2*y0/3);
		if (poste=="MO") bords(2*x0/3,y0/3,5*x0/6,2*y0/3);
		if (poste=="AC") bords(5*x0/6,y0/3,x0,2*y0/3);
		if (poste=="AG") bords(2*x0/3,0,x0,y0/3);
		if (poste=="AD") bords(2*x0/3,2*y0/3,x0,y0);
		xm=(double)(x1+x2)/2;
		ym=(double)(y1+y2)/2;
	}
	
	public void bords(int x1, int y1, int x2, int y2){
		this.y1=y1;
		this.x1=x1;
		this.y2=y2;
		this.x2=x2;
	}
	
	
public boolean horsX(double x){
		if (x2<x1) return (x<x2)||(x>x1);
		return (x>x2)||(x<x1);
	}
	
public boolean horsY(double y){
		return (y<y1)||(y>y2);
	}
}
