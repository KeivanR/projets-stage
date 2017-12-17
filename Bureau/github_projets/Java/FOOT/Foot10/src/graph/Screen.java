package graph;
import java.awt.Color;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JFrame;
import javax.swing.JPanel;

import Elements.Equipe;
import contrôle.Jcontrôle;
import jeux.Etat;



public class Screen extends JFrame {

	JPanel pan = new JPanel();
	public static double dt=0.001;
	Jcontrôle jc;
	int joueurcontrolée=0;
	Equipe equipe;
	public Screen(Equipe equipe)
	{
	    //Définit un titre pour notre fenêtre
	    this.setTitle("Screen");
	    //Définit sa taille : 400 pixels de large et 100 pixels de haut
	    this.setSize(1018,640);
	    //Nous demandons maintenant à notre objet de se positionner au centre
	    this.setLocationRelativeTo(null);
	    //Termine le processus lorsqu'on clique sur la croix rouge
	    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    //Et enfin, la rendre visible        
	    this.setVisible(true);
       //couleur du fond 
	    pan.setBackground(Color.DARK_GRAY);
	   //on applique à notre écran
	    jc=new Jcontrôle(equipe);
	    this.addKeyListener(jc);
	    this.equipe=equipe;
	    }
	
	public Screen(Etat etat)
	{
	    //Définit un titre pour notre fenêtre
	    this.setTitle("Screen");
	    //Définit sa taille : 400 pixels de large et 100 pixels de haut
	    this.setSize(1018,640);
	    //Nous demandons maintenant à notre objet de se positionner au centre
	    this.setLocationRelativeTo(null);
	    //Termine le processus lorsqu'on clique sur la croix rouge
	    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    //Et enfin, la rendre visible        
	    this.setVisible(true);
       //couleur du fond 
	    pan.setBackground(Color.DARK_GRAY);
	   //on applique à notre écran
	    jc=new Jcontrôle(etat.getequipe1());
	    this.addKeyListener(jc);
	    
	    }

	
	public void modifPan(Pan pan){
		
		this.pan=pan;
		this.setContentPane(pan);
	   
	}
	
	public JPanel getPan(){
		
		return pan;
		
	}
	
	
	 public void refresh(){
		    
		      pan.repaint();  
		      try {
		        Thread.sleep(10);
		      } catch (InterruptedException e) {
		        e.printStackTrace();
		      }
		     
		}
	 
	public Jcontrôle getjccontrôle()
	 {
		 return jc;
	 }
	
	public void updatejoueurcontrolée()
	{  
		
		jc.setJoueur();
		jc.accelJoueur();
		this.joueurcontrolée=jc.getjoueur();
		((Pan) this.pan).updatejoueurcontrolée(joueurcontrolée);
	}
	
	public void updatepuissancej(){
		((Pan) this.pan).updatepuissancej(jc.getpuissance());
	}
	 
	public void update(){
		this.updatejoueurcontrolée();
		this.updatepuissancej();
	}
	 
	
	 
}



