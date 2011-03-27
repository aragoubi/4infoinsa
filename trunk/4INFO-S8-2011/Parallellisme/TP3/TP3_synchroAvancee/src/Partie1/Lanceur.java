package Partie1;

public class Lanceur {

	public static void main(String [] args){
		IntEvt evt = new IntEvt();
		
		Thread t2 = new Thread(new Lire(evt));
		Thread t3 = new Thread(new Lire(evt));
		
		t2.start();
		t3.start();
		
		evt.write(3);
	}
}
