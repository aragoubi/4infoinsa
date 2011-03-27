package Partie2;

public class ObjetPartage {
	
	private int valeur;
	int nbLect = 0, nbRed = 0, nbAttRed = 0;

	public ObjetPartage(int valeur){
		this.valeur = valeur;
	}
	
	public int lire() throws Exception{
		synchronized(this){
			
			if(nbAttRed > 0 || nbRed > 0)
				throw new Exception();
			
			nbLect++;
		}
		
		System.out.println("["+Thread.currentThread().getName()+"] début lecture");
		
		Thread.currentThread().sleep(100);
		
		int val = valeur;
		
		System.out.println("["+Thread.currentThread().getName()+"] viens de lire " + val);
		
		synchronized(this){
			nbLect--;
		}
		
		return val;
	}
	
	public void ecrire(int valeur) throws Exception{
		synchronized(this){
			if(nbRed > 0 || nbLect > 0){
				
				if(nbLect > 0)
					nbAttRed++;
				
				throw new Exception();
			}
			
			nbRed++;
			
			if(nbAttRed > 0)
				nbAttRed--;
		}
		
		System.out.println("["+Thread.currentThread().getName()+"] début écriture");
		
		Thread.currentThread().sleep(100);
		
		this.valeur = valeur;
		
		System.out.println("["+Thread.currentThread().getName()+"] viens d'écrire " + valeur);
		
		synchronized(this){
			nbRed--;
		}
	}
}
