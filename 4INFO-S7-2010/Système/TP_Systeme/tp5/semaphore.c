/*
int semget(key_t key, int nsems, int semflg);
L’appel  système  semget()  renvoie l’identifiant de l’ensemble de sémaphores associé à la valeur de clé key. Un nouvel ensemble contenant nsems sémaphores
est créé si key a la valeur IPC_PRIVATE ou si aucun ensemble n’est associé à key, et si l’option IPC_CREAT est présente dans semflg.

int semctl(int semid, int semnum, int cmd, ...);
Cette fonction effectue l’opération de contrôle indiquée par cmd sur l’ensemble de sémaphores (ou sur le semnum-ième sémaphore de l’ensemble) identifié par
semid. (Les sémaphores sont numérotés à partir de zéro.)

int semop(int semid, struct sembuf *sops, unsigned nsops);
La  fonction  semop()  effectue  des  opérations sur les membres de l’ensemble de sémaphores identifié par semid. Chacun des nsops éléments dans le tableau
       pointé par sops indique une opération à effectuer sur un sémaphore en utilisant une structure struct sembuf contenant les membres suivants :
           unsigned short sem_num;   Numéro du sémaphore        
           short          sem_op;    Opération sur le sémaphore 
           short          sem_flg;   Options pour l’opération   

*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>


int init(int key, int i){
	int sem_id = semget(key, 1, IPC_CREAT|0666);
         union semun {
               int              val;    /* Valeur pour SETVAL */
               struct semid_ds *buf;    /* Tampon pour IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Tableau pour GETALL, SETALL */
               struct seminfo  *__buf;  /* Tampon pour IPC_INFO
                                           (spécifique à Linux) */
           } sem_val;
	sem_val.val = i;
	semctl(sem_id, 0, SETVAL, sem_val);
	return sem_id;
}

int get_sem_id(int key){
	int sem_id = semget(key, 1, 0);
	return sem_id;
}


void P(int sem_id){
	struct sembuf operation;
	operation.sem_num = 0;
	operation.sem_op = -1;
	operation.sem_flg = 0;
	semop(sem_id, &operation, 1);
}

void V(int sem_id){
	struct sembuf operation;
	operation.sem_num = 0;
	operation.sem_op = 1;
	operation.sem_flg = 0;
	semop(sem_id, &operation, 1);
}

/* main de la question 2

int main(int argc, char** argv){
	printf("argv1=|%s|\n", argv[1]);
	if(strcmp(argv[1],"create") == 0){ //on crée le sémaphore
		int s = init(42, 1);
		printf("Sémaphore créé. sem_id=%d\n", s);
	} else if (strcmp(argv[1],"delete") == 0){ //on supprime le sémaphore
		int s = get_sem_id(42);
		printf("Suppression du sémaphore. sem_id=%d\n", s);
		semctl(s, 0, IPC_RMID);
	} else { //on affiche le message
		int s = get_sem_id(42);
		printf("Affichage publicitaire. sem_id=%d\n", s);
		while(1){
			P(s);
			printf("--------Debut du message publicitaire--------\n");
			printf("%s\n", argv[1]);
			sleep(5);
			printf("--------Fin du message publicitaire--------\n\n");
			V(s);
		}
	}
	return 0;
}

*/
/*
#define SIZE 16

void tri_fusion(int* t, int n){

}

void fusionner(int* t1, int n1, int* t2, int n2){

}

int main(){
	int shid = shmget(IPC_PRIVATE, SIZE*sizeof(int), IPC_CREAT|0666); //créer une zone de mémoire partagée
	int* array; 
	array = shmat(shid, NULL, 0); //lier la zone de mémoire à une variable
	int i;
	srand(time(NULL));
	for(i = 0; i < SIZE; i++){
		array[i] = (100*rand())/RAND_MAX;
		printf("|%d", array[i]);
	}
	
//	if(

	return 0;
}
*/


