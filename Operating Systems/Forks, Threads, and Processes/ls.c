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
	pid = fork();

	if(pid == 0){
		execlp("/bin/ls", "ls", NULL);
	}
	else{
		wait(NULL);
		printf("Child Complete");
		exit(0);
	}
}
