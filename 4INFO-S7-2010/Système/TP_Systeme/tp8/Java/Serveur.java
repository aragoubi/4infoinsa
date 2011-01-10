import java.util.concurrent.ConcurrentSkipListSet;

public class Serveur extends Thread {
	private Journal journal;
	private int nblus;
	private int nbecrits;
	private int nbecrAtt;
	private int nblecAtt;
	public static final int K = 3;
	private int nbLecteurs;


	private boolean ecritureEnCours;
	

	private ConcurrentSkipListSet<Internaute> listeAttente;
	
	public Serveur(){
		journal = new Journal();
		nblus = 0;
		nbecrits = 0;
		nbecrAtt = 0;
		nblecAtt = 0;
		nbLecteurs = 0;
		ecritureEnCours = false;
	}
	
	public int getNbLecteurs() {
		return nbLecteurs;
	}

	public void setNbLecteurs(int nbLecteurs) {
		this.nbLecteurs = nbLecteurs;
	}
	
	public boolean isEcritureEnCours() {
		return ecritureEnCours;
	}

	public void setEcritureEnCours(boolean ecritureEnCours) {
		this.ecritureEnCours = ecritureEnCours;
	}

	public ConcurrentSkipListSet<Internaute> getListeAttente() {
		return listeAttente;
	}
	
	public synchronized  boolean estAccessibleLecture(){
			if(nbLecteurs < K && !ecritureEnCours){
			nbLecteurs++;
			nblus++;
			journal.lireArticle();
			return true;
			}
			return false;
			}
	}
	
	public synchronized  boolean estAccessibleEcriture(){
		if(nbLecteurs == 0 && !ecritureEnCours){
		ecritureEnCours = true;
		nbecrits++;
		journal.ecrireArticle();
		return true;
		}
		return false;
		}
	}
	
	public void attendre(Internaute i){
		ListeAttente.add(i);
		try {
			i.wait();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

