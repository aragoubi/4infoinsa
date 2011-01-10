#include <unistd.h>

int main(){
	
	int fp[2];
	pipe(fp);
	pid_t pid = fork();

	if(pid != 0){
		dup2(fp[1], STDOUT_FILENO);
		close(fp[0]);
		execlp("/usr/bin/who", "who", NULL);
	} else {
		dup2(fp[0], STDIN_FILENO);
		close(fp[1]);
		execlp("/bin/grep", "grep", "tty7", NULL);
	}
			

	return 0;
}
