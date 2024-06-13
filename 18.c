#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item;
    while (1) {
        // Produce an item
        item = rand() % 100;
        sleep(1); // Simulate time taken to produce an item

        // Wait for empty slot and lock the buffer
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        // Unlock the buffer and signal that buffer is not empty
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        // Wait for an item in the buffer and lock the buffer
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // Remove the item from the buffer
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        // Unlock the buffer and signal that buffer is not full
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(1); // Simulate time taken to consume an item
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (they won't in this infinite loop)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
