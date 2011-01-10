#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
struct sigaction action;



pid_t pid;
int cpt;
int nbsig;
/*
void handlerfils(int sig){
	int i = 0;
	for(i;i<10;i++){
		printf("b\n");
	}
	kill(getpid(),SIGKILL);
}

void handler_question3(int sig){
	printf("J'en suis à %d\n", cpt);
}
*/
/*
void handler_question4(int sig){
	if(sig == SIGUSR1){
		cpt++;
		printf("Signal n°%d\n",cpt);
		kill(getppid(),SIGUSR2);
	}else if(sig==SIGUSR2) {
		if(nbsig>0){
			kill(pid,SIGUSR1);
			nbsig--;
		}else{ 
			//kill(getpid(),SIGKILL); 
		}
	}

}
*/
pid_t tabpid[10];
void handler_question6(int sig){
	int i = 0;	
	for(i;i<10;i++){
		kill(tabpid[i],SIGINT);
	}

}
int main() {
	action.sa_handler = handler_question6;
	sigaction(SIGUSR1,&action,NULL);
	int i = 0;
	pid_t temp; 
	for(i;i<10;i++){
		temp = fork();
		if(temp != 0){tabpid[i] = temp; }else{i=10;}
	}
	if(temp != 0 ){
		printf("PID PAPA : %d\n",getpid());
		int j = 0;
		for( j;j<10;j++){
			wait(tabpid[j]);
		}
		printf("Tout mes fils sont morts\n");
	}else{
		while(1){}
	}
}
/* Question 4 & 5
	nbsig = 500000;
	cpt = 0;
	action.sa_handler = handler_question4;
	sigaction(SIGUSR1,&action,NULL);
	sigaction(SIGUSR2,&action,NULL);
	pid = fork();
	if(pid != 0){
		kill(pid,SIGUSR1);
		while(1){}
		
	}else{
		
		while(1){}
	}

}

 QUESTION 3
	cpt = 0;
	action.sa_handler = handler_question3;
	sigaction(SIGUSR1,&action,NULL);
	printf("Mon pid est %d\n",getpid());
	while(1){
		sleep(1);
		cpt++;
	}
	




_____ QUESTION 1 & 2 
	action.sa_handler = handlerfils;
	sigaction(SIGUSR1,&action,NULL);
	pid_t pid = fork();
	
	if(pid != 0){
		int i = 0;
		for(i;i<10;i++){
			printf("a\n");
		}
		kill(pid,SIGUSR1);
		wait(pid);
		printf("Je suis %d, mon fils est mort, du coup je meurs aussi\n", getpid());
		
	}else{
		while(1){}
	}
*/




