#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define N 256
#define M 256
#define L 256
// N, M, L should all = 256 so they are large enough to exploit parallelism

int matrixA[N][M];
int matrixB[M][L];
int matrixC[N][L];

// Thread function to perform matrix multiplication
void* multiply_row(void* arg) {
    int i = *(int*)arg;  // Get the row index from argument

    for (int j = 0; j < L; j++) {
        int temp = 0;
        for (int k = 0; k < M; k++) {
            temp += matrixA[i][k] * matrixB[k][j];
        }
        matrixC[i][j] = temp;  // Stores result in matrixC
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    // Initialize matrixA with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrixA[i][j] = rand() % 10;
        }
    }

    // Initialize matrixB with random values
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < L; j++) {
            matrixB[i][j] = rand() % 10;
        }
    }

    // Thread array
    pthread_t threads[N];
    int row_indices[N];

    // Create N threads, one for each row of matrixA
    for (int i = 0; i < N; i++) {
        row_indices[i] = i;
        if (pthread_create(&threads[i], NULL, multiply_row, &row_indices[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print matrixC
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++) {
            printf("%d ", matrixC[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}

