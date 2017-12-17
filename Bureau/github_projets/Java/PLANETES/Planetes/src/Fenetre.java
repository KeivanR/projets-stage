

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class Fenetre extends JFrame implements MouseListener,KeyListener,MouseMotionListener{
	
	 private JCheckBox check1 = new JCheckBox("vitesse");
	 private JCheckBox check2 = new JCheckBox("accélération");
	
	static final long serialVersionUID = 1;
	boolean pressed=false;
	boolean gauche=false,droite=false,haut=false,bas=false;
	double vX, vY;
	double vRefX=0, vRefY=0;
	int xMouse, yMouse;
	Univers monUnivers;
	JLabel titre = new JLabel("Planètes");
	JPanel entete = new JPanel();
	JPanel indications = new JPanel();
	public int dimX=1300;
	public int dimY=600;
	StateListener monListener = new StateListener();
	public Fenetre(){
		addMouseListener(this);
		addMouseMotionListener(this);
		addKeyListener(this);
		monUnivers=new Univers(dimX,dimY);
		entete.setLayout(new BorderLayout());
		check1.addActionListener(monListener);
	    check2.addActionListener(monListener);
	    indications.add(check1);
	    indications.add(check2);
		entete.add(titre);
		//add(entete, BorderLayout.NORTH);
		add(monUnivers, BorderLayout.CENTER);
		//add(indications, BorderLayout.SOUTH);
		setDefaultLookAndFeelDecorated(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();
	}
	public boolean surPlanete(int i, double x, double y){
		double xi=monUnivers.zoomX+(monUnivers.mesCorps.get(i).x-monUnivers.zoomX)*monUnivers.zoom;
		double yi=monUnivers.zoomY+(monUnivers.mesCorps.get(i).y-monUnivers.zoomY)*monUnivers.zoom;
		return ((x-5>=xi-monUnivers.mesCorps.get(i).rayon*monUnivers.zoom)&&(x-5<=xi+monUnivers.mesCorps.get(i).rayon*monUnivers.zoom)&&(y-25>=yi-monUnivers.mesCorps.get(i).rayon*monUnivers.zoom)&&(y-25<=yi+monUnivers.mesCorps.get(i).rayon*monUnivers.zoom));
	}
	@Override
	public void mouseClicked(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
	}
	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub
		int i;
		if (arg0.getButton()==MouseEvent.BUTTON1){
		monUnivers.mesCorps.add(new Corps((arg0.getX()-monUnivers.zoomX)/monUnivers.zoom+monUnivers.zoomX-5,(arg0.getY()-monUnivers.zoomY)/monUnivers.zoom+monUnivers.zoomY-25,0,0,0));
		pressed=true;
		monUnivers.iMoteur=monUnivers.mesCorps.size()-1;
		//monUnivers.G*=1.5;
		}
		else {
			for (i=0;i<monUnivers.mesCorps.size();i++){
				if (surPlanete(i,arg0.getX(),arg0.getY())) monUnivers.iMoteur=i;
				}
			}
			monUnivers.mesCorps.get(monUnivers.iMoteur).thetaMoteur=0;
		
	}
	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		pressed=false;
	}
	@Override
	public void keyPressed(KeyEvent arg0) {
		// TODO Auto-generated method stub
		int i,k;
		boolean vide=true;
		if (arg0.getKeyCode()==KeyEvent.VK_DOWN) {monUnivers.moteur=-1;}
		if (arg0.getKeyCode()==KeyEvent.VK_UP) {monUnivers.moteur=1;}
		if (arg0.getKeyCode()==KeyEvent.VK_LEFT) {monUnivers.mesCorps.get(monUnivers.iMoteur).thetaMoteur-=0.1;}
		if (arg0.getKeyCode()==KeyEvent.VK_RIGHT) {monUnivers.mesCorps.get(monUnivers.iMoteur).thetaMoteur+=0.1;}
		if (arg0.getKeyChar()=='z') {monUnivers.zoomX=xMouse;monUnivers.zoomY=yMouse;monUnivers.zoom+=0.1;}
		if (arg0.getKeyChar()=='d') {monUnivers.zoomX=xMouse;monUnivers.zoomY=yMouse;monUnivers.zoom-=0.1;}
		if (arg0.getKeyChar()=='r'){
			for (k=0;(k<monUnivers.mesCorps.size())&&(vide);k++){
				if (surPlanete(k,xMouse,yMouse)) {
					vide=false;
					for (i=0;i<monUnivers.mesCorps.size();i++){
						monUnivers.mesCorps.get(i).vitesseX+=monUnivers.vRefX; monUnivers.mesCorps.get(i).vitesseY+=monUnivers.vRefY;
					}
					monUnivers.iRef=k;
					monUnivers.vRefX=monUnivers.mesCorps.get(monUnivers.iRef).vitesseX;
					monUnivers.vRefY=monUnivers.mesCorps.get(monUnivers.iRef).vitesseX;
					for (i=0;i<monUnivers.mesCorps.size();i++){
						monUnivers.mesCorps.get(i).vitesseX-=monUnivers.vRefX; monUnivers.mesCorps.get(i).vitesseY-=monUnivers.vRefY;
					}
				}
			}
			if (vide)  {monUnivers.vRefX=0;monUnivers.vRefY=0;monUnivers.iRef=-1;}	
		}
		if (arg0.getKeyCode()==KeyEvent.VK_DELETE){
			for (i=0;i<monUnivers.mesCorps.size();i++){
				if (surPlanete(i,xMouse,yMouse)) monUnivers.mesCorps.remove(i);
			}
		}
		if (arg0.getKeyCode()==KeyEvent.VK_N){
			monUnivers.mesCorps.add(new Corps((xMouse-monUnivers.zoomX)/monUnivers.zoom+monUnivers.zoomX-5,(yMouse-monUnivers.zoomY)/monUnivers.zoom+monUnivers.zoomY-25,1,0.05,0.05));
		monUnivers.iMoteur=monUnivers.mesCorps.size()-1;
		//monUnivers.G*=1.5;
		monUnivers.mesCorps.get(monUnivers.iMoteur).thetaMoteur=0;
		}
		if (arg0.getKeyChar()=='a'){
			if (monUnivers.afficheAccel) monUnivers.afficheAccel=false; else monUnivers.afficheAccel=true;
		}
		if (arg0.getKeyChar()=='v'){
			if (monUnivers.afficheVitesse) monUnivers.afficheVitesse=false; else monUnivers.afficheVitesse=true;
		}
	}
	@Override
	public void keyReleased(KeyEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void keyTyped(KeyEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseDragged(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		xMouse=e.getX();
		yMouse=e.getY();
		if (e.getX()<20)  gauche=true; else gauche=false;
		if (e.getX()>dimX-20) droite=true; else droite=false;
		if (e.getY()<40) haut=true; else haut=false;
		if (e.getY()>dimY-40) bas=true; else bas=false;
	}
	
	
	
}



class StateListener implements ActionListener{
	public boolean vitesse,accel;
    public void actionPerformed(ActionEvent e) {
    if (((JCheckBox)e.getSource()).getText()=="vitesse") vitesse = ((JCheckBox)e.getSource()).isSelected();
    if (((JCheckBox)e.getSource()).getText()=="accélération") accel = ((JCheckBox)e.getSource()).isSelected();
    }
}
