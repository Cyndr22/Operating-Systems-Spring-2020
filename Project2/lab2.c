/*			Lab 2 Partial Example			*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	char *inPath, *outPath, *argv[20], buf[80], n, *p;
	int m, status, inword, continu, count, numPipes, inFlag, outFlag;
	int args[20], lPipe[2], rPipe[2] = {0};

	while(1) {
		inword = 0;
		p = buf;
		m = 0;
		continu = 0;
		count = 0;
		numPipes = 0;
		inFlag, outFlag = 0;

		printf("\nshhh> ");

		while((n = getchar()) != '\n' || continu) { // command parsing
			if(n ==  ' ') { 
				if(inword) {
					inword = 0;
					*p++ = 0;
				} 
			}
			else if(n == '\n') 
				continu = 0;
			else if(n == '\\' && !inword) 
				continu = 1;
			else {
				if(!inword) {
					inword = 1;
					argv[m++] = p;
					*p++ = n;
				}
				else 
				*p++ = n;
			}
		}	

		*p++ = 0;
		argv[m] = 0;

		if(strcmp(argv[0],"exit") == 0) 
			exit(0);

		// redirection request handler
		while(argv[count] != 0) {
			if(strcmp(argv[count], "|") == 0) {
				argv[count] == 0;
				args[numPipes + 1] = count + 1;
				++numPipes;
			} else if(strcmp(argv[count], "<") == 0) {
				inPath = strdup(argv[count + 1]);
				argv[count] = 0;
				inFlag = 1;
			} else if(strcmp(argv[count], ">") == 0) {
				outPath = strdup(argv[count + 1]);
				argv[count] = 0;
				outFlag = 1;
			} else {
				args[count] = count;
			}
			++count;
		}
		
		// command execution
		for(int i = 0; i < numPipes; ++i) { 
			if(numPipes > 0 && i != numPipes) {
				pipe(rPipe);
			}
			
			pid_t pid = fork();
			
			if(pid < 0) {
				execvp(argv[0], argv);
				printf("failed to fork");
				exit(1);
			} 
			
			else if(pid == 0) { //children
				if((i == 0) && (inFlag == 1)) { // input redirection management
					int inFile = open(inPath, O_RDONLY, 0400);
					if(inFile == -1) {
						printf("failed to open input");
						exit(1);
					}
					
					close(1);
					dup(inFile);
					close(inFile);
				} 
				
				if((i == numPipes) && (outFlag == 1)) { // output redirection management
					int outFile = creat(outPath, 0700);
					if(outFile < 0) {
						printf("failed to open output");
						exit(1);
					}
					
					close(1);
					dup(outFile);
					close(outFile);
				}
				
				if(numPipes > 0) {
					if(i == 0) { // first child
						close(1);
						dup(rPipe[1]);
						close(rPipe[1]);
						close(rPipe[0]);
					} else if(i < numPipes) { // intermediate child
						close(0);
						dup(lPipe[0]);
						close(lPipe[0]);
						close(lPipe[1]);
						
						close(1);
						dup(rPipe[1]);
						close(rPipe[1]);
						close(rPipe[0]);
					} else { // final child
						close(0);
						dup(lPipe[0]);
						close(lPipe[0]);
						close(lPipe[1]);
					}
				}
				
				execvp(argv[args[i]], &argv[args[i]]);
				perror("failed to execute command");
				exit(2);
			} 
			
			else { //parent
				if(i > 0) {
					close(lPipe[0]);
					close(lPipe[1]);
				}
				
				lPipe[0] = rPipe[0];
				lPipe[1] = rPipe[1];
				
				wait(&status);
			}
		}
		
		for(int i = 0; i < 20; ++i) { //clear arrays
			argv[i] = 0;
			args[i] = 0;
		}
	}
	
	return 0;
}

