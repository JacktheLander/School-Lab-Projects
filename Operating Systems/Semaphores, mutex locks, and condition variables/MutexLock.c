#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
pthread_mutex_t lock;
pthread_cond_t cond_empty, cond_full;
int count = 0;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;
        printf("Producer produced item %d\n", item);

        pthread_mutex_lock(&lock);

        // Wait if buffer full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_empty, &lock);
        }

        // Add item
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == -1) {
                buffer[i] = item;
                count++;
                break;
            }
        }

        pthread_cond_signal(&cond_full); // Signal new item
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    while (1) {
        pthread_mutex_lock(&lock);

        // Wait if buffer is empty
        while (count == 0) {
            pthread_cond_wait(&cond_full, &lock);
        }

        // Remove item
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] != -1) {
                item = buffer[i];
                buffer[i] = -1;
                count--;
                break;
            }
        }

        pthread_cond_signal(&cond_empty); // Signal empty slot
        pthread_mutex_unlock(&lock);

        printf("Consumer consumed item %d\n", item);
    }
    return NULL;
}

int main() {
    // Initialize buffer to -1 for empty
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond_empty, NULL);
    pthread_cond_init(&cond_full, NULL);

    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_empty);
    pthread_cond_destroy(&cond_full);

    return 0;
}

