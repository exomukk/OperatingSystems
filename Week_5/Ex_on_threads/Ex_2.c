#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define NTHREADS 2
#define SIZE 4

int A[SIZE][SIZE] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
int B[SIZE][SIZE] = {{16,15,14,13}, {12,11,10,9}, {8,7,6,5}, {4,3,2,1}};
int C[SIZE][SIZE] // result matrix

typedef struct {
    int start_col;
    int end_col;
} ThreadData;

void *matrix_multiply(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int start_col = data->start_col;
    int end_col = data->end_col;

    for (int i = 0; i < SIZE; i++) {
        for (int j = start_col; j < end_col; j++) {
            C[i][j] = 0; // Initialize element
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main(int agrc, char *argv[]) {
    int i, tids[NTHREADS];
    pthread_t threads[NTHREADS];
    pthread_attr_t attr;

    // Pthread setup: initialize mutex and explicitly create threads in a 
    // join able state (for portability). Pass each thread its loop offset

    pthread_mutex_init(&sum_mutex, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    printf("Number of threads is %d\n", NTHREADS);

    for (i = 0; i < NTHREADS; i++) {
        tids[i] = i;
        pthread_create(&threads[i], &attr, do_work, (void *) &tids[i]);
    }

    // Wait all thread to complete them print global sum
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Sum = %e \n", sum);

    sum = 0.0;
    for (i = 0; i < ARRAYSIZE; i++) {
        a[i] = i * 1.0;
        sum = sum + a[i];
    }

    printf("Verification from the main thread: %e\n", sum);

    // Clean up the code and exit
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&sum_mutex);
    pthread_exit(NULL);
}