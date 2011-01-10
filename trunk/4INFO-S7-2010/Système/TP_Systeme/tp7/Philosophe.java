public class Philosophe extends Thread{
	public static final int N = 10;
	
	private int pos;
	private static Baguette[] baguettes;
		
	public Philosophe(int posit, Baguette[] tab){
		pos = posit;
		baguettes = tab;
	}
	
	public void run(){
		 while(true){
			 try{
				 manger();
				 sleep(5000,0); //reflexion
			 }
			 catch(Exception e){
				 
			 }
		 }
	 }
	
	public void manger() throws Exception{
		int iGauche = pos % N;
		int iDroite = (pos+1) % N;
		synchronized(baguettes){
			synchronized(baguettes[iDroite]){
				if(baguettes[iDroite].libre){
					baguettes[iDroite].libre = false;
					sleep(100,0); //temps de prise de baguette
				} else {
					System.out.println(pos+" attend sa baguette droite");
					baguettes[iDroite].wait();
					baguettes[iDroite].libre = false;
					sleep(100,0); //temps de prise de baguette
				}
			}	
			synchronized(baguettes[iGauche]){
				if(baguettes[iGauche].libre){
					baguettes[iGauche].libre = false;
					sleep(100,0); //temps de prise de baguette
				} else {
					System.out.println(pos+" attend sa baguette gauche");
					baguettes[iGauche].wait();
					baguettes[iGauche].libre = false;
					sleep(100,0); //temps de prise de baguette
				}
			}
		}
		System.out.println("Debut du repas de "+pos);
		sleep(5000,0); //on mange
		System.out.println("Fin du repas de "+pos);
		synchronized(baguettes[iDroite]){
			baguettes[iDroite].libre = true;
			baguettes[iDroite].notify();
		}
		synchronized(baguettes[iGauche]){
			baguettes[iGauche].libre = true;
			baguettes[iGauche].notify();
		}
	}
	
	public static void main(String[] args){
		Baguette[] table = new Baguette[N];
		Philosophe[] phil = new Philosophe[N];
		for(int i = 0; i < N; i++){
			phil[i] = new Philosophe(i, table);
			table[i] = new Baguette(true);
		}
		
		for(int i = 0; i < N; i++){
			phil[i].start();
		}
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
}
