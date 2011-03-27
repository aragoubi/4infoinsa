package Partie1;

public class Lire implements Runnable{

	private IntEvt evt;
	
	public Lire(IntEvt evt){
		this.evt = evt;
	}
	
	public void run(){
		System.out.println("Valeur = " + evt.read());
	}
}
