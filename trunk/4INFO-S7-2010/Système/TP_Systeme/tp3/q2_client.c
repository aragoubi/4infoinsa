#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>


int recu = 0;

void handlerClient(int sig){
	printf("Entrée dans le handler\n");
	if(sig == SIGUSR1){
		printf("SIGUSR1 reçu\n");
		recu = 1;
	}
}


int main(int argc, char** argv){
	int fds;
	int fd;
	int nb;
	char buffer[32];
	char pidString[8];
	struct sigaction action;
 	action.sa_handler = handlerClient;
        sigaction(SIGUSR1,&action,NULL);

	if(mkfifo("/tmp/tubeClient", 0666) != 0){
		perror("mkfifo");
		exit(1);
	}
	printf("tubeClient créé\n");
	if((fds = open("/tmp/tubeServeur", O_RDWR)) == -1){
		perror("openServeur");	
		exit(1);
	}
	printf("pipe du serveur ouvert\n");
	if((fd = open("/tmp/tubeClient", O_RDWR)) == -1){
		perror("openClient");	
		exit(1);
	}
	printf("pipe du client ouvert\n");
	
	//demande de service1
	kill(atoi(argv[1]),SIGUSR1);
	sprintf(pidString, "%d\0", getpid());
	write(fds, pidString, sizeof(pidString));
	printf("serveur notifié\n");
	while(!recu);
	printf("accusé de réception reçu\n");
	write(fds, "/tmp/tubeClient", 17);
	printf("nom du tube client envoyé au serveur\n");
	nb = read(fd, buffer, 32);
	printf("réponse du serveur lue\n");
	if(nb > 0){
		printf("|%s|\n", buffer);
	}
	
	recu = 0;
	//demande de service2
	kill(atoi(argv[1]),SIGUSR2);
	sprintf(pidString, "%d\0", getpid());
	write(fds, pidString, sizeof(pidString));
	printf("serveur notifié\n");
	while(!recu);
	printf("accusé de réception reçu\n");
	write(fds, "/tmp/tubeClient", 17);
	printf("nom du tube client envoyé au serveur\n");
	nb = read(fd, buffer, 32);
	printf("réponse du serveur lue\n");
	if(nb > 0){
		printf("|%s|\n", buffer);
	}
	
	close(fd);
	close(fds);
	unlink("/tmp/tubeClient");
	return 0;
}
