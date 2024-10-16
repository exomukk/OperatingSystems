#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define NTHREADS 8 // change this from 4 to 8
#define ARRAYSIZE 1000000
#define ITERATIONS ARRAYSIZE / NTHREADS

double sum = 0.0, a[ARRAYSIZE];
pthread_mutex_t sum_mutex;

void *do_work(void *tid) {
    int i, start, *mytid, end;
    double mysum = 0.0;
    pid_t tid2 = syscall(SYS_gettid);

    // Initialize my part of the global array and keep local sum
    mytid = (int *) tid;
    start = (*mytid * ITERATIONS);
    end = start + ITERATIONS;

    for (i = start; i < end; i++) {
        a[i] = i * 1.0;
        mysum = mysum + a[i];
    }

    printf("Thread %d with id %d completed iterations %d to %d, partial sum = %.2f, mysum = %.2f before locking sum = %.2f\n", *mytid, tid2, end - 1, mysum, mysum, sum);

    // Lock the mutex and update the global sum, then exit
    pthread_mutex_lock(&sum_mutex);

    sum = sum + mysum;

    printf("Thread %d after locking, sum = %.2f\n", *mytid, sum);
    pthread_mutex_unlock(&sum_mutex);

    sleep(10);
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

/* Differences before the lock and after the lock:
- Before the lock (mutex): Each thread prints its 'mytid', local sum 'mysum'
and the global 'sum' as it stands before entering the critical section. Since
multiple threads can be running in parallel, 'sum' might not include the contributions
from other threads yet.
- After the lock: Once inside the critical section (after acquiring the mutex lock),
each thread updates the global 'sum' and prints the new value. This updated 'sum'
now reflects the cumulative additions from other threads that have already completed
their work.

=> value of 'sum' before locking differs between threads due to race conditions.
After locking, the updates are synced, so 'sum' includes all previous contributions,
leading to the final correct total */