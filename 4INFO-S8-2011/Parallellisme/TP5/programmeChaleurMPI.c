#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define LARGEUR 6
#define HAUTEUR 6

#define K 2
#define SEUIL 10
#define MAX 50

#define TAILLEPAQUET 2

//Affiche la matrice donnée en paramètre
void afficherMatrice(double M[LARGEUR+2][HAUTEUR+2]);;

/*********************
*** PRINCIPE ***
Le principe du logiciel est toujours de calculer la propagation de la chaleur sur la plaque.
Cependant ici nous allons répartir ce travail entre plusieurs processus voire même plusieurs machines.


*** ALGORITHME ***
->Processus/Machine Principal(e) :
	1. Création et initialisation de la matrice
	2. Tant que (delta >= SEUIL) faire
	   | 2.1 Envoyer le bord haut au premier processus fils (celui qui s'occupe du premier paquet de lignes)
	   | 2.2 Envoyer le bord bas au dernier processus fils (celui qui s'occupe du dernier paquet de lignes)
	   | 2.3 Récupérer les valeurs des deltas de chaque fils
	   |
	   | 2.4 Si delta >= SEUIL alors
	   |	 | 2.4.1 Envoyer confirmation aux fils pour qu'il refasse un nouveau calcul
	   | 2.5 Sinon
	   |	 | 2.5.1 Envoyer 0 aux fils pour qu'ils s'arrêtent
	   | 2.6 fsi
	   |
	3. ftq
	4. Récupération de la matrice auprès des fils
	5. Affichage de la matrice après calcul
	
	
	
->Processus/Machines Fils :
	1. Initialisation de la matrice (matrice représentant le paquet de lignes à traiter)
	2. Tant que confirm = 1 faire
	   | 2.1. Envoie du bord haut au voisin du haut (sauf si premier processus fils)
	   | 2.2. Envoie du bord bas au voisin du bas (sauf si dernier processus fils)
	   | 2.3. Réception du bord haut depuis le voisin du haut (ou processus pere si premier fils)
	   | 2.4. Réception du bord bas depuis le voisin du bas (ou processus pere si dernier fils)
	   | 2.5. Calcul de la nouvelle matrice et du delta
	   | 2.6. Envoie du delta au processus père
	   | 2.7. Réception de confirm
	3. ftq
	4. Envoie de la matrice au processus père
	
	
*** ATTENTION ***
Pour une raison obscure que j'ignore, j'ai utilisé les matrices comme ceci : matrice[numCOLONNE][numLIGNE].

*********************/
int main(int argc, char ** argv){

	double delta;


	int i;      /* numero du processus courant */
	int p;	/* nombre total de processus */

	int recu; /* valeur recue par le processus courant */
	MPI_Status stat; /* pour l'initialisation */
	
	int rc = MPI_Init(&argc, &argv); 
	if(rc != MPI_SUCCESS){
		fprintf(stderr, "Erreur lors de l'initialisation de MPI\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}
	
	MPI_Comm_rank(MPI_COMM_WORLD, &i); // Rang du processus
	MPI_Comm_size(MPI_COMM_WORLD, &p); // Nombre de processus
	
	//printf ("Number of tasks= %d My rank= %d\n", p,i);
	
	
	//DEBUT
	//Processus principal
	if(i == 0){
	
		double T[LARGEUR+2][HAUTEUR+2], T1[LARGEUR+2][HAUTEUR+2];
		int cptIteration = 0;
	
		//INITIALISATION

		delta = MAX;

		int cptI, cptJ;
		for(cptI = 0; cptI < LARGEUR+2; cptI++){
			for(cptJ = 0; cptJ < HAUTEUR+2; cptJ++){
				if(cptI == 0 || cptI == LARGEUR+1 || cptJ == 0 || cptJ == HAUTEUR+1){
					T[cptI][cptJ] = MAX;
					T1[cptI][cptJ] = MAX;	
				}
				else{
					T[cptI][cptJ] = 0;
					T1[cptI][cptJ] = 0;
				}
			}
		}
	
		while(delta >= SEUIL){
			delta = 0;
		
			/*
			  Envoie des BORDS
			*/
				//HAUT
			int cptC = 0;
			for(cptC = 0; cptC < LARGEUR+2; cptC++){
				MPI_Send(&T[cptC][0], 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
			}
				
				//BAS
			for(cptC = 0; cptC < LARGEUR+2; cptC++){
				MPI_Send(&T[cptC][HAUTEUR+1], 1, MPI_DOUBLE, p-1, 0, MPI_COMM_WORLD);
			}
			
			/*
			  Attente de la réception des deltas
			*/
			int cptP;
			for(cptP = 1; cptP < p; cptP++){
				double tmpDelta;
				MPI_Recv(&tmpDelta, 1, MPI_DOUBLE, cptP, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
				
				delta += tmpDelta;
			}
			
			//Calcul delta final
			delta = delta / (p-1);
			
			//Traitement de fin d'itération
			if(delta >= SEUIL){
			
				printf("Delta = %2.2f\n", delta);
			
				for(cptP = 1; cptP < p; cptP++){
						int tmp = 1;
						MPI_Send(&tmp, 1, MPI_INT, cptP, 0, MPI_COMM_WORLD);
				}
			}
			else{
				for(cptP = 1; cptP < p; cptP++){
						int tmp = 0;
						MPI_Send(&tmp, 1, MPI_INT, cptP, 0, MPI_COMM_WORLD);
				}
			}
			
			cptIteration++;
		}
		
		/*
		  Attente de la matrice
		*/
		int cpt = 0;
		
		//Récupération de chaque paquet
		for(cpt = 1; cpt < p; cpt++){
			int cptC = 0;
			
			int cptL;
			//Récupération de chaque ligne du paquet
			for(cptL = 0; cptL < TAILLEPAQUET; cptL++){
				for(cptC = 1; cptC < LARGEUR + 1; cptC++){
				
					//Récupération de la case courante du paquet
					MPI_Recv(&T1[cptC][(cpt-1)*TAILLEPAQUET + cptL + 1], 1, MPI_DOUBLE, cpt, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
					
					//Recopie de T1 dans T
					T[cptC][(cpt-1)*TAILLEPAQUET + cptL + 1] = T1[cptC][(cpt-1)*TAILLEPAQUET + cptL + 1];
				}
			}
		}
		afficherMatrice(T);
		printf("Delta = %2.2f\n", delta);
		sleep(1);
	}
	//Pour les autres processus
	else if(i > 0){

		double delta;
		double M[LARGEUR+2][TAILLEPAQUET+2];
		double M1[LARGEUR+2][TAILLEPAQUET+2];
		
		
		//INITIALISATION DE LA MATRICE
		int cptI, cptJ;
		for(cptJ = 1; cptJ <= TAILLEPAQUET; cptJ++){
			for(cptI = 0; cptI <= LARGEUR+1; cptI++){
				if(cptI == 0 || cptI == LARGEUR+1 || cptJ == 0 || cptJ == TAILLEPAQUET+1){
					M[cptI][cptJ] = MAX;
					M1[cptI][cptJ] = MAX;	
				}
				else{
					M[cptI][cptJ] = 0;
					M1[cptI][cptJ] = 0;
				}
			}
		}
		
		int confirm = 1;
		
		while(confirm){
			delta = 0;
		
		
			/*
			 ENVOIE DES BORDS
			*/
			int cptC;
			
			
			//HAUT
			if(i > 1){
				for(cptC = 0; cptC < LARGEUR+2; cptC++){
					MPI_Send(&M[cptC][1], 1, MPI_DOUBLE, i-1, 0, MPI_COMM_WORLD);
				}
			}
			
			//BAS
			if(i < p-1){
				for(cptC = 0; cptC < LARGEUR+2; cptC++){
					MPI_Send(&M[cptC][TAILLEPAQUET], 1, MPI_DOUBLE, i+1, 0, MPI_COMM_WORLD);
				}
			}		
		
		
			/*
			 Attente des valeurs des bords
			*/
			
				//BORD HAUT
			for(cptC = 0; cptC < LARGEUR+2; cptC++){
				MPI_Recv(&M[cptC][0], 1,MPI_DOUBLE, i-1, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
			}
			
			
				//BORD BAS
			if(i <= p-1){
				for(cptC = 0; cptC < LARGEUR+2; cptC++){
					MPI_Recv(&M[cptC][TAILLEPAQUET+1], 1, MPI_DOUBLE, (i+1)%p, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
				}
			}
						
			
			/*
			  CALCUL
			*/
			int cptI, cptJ;
			for(cptI = 1; cptI < LARGEUR + 1; cptI++){
				for(cptJ = 1; cptJ < TAILLEPAQUET + 1; cptJ++){
					M1[cptI][cptJ] = (M[cptI][cptJ+1] + M[cptI][cptJ-1] + M[cptI+1][cptJ] + M[cptI-1][cptJ] + M[cptI][cptJ]) / 5;
					
					delta += abs(M1[cptI][cptJ] - M[cptI][cptJ]);
					
					int cptL;
					int cptC;
					for(cptC = 1; cptC < LARGEUR + 1; cptC++){
						for(cptL = 1; cptL < TAILLEPAQUET + 1; cptL++){
							M[cptC][cptL] = M1[cptC][cptL];
						}
					}
				}
			}
			
			//ENVOIE DU DELTA
			MPI_Send(&delta, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
			
			//RECUPERATION DE LA CONFIRMATION
			MPI_Recv(&confirm, 1, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
		}
		
		//ENVOIE DES DONNEES
		for(cptJ = 1; cptJ < TAILLEPAQUET + 1; cptJ++){
			for(cptI = 1; cptI < LARGEUR + 1; cptI++){
				MPI_Send(&M[cptI][cptJ], 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
			}
		}
	}
	
	MPI_Finalize();

	return 0;
}

void afficherMatrice(double M[LARGEUR+2][HAUTEUR+2]){
	int i, j;
	for(j = 0; j < HAUTEUR+2; j++){
		for(i = 0; i < LARGEUR+2; i++){
			printf("%2.2f\t", M[i][j]);
		}
		printf("\n");
	}
	
	printf("\n\t--------------\n");
}
