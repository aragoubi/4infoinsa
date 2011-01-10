#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>


int fd;
int fdc;
char buffer[32];

void handlerService(int sig){
	printf("Entrée dans le handler\n");
	int pid = -1;
	int nb = -1;
	if(sig == SIGUSR1){
		printf("Demande de service1 reçue\n");
		nb = read(fd, buffer, 32);
		printf("Message reçu = |%s|\n", buffer);
		if (nb > 0){
			pid = atoi(buffer);
			printf("pid du client = %d\n", pid);
			service1(pid);
		}
	} else if(sig == SIGUSR2) {
		nb = read(fd, buffer, 32);
		if (nb > 0){
			pid = atoi(buffer);
			service2(pid);
		}
	}
}


int service1(int pid){
	printf("Entrée dans service1\n");
	kill(pid, SIGUSR1); //accusé de réception
	printf("Accusé de réception envoyé\n");	
	int nb = -1;
	nb = read(fd, buffer, 32);
	printf("Message lu = |%s|\n", buffer);
	if(nb > 0){
		fdc = open(buffer, O_RDWR);
		printf("Pipe du client ouvert\n");		
		write(fdc, "Service1\n", 10);
		printf("Ecriture dans le pipe du client finie\n");
		close(fdc);
	}
}

int service2(int pid){
	printf("Entrée dans service2\n");
	kill(pid, SIGUSR1); //accusé de réception
	printf("Accusé de réception envoyé\n");	
	int nb = -1;
	nb = read(fd, buffer, 32);
	printf("Message lu = |%s|\n", buffer);
	if(nb > 0){
		fdc = open(buffer, O_RDWR);
		printf("Pipe du client ouvert\n");		
		write(fdc, "Service2\n", 10);
		printf("Ecriture dans le pipe du client finie\n");
		close(fdc);
	}
}

int main(){

	struct sigaction action;
        action.sa_handler = handlerService;
        sigaction(SIGUSR1,&action,NULL);
        sigaction(SIGUSR2,&action,NULL);
	
	printf("%d\n", getpid());
	if(mkfifo("/tmp/tubeServeur", 0666) != 0){
		printf("dans le if de mkfifo");	
		perror("mkfifo");
		exit(1);
	}
	printf("tubeServeur créé\n");
	if((fd = open("/tmp/tubeServeur", O_RDWR)) == -1){
		printf("dans le if de open");	
		perror("open");	
		exit(1);
	}
	printf("tubeServeur ouvert\n");	

	while(1){
//		sleep(1);
	}
	printf("Sortie de boucle infinie\n");
	close(fd);
	unlink("/tmp/tubeServeur");
	return 0;
}
