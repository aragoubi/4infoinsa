package Partie2;

public class Ecrivain extends Thread{
	
	private ObjetPartage obj;

	public Ecrivain(String name, ObjetPartage obj){
		super(name);
		this.obj = obj;
	}
	
	public void run(){
		while(true){
			try{
				int val = (int) Math.round(Math.random()*100);
				obj.ecrire(val);
			}
			catch(Exception e){
				System.out.println("["+Thread.currentThread().getName()+"] fait autre chose");
			}
			
			if(Math.random() > 0.5)
				try {
					Thread.currentThread().sleep(500);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
		}
	}
}
