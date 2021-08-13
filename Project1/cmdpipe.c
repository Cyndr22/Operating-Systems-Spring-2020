#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MSGSIZE 512

int main(int argc, char *argv[])
{
	char inbuf[MSGSIZE];
	int p[2];
	pid_t pid;
	
	if(pipe(p) < -1) { //checks for a pipe failure
		perror("failed to pipe");
		exit(1);
	}
	
	switch(pid = fork()) {
		case -1: //fork failure
			perror("failed to fork");
			exit(2);
		case 0: //child pipe write
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			execvp(argv[0], argv);
			perror("failed to execl");
			return(EXIT_FAILURE);
		default: //parent pipe read
			sleep(2);
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			execvp(argv[0], argv);
			return(EXIT_FAILURE);
	}
	
	return(EXIT_FAILURE);
}