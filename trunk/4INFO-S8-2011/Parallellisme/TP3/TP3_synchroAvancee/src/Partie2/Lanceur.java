package Partie2;

public class Lanceur {
	
	public static void main(String [] args){
		ObjetPartage obj = new ObjetPartage(1);
		
		Ecrivain e1 = new Ecrivain("E1", obj);
		Ecrivain e2 = new Ecrivain("E2", obj);
		
		Lecteur l1 = new Lecteur("L1", obj);
		Lecteur l2 = new Lecteur("L2", obj);
		
		e1.start();
		e2.start();
		l1.start();
		l2.start();
	}
}
