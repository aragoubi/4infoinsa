#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 12

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t pourLire = PTHREAD_COND_INITIALIZER;
pthread_cond_t pourEcrire = PTHREAD_COND_INITIALIZER;


void put(int);
int get();

int buf[N];
int indCons, indProd;
int nbElements;

void* loop_Prod(void* nb){
	int* ptr = nb;
	int a = *ptr;
	while(1){
		put(a);
		
		printf("[%d] production\t[nb elt = %d]\n", a, nbElements);
		
		sleep(1);
	}
}

void* loop_Cons(void* nb){
	int* ptr = nb;
	int a = *ptr;
	while(1){
		int n =  get();
		
		printf("[%d] lecture %d\t[nb elt = %d]\n", a, n, nbElements);
		
		sleep(1);
	}
}

void put(int v){
	pthread_mutex_lock( &mutex1 );
	
	while(nbElements == N)
		pthread_cond_wait(&pourEcrire, &mutex1);
	
	buf[indProd] = v;
	
	indProd = (indProd+1) % N;
	nbElements++;
	
	pthread_cond_signal(&pourLire);
	
	pthread_mutex_unlock( &mutex1 );
}

int get(){
	pthread_mutex_lock( &mutex2 );
	
	while(nbElements == 0){
		pthread_cond_wait(&pourLire, &mutex2);
	}
	
	int res = buf[indCons];
	
	indCons = (indCons+1) % N;
	nbElements--;
	
	pthread_cond_signal(&pourEcrire);
	
	pthread_mutex_unlock( &mutex2 );
	
	return res;
}

int main(int argc, char* argv[]){

	nbElements = 0;
	indCons = 0;
	indProd = 0;

	int thr_id;
	
	pthread_t p_thread[1000];
	
	int nbThread = 0;
	pthread_attr_t attr;
	int choix;
	
	
	do{
		printf("Faite votre choix :\n");
		printf("\t1. créer producteur\n");
		printf("\t2. créer consommateur\n");
		printf("\t3. visualiser état\n");
		
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
			
			case 3:
				printf("Nb threads : %d\n", nbThread);
				printf("Tampon : ");
				
				pthread_mutex_lock( &mutex1 );
				pthread_mutex_lock( &mutex2 );
				
				int i;
				for(i = 0; i < nbElements; i++){
					printf("buf[%d] = %d\n", (indCons+i)%N, buf[(indCons+i)%N]);
				}
				
				sleep(3);
				
				pthread_mutex_unlock( &mutex1 );
				pthread_mutex_unlock( &mutex2 );
				break;
			
			default:
				printf("Choix incorrect !\n");
				break;
		}
	}while(1);
}
