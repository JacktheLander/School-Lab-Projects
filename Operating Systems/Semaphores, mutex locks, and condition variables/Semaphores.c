#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t full, empty, lock;

void* producer(void* arg) {	// Producer thread
    int item;
    do{
        item = rand() % 100;
        printf("Producer produced item %d\n", item);

        sem_wait(&empty);  // Wait for empty slot
        sem_wait(&lock);   // Access buffer

        // Next empty slot is empty value -1
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == -1) {
                buffer[i] = item;
                break;
            }
        }

        sem_post(&lock);   // Release buffer
        sem_post(&full);   // Signal full slot
    }while(1);
    return NULL;
}

void* consumer(void* arg) {	// Consumer thread
    int item;
    do{
        sem_wait(&full);   // Wait for full slot
        sem_wait(&lock);   // Access buffer

        // Next filled slot set to -1
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] != -1) {
                item = buffer[i];
                buffer[i] = -1;
                break;
            }
        }

        sem_post(&lock);   // Release buffer
        sem_post(&empty);  // Signal empty slot

        printf("Consumer consumed item %d\n", item);
    }while(1);
    return NULL;
}

int main() {
    // Initialize buffer to -1 for empty
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }

    sem_init(&full, 0, 0);         // No items initially
    sem_init(&empty, 0, BUFFER_SIZE); // All slots empty
    sem_init(&lock, 0, 1);         // Mutex lock available

    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&lock);

    return 0;
}
