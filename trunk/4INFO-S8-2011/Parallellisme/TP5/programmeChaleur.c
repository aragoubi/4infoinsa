#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LARGEUR 6
#define HAUTEUR 6

#define K 1
#define SEUIL 10
#define MAX 300

void afficherMatrice(double M[LARGEUR+2][HAUTEUR+2]);

int main(int argc, char ** argv){

	double delta;
	int cptIteration = 0;
	
	double T[LARGEUR+2][HAUTEUR+2], T1[LARGEUR+2][HAUTEUR+2];
	
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
		
		int i, j;
		for(i = 1; i <= LARGEUR; i++){
			for(j = 1; j <= HAUTEUR; j++){
				T1[i][j] = (T[i][j+1] + T[i][j-1] + T[i+1][j] + T[i-1][j] + T[i][j]) / 5;
				delta = delta + abs(T1[i][j] - T[i][j]);
				
				
				int cptL;
				int cptC;
				for(cptL = 0; cptL <= LARGEUR+1; cptL++){
					for(cptC = 0; cptC <= HAUTEUR+1; cptC++){
						T[cptL][cptC] = T1[cptL][cptC];
					}
				}
			}
		}
		
		if( (cptIteration % K) == 0){
			afficherMatrice(T);
			printf("Delta = %f\n", delta);
		}
		
		cptIteration++;
	}
}

void afficherMatrice(double M[LARGEUR+2][HAUTEUR+2]){
	int i, j;
	for(i = 0; i < LARGEUR+2; i++){
		for(j = 0; j < HAUTEUR+2; j++){
			printf("%2.2f\t", M[i][j]);
		}
		printf("\n");
	}
	
	printf("\n\t--------------\n");
}
