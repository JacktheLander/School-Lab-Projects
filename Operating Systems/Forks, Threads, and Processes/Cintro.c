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
	int i, n = atoi(argv[1]);
	printf("\n Before Forking\n");
	pid = fork();
	if (pid == -1) {
		fprintf(stderr, "can't fork, error %d\n", errno);
	}
	if (pid){
		for(i=0;i<100;i++){
			printf("\t \t \t Parent process %d \n", i);
			usleep(n);
		}
	}
	else{
		for(i=0;i<100;i++){
			printf("Child process %d\n", i);
			usleep(n);
		}
	}
	return 0;
}


