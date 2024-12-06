#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    const char *src_file;
    int thread_id;
    int buffer_size;
} thread_args;

void *copy(void *args){
	thread_args *thread_data = (thread_args *)args;
	char *buffer = (char *)malloc(thread_data->buffer_size);
	char new_file[256];
	FILE *fp, *fp_write;

    	snprintf(new_file, sizeof(new_file), "%s_copy_%d.out", thread_data->src_file, thread_data->thread_id);

    	fp = fopen(thread_data->src_file, "rb");
	fp_write = fopen(new_file, "wb");
	
	size_t bytes_read;
	while ((bytes_read = fread(buffer, sizeof(buffer), 1, fp)) > 0){
                fwrite(buffer, 1, bytes_read, fp_write);
        }
        fclose(fp);
        fclose(fp_write);
	free(buffer);
    	free(thread_data);
	pthread_exit(NULL);
}

void main(int argc, char *argv[]){
	int num_threads = atoi(argv[3]);

	pthread_t *threads = malloc(num_threads * sizeof(pthread_t));

    	for (int i = 0; i < num_threads; i++) {
        	thread_args *thread = malloc(sizeof(thread_args));

        	thread->src_file = argv[1];
        	thread->thread_id = i + 1;
		thread->buffer_size = atoi(argv[2]);

        	if (pthread_create(&threads[i], NULL, copy, thread) != 0) {
        	    perror("Error creating thread");
        	    free(thread);
        	    free(threads);
        	    return;
        	}
   	 }

    	for (int i = 0; i < num_threads; i++) {
        	pthread_join(threads[i], NULL);
    	}

    	free(threads);	
	return;
}
