#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define COUNT_LIMIT 10

int count = 0;
pthread_mutex_t mutex;

void *increment_counter(void *threadid) {
    long tid;
    tid = (long)threadid;

    while (1) {
        pthread_mutex_lock(&mutex);  // Lock mutex before entering critical section

        if (count < COUNT_LIMIT) {
            count++;
            printf("Thread %ld incremented count to %d\n", tid, count);
        } else {
            pthread_mutex_unlock(&mutex);  // Unlock mutex before exiting
            break;
        }

        pthread_mutex_unlock(&mutex);  // Unlock mutex after critical section
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, increment_counter, (void *)t);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Join threads
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    printf("Final count value: %d\n", count);

    return 0;
}
