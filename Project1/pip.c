#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
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
			execl("./pre", "pre", (char *)0);
			perror("failed to execl");
			break;
		default: //parent pipe read
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			execl("./sort", "sort", (char *)0);
			return(EXIT_FAILURE);
	}
	
	return(-1);
}