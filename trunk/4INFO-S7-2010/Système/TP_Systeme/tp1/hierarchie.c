#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define NIVEAUX 3

main(){
	
	int i = NIVEAUX;
	
	pid_t ancetres[NIVEAUX];
	
	printf("[i = %d] 		je suis le proc numero %d, mon père est le numéro %d\n", i, getpid(), getppid());	
	pid_t pidFils;
	do{
		ancetres[NIVEAUX-i] = getpid();
		
		i--;
		pidFils = fork();
		if(pidFils){
			pidFils = fork();
		}
		
		if(!pidFils){
			printf("[i = %d] 		je suis le proc numero %d, mon père est le numéro %d\n", i, getpid(), getppid());
		}
		
		
		
	}while(!pidFils && i > 0);
	
	//Pour éviter d'avoir des processus orphelins
	sleep(2);
	
	if(i == 0){
		int j;
		for(j = NIVEAUX-1; j >= 0; j--){
			printf("ancetre numero %d : %d\n", (NIVEAUX-j), ancetres[j]);
		}
	}
}
