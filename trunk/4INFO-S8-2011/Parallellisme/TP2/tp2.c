#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 12

pthread_mutex_t mutexLastTrame = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexEtats[N];

pthread_cond_t pourLire = PTHREAD_COND_INITIALIZER;
pthread_cond_t pourEcrire = PTHREAD_COND_INITIALIZER;

typedef enum {ECDL = 0, LOV, NL, ECE} Etat;

int lastTrame = -1;
int buf[N];
Etat etats[N];
int nbElements;

int ecrire(int v);
int debut_lire(int l);
int lire(int ind);
void fin_lire(int ind);


void* loop_Prod(void* nb){
	int* ptr = nb;
	int a = *ptr;
	
	int valeurAEcrire = 0;
	while(1){
		
		int indice = ecrire(valeurAEcrire);
		
		printf("[%d] buf[%d] = %d\n", a, indice, valeurAEcrire);
		
		sleep(1);
		valeurAEcrire++;
	}
}

void* loop_Cons(void* nb){
	int* ptr = nb;
	int a = *ptr;
	
	int indCons;
	while(1){
		printf("debut_lire\n");
		indCons = debut_lire(lastTrame);
		printf("indice lecture = %d\n", indCons);
		
		pthread_mutex_lock( &mutexLastTrame );
			lastTrame = lire(indCons);
		pthread_mutex_unlock( &mutexLastTrame );
		
		fin_lire(indCons);
		
		sleep(1);
	}
}

int ecrire(int v){
	int ind = 0;
	int min = -1;
	int i = 0;
	int trouve = 0;
	
	
	while(!trouve && i < N){
		pthread_mutex_lock( &mutexEtats[i] );
	
		if(etats[i] == LOV){
		
			if(min != -1)
				pthread_mutex_unlock( &mutexEtats[ind] );
		
			ind = i;
			trouve = 1;
		}
		else if(etats[i] == NL && (min == -1 || buf[i] < min)){
			
			if(min != -1)
				pthread_mutex_unlock( &mutexEtats[ind] );
				
			min = buf[i];
			ind = i;
		}
		else{
			pthread_mutex_unlock( &mutexEtats[i] );
		}
		
		i++;
	}
	
	etats[ind] = ECE;
	buf[ind] = v;
	etats[ind] = NL;
	pthread_mutex_unlock( &mutexEtats[ind] );
	pthread_cond_signal(&pourLire);
	
	return ind;
}

int debut_lire(int min){
	int res = 0;
	
	int i;
	int nouvelleValeur = 0;
	
	do{
		for(i = 0; i < N; i++){
			pthread_mutex_lock( &mutexEtats[i] );
		
			if(etats[i] == NL && (min == -1 || buf[i] < min)){
				if(min != -1)
					pthread_mutex_unlock( &mutexEtats[res] );
					
				min = buf[i];
				res = i;
				nouvelleValeur = 1;
			}
			else{
				pthread_mutex_unlock( &mutexEtats[i] );
			}
		}
		
		if(!nouvelleValeur){
			printf("aucune nouvelle valeur, dodo\n");
			pthread_cond_wait(&pourLire, NULL);
		}
			
	}while(!nouvelleValeur);
	
	return res;
}

int lire(int indice){
	etats[indice] = ECDL;
	int res = buf[indice];
	pthread_mutex_unlock( &mutexEtats[indice] );
	return res;
}

void fin_lire(int indice){
	pthread_mutex_lock( &mutexEtats[indice] );
		etats[indice] = LOV;
	pthread_mutex_unlock( &mutexEtats[indice] );
}

int main(int argc, char* argv[]){

	pthread_mutexattr_t attrMutex[N];	

	int i;
	for(i = 0; i < N; i++){
		etats[i] = LOV;
		
		pthread_mutexattr_init(&attrMutex[i]);
		pthread_mutex_init(&(mutexEtats[i]), &attrMutex[i]);

	}

	int thr_id;
	
	pthread_t p_thread[1000];
	
	int nbThread = 0;
	pthread_attr_t attr;
	int choix;
	
	
	do{
		printf("Faite votre choix :\n");
		printf("\t1. créer producteur\n");
		printf("\t2. créer consommateur\n");
		
		printf("\tVotre choix : ");
		scanf("%d", &choix);
		
		switch(choix){
			case 1:
				pthread_attr_init(&attr);
				thr_id = pthread_create(&(p_thread[nbThread]), &attr, loop_Prod, (void*) &nbThread);
				nbThread++;
				break;
				
			case 2:
				pthread_attr_init(&attr);
				thr_id = pthread_create(&(p_thread[nbThread]), &attr, loop_Cons, (void*) &nbThread);
				nbThread++;
				break;
			
			default:
				printf("Choix incorrect !\n");
				break;
		}
	}while(1);
}
