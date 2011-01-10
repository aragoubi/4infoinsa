#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


#include "semaphore.h"

#define SIZE 5
#define NB_PROD 4
#define NB_CONSO 2

enum flags { VIDE, PLEIN, EN_COURS };
enum roles { PROD, CONSO, PRINC };

struct sigaction action;
int fin = 0;

void handlerTerminate(int sig){
	fin = 1;
}


int main(){
	//Creation de la memoire partagee
	int shid_data = shmget(IPC_PRIVATE, SIZE*sizeof(int), IPC_CREAT|0666);
	int shid_flags = shmget(IPC_PRIVATE, SIZE*sizeof(int), IPC_CREAT|0666);
	int* data;
	int* flags; 
	data = shmat(shid_data, NULL, 0); //donnees partagees
	flags = shmat(shid_flags, NULL, 0); //flags d'accessibilite des donnees partagees

	//Creation des semaphores
	int sem_prod = init(42, SIZE);
	int sem_conso = init(43, 0);
	int sem_mutex_prod = init(44, 1);
	int sem_mutex_conso = init(45, 1);

	//Gestion du signal de fin
	action.sa_handler = handlerTerminate;
	sigaction(SIGUSR1,&action,NULL);

	//Creation des processus fils
	int role = PRINC;
	int nb;
	int tab_pid[NB_PROD+NB_CONSO];
	int i_pid = 0;
	for(nb = 0; nb < NB_PROD && role == PRINC; nb++){ //creation des producteurs
		pid_t pid_fils = fork();
		tab_pid[i_pid] = pid_fils;
		i_pid++;
		if(pid_fils == 0){
			role = PROD;
		}
	}
	for(nb = 0; nb < NB_CONSO && role == PRINC; nb++){ //creation des consommateurs
		pid_t pid_fils = fork();
		tab_pid[i_pid] = pid_fils;
		i_pid++;
		if(pid_fils == 0){
			role = CONSO;
		}
	}
	
	//code du producteur
	while(role == PROD){ 
		P(sem_prod);
		int i;
		int trouve = 0;
		for(i = 0; i < SIZE && !trouve; i++){
			if(flags[i] == VIDE){
				P(sem_mutex_prod);
				flags[i] = EN_COURS;
				trouve = 1;
				V(sem_mutex_prod);
			}
		}
		data[i] = getpid();
		P(sem_mutex_prod);
		flags[i] = PLEIN;
		V(sem_mutex_prod);
		V(sem_conso);
	}

	//code du consommateur
	while(role == CONSO){ 
		P(sem_conso);
		int i;
		int trouve = 0;
		for(i = 0; i < SIZE && !trouve; i++){
			if(flags[i] == PLEIN){
				P(sem_mutex_conso);
				flags[i] = EN_COURS;
				trouve = 1;
				V(sem_mutex_conso);
			}
		}
		printf("Valeur lue par %d : %d\n", getpid(), data[i]);
		P(sem_mutex_conso);
		flags[i] = VIDE;
		V(sem_mutex_conso);		
		V(sem_prod);
	}
	
	//code du pere de tous les producteurs et consommateurs
	while(role == PRINC && !fin){ 
		sleep(1);		
	}
	int i;			
	for(i = 0; i < i_pid; i++){
		kill(tab_pid[i], SIGKILL);
	}
	
	//Nettoyage des semaphores et de la memoire partagee
	semctl(sem_prod, 0, IPC_RMID);
	semctl(sem_conso, 0, IPC_RMID);
	semctl(sem_mutex_prod, 0, IPC_RMID);
	semctl(sem_mutex_conso, 0, IPC_RMID);
	shmctl(shid_data, IPC_RMID, NULL);
	shmctl(shid_flags, IPC_RMID, NULL);

	return 0;
}
