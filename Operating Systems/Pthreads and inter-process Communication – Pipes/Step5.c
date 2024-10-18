#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
	char buffer[30];
	pid_t pid;
    	int fds[2];
	int *counter;

	if(pipe(fds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	memset(buffer, 0, 30);

	pid = fork();
	if (pid == -1) {
        	perror("fork");
        	exit(EXIT_FAILURE);
    	}
	if (pid>0){
		int i = 0;
		char letter = 'a';

		//Producer
		printf("\nProducer - Writes to buffer\n");
		close(fds[0]);
		while(*counter < 30){
			write(fds[1], &letter, 1);
			printf("\n%c", letter);
			i++;
			letter = 'a' + (i%26);
			(*counter)++;
		        
			while(*counter >= 30) {
                 	   printf("\nProducer waiting for buffer to empty...\n");
                	}
		}
		close(fds[1]);
	}
	else{
		//Consumer
		printf("\n\tConsumer - Reads from buffer\n");
		close(fds[1]);
		while(read(fds[0], buffer, 1) == 1){
			printf("\n\t%c", buffer[0]);
			(*counter)--;
			while(*counter == 0) {
             			printf("\n\tConsumer emptied the buffer, allowing producer to write again...\n");
        	        }
		}
		close(fds[0]);

	}
	printf("\n\nError Looping --- Process Ended\n");
   	munmap(counter, sizeof(int));
    	return 0;
}

