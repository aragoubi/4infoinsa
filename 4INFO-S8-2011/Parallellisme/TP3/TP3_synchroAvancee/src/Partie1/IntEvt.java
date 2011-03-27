package Partie1;

public class IntEvt {
	int valeur;
	boolean canRead = false;
	Thread author;
	

	public IntEvt(){
		author = Thread.currentThread();
		canRead = false;
	}
	
	public synchronized int read(){
		while(!canRead){
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		return valeur;
	}
	
	public synchronized void write(int i){
		if(Thread.currentThread() == author){
			System.out.println("Ecriture ok");
			valeur = i;
			canRead = true;
			notifyAll();
		}
		else{
			System.out.println("Ce n'est pas l'auteur");
		}
	}
}
