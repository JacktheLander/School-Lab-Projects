// Name: Jack Landers
// Date: 10/2/25
// Title: Lab2 - Forks, Threads, and processes
// Description: Creating parallelism with multithreading and multiprocessing
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	int i, j;
	printf("\n Before Forking\n");
	for(i=0; i < 2; i++){
		pid = fork();
		if (pid == -1) {
			fprintf(stderr, "can't fork, error %d\n", errno);
		}
		if (pid == 0){
			printf("Child %d - Parent PID %d, PID: %d\n", i+1, getppid(), getpid());
			for(j=0; j < 2; j++){
				pid_t lowerpid = fork();
				if(lowerpid == 0){
					printf("Child %d of %d - Parent PID: %d, PID: %d\n", j+1, i+1, getppid(), getpid());
					exit(0);
				}
				if(lowerpid == -1){
					fprintf(stderr, "can't fork, error %d\n", errno);
				}
				else{
					//printf("\nChild %d waiting for children\n", i+1);
					wait(0);
					//printf("\nReturned to child %d with ppid: %d and pid: %d\n", i+1, getppid(), getpid());
				}
			}
			exit(0);
		}
		else{
			printf("\nRoot ID: %d\n", getpid());
			wait(0);
			printf("\nReturned to root\n");
		}
	}
	return 0;
}


