// Name: Jack Landers
// Date: 10/2/25
// Title: Lab2 - Forks, Threads, and processes
// Description: Creating parallelism with multithreading and multiprocessing
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

typedef struct{
	int id;
	int n;
} ThreadData;

void *count(void *arg) {
	ThreadData *data = (ThreadData *)arg;
    	int tid = data->id;
    	int n = data->n;
	for(int i=0;i<100;i++){
		printf("\nThread %d: %d\n", tid, i);
		usleep(n);
	}
	free(data);
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t thread1;
	pthread_t thread2;

	int n = atoi(argv[1]); 

	printf("\n Before Threading\n");

    	ThreadData *data1 = malloc(sizeof(ThreadData));
    	ThreadData *data2 = malloc(sizeof(ThreadData));

    	if (!data1 || !data2) {
      	 	perror("Failed to allocate memory");
       		return 1;
	}

    	data1->id = 1;
    	data1->n = n;

    	data2->id = 2;
    	data2->n = n;
	
	if (pthread_create(&thread1, NULL, count, (void *)data1) == 0){
		printf("\nThread 1 created\n");
	}

	if (pthread_create(&thread2, NULL, count, (void *)data2) == 0){
		printf("\nThread 2 created\n");
	}

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);	
	return 0;
}


