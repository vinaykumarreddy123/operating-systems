#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2
#define BUFFER_SIZE 5

int buffer = 0; // Shared buffer

sem_t mutex, write_mutex, read_count_sem;

int read_count = 0; // Number of readers reading the buffer

void *writer(void *arg) {
    int writer_id = *(int *)arg;
    while (1) {
        // Writer is writing
        sleep(1); // Simulate writing time
        sem_wait(&write_mutex); // Acquire write lock

        // Writing to buffer
        buffer++;
        printf("Writer %d wrote: %d\n", writer_id, buffer);

        sem_post(&write_mutex); // Release write lock
    }
    pthread_exit(NULL);
}

void *reader(void *arg) {
    int reader_id = *(int *)arg;
    while (1) {
        sem_wait(&mutex); // Acquire mutex to update read_count
        read_count++;
        if (read_count == 1) {
            sem_wait(&write_mutex); // Acquire write lock if first reader
        }
        sem_post(&mutex); // Release mutex

        // Reader is reading
        printf("Reader %d read: %d\n", reader_id, buffer);
        sleep(1); // Simulate reading time

        sem_wait(&mutex); // Acquire mutex to update read_count
        read_count--;
        if (read_count == 0) {
            sem_post(&write_mutex); // Release write lock if last reader
        }
        sem_post(&mutex); // Release mutex
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    int i, rc;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);
    sem_init(&read_count_sem, 0, 1);

    // Create reader threads
    for (i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        rc = pthread_create(&readers[i], NULL, reader, (void *)&reader_ids[i]);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Create writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        rc = pthread_create(&writers[i], NULL, writer, (void *)&writer_ids[i]);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Join reader threads
    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&write_mutex);
    sem_destroy(&read_count_sem);

    return 0;
}
