#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


main(){
int nb = 0;
while(nb != 10){
	nb++;
	pid_t pidFils= fork();
	if(pidFils == 0){
		printf("Je suis le fils numéro : %d\n ", nb);
		nb = 10;
	}else
	{
		printf("Je suis ton père, mon PID est : %d\n", getpid());
		
		sleep(1);
	}

}

}

