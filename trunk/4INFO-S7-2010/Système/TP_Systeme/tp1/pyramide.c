#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


main(){
int nbniv = 0;
int anc[4];
int i = 0;
int max = 1;
for(i;(i<max)&&(nbniv<3);i++){
	//printf("Je suis  %d je suis au niveau %d\n", getpid(),nbniv);
	pid_t fils1 = fork();
	pid_t fils2 = -1;
	if(fils1 !=0){
		fils2 = fork();
	}
	
	
	if((fils1 == 0) || (fils2 ==0))
	{
		anc[nbniv]=getppid();
	
		nbniv++;
		printf("Je suis  %d je suis au niveau %d Mon père est %d\n", getpid(),nbniv,getppid());
		i--;
		
	}

}	
sleep(4);

if(nbniv == 3){
int j = 0;
		for(j;j<nbniv;j++){
			printf("Mon pid est : %d mon ancetre de Niveau %d : %d \n", getpid(),j,anc[j]);
		}


}
			
}

















