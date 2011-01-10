
public class Internaute extends Thread implements Comparable<Internaute>{
	private static Serveur serveur;
	private int priorite;
	public static final int L = 5;
	public static final int R = 6;

	public Internaute(){
		priorite = L;
	}
	
	public void setServeur(Serveur s){
		serveur = s;
	}
	
	public int compareTo(Internaute i){
		if(priorite < i.priorite)
			return -1;
		else if(priorite == i.priorite)
			return 0;
		else
			return 1;
	}
	
	public void lireArticle(){
			if(!serveur.estAccessibleLecture()){
				
				serveur.attendre(this);
			}	
		
		reflechir();
		
		serveur.getListeAttente().last().notify();
		
		priorite--;
	}
	
	public void ecrireArticle(){
		synchronized(serveur){
			
			
		}
	}
	

	private void reflechir() {
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
