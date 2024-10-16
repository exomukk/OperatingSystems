#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5  // Size of the circular buffer

int buffer[BUFFER_SIZE];  // Circular buffer
int count = 0;            // Number of items in the buffer
int in = 0;               // Index for the producer
int out = 0;              // Index for the consumer

pthread_mutex_t mutex;        // Mutex for shared data protection
pthread_cond_t buffer_not_full;  // Condition variable for "not full"
pthread_cond_t buffer_not_empty; // Condition variable for "not empty"

void *producer(void *param) {
    int item;
    while (1) {
        item = rand() % 100;  // Produce an item (random number)
        
        // Acquire lock and wait if buffer is full
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&buffer_not_full, &mutex);
        }
        
        // Produce item and place it in the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Producer produced %d\n", item);
        
        // Signal that the buffer is not empty
        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&mutex);
        
        sleep(1);  // Simulate time taken to produce an item
    }
}

void *consumer(void *param) {
    int item;
    while (1) {
        // Acquire lock and wait if buffer is empty
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&buffer_not_empty, &mutex);
        }
        
        // Consume the item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("Consumer consumed %d\n", item);
        
        // Signal that the buffer is not full
        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&mutex);
        
        sleep(1);  // Simulate time taken to consume an item
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&buffer_not_full, NULL);
    pthread_cond_init(&buffer_not_empty, NULL);
    
    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // Wait for the threads to finish (they won't, so this loops indefinitely)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    // Cleanup
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&buffer_not_full);
    pthread_cond_destroy(&buffer_not_empty);
    
    return 0;
}
