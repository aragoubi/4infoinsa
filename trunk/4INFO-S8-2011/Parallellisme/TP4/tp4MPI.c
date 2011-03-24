#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

double f(double x);
int main (int argc, char *argv[])
{
	if(argc < 2){
		printf("Usage : tp4 n");
		return 1;
	}

	int n = atoi(argv[1]);
	
	if(n <= 0){
		printf("n doit être supérieur à 0\n");
		return 1;
	}

	int i;      /* numero du processus courant */
	int p;      /* nombre total de processus */

	int recu; /* valeur recue par le processus courant */
	MPI_Status stat; /* pour l'initialisation */

	MPI_Init(&argc, &argv); 
	MPI_Comm_rank(MPI_COMM_WORLD, &i); // Rang du processus
	MPI_Comm_size(MPI_COMM_WORLD, &p); // Nombre de processus
	
	double tpsDebut;
	if(i == 0)
		tpsDebut = MPI_Wtime();
	
	int tailleCalcul = n/p;
	
	//Envoie/Réception taille des calculs => [Charles/Luc] NE SERT A RIEN !!!!
	MPI_Bcast(&tailleCalcul, 1, MPI_INT, 0, MPI_COMM_WORLD);
		
		
//Calcul
	double somme = 0;
	int cpt;
	for(cpt = i*tailleCalcul; cpt <= (i+1)*tailleCalcul; cpt++){
		somme += f((cpt)/(n+0.0)) + f((cpt+1)/(n+0.0));
	}
		
	double * buffer;
	if(i == 0)
		buffer = malloc(sizeof(double)*p);

	MPI_Gather(&somme, 1, MPI_DOUBLE, buffer, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if(i == 0){
		for(cpt = 1; cpt < p; cpt++){
			somme += buffer[cpt];
		}
		
		double pi = somme/(2.0*n);
		printf("PI = %f\n", pi);
		
		double tempsTotal = MPI_Wtime() - tpsDebut;
		printf("Temps total : %f\n", tempsTotal);
		
		free(buffer);
	}
		
	MPI_Finalize();
	return 0;
}

double f(double x){
	return (4/(1+x*x+0.0));
}
