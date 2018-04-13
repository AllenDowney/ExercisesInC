/* Example code for Think OS.

Copyright 2015 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "queue.h"
#include "utils.h"

#define NUM_CHILDREN 2
#define NUM_ELEMENTS 64
#define QUEUE_LENGTH 64


// SHARED

typedef struct {
    Queue *queue;
} Shared;

/* Initialize the state shared between threads.
*/
Shared *make_shared() {
    Shared *shared = check_malloc(sizeof(Shared));
    shared->queue = make_queue(QUEUE_LENGTH);
    return shared;
}

// PRODUCER-CONSUMER CODE

void *producer_entry(void *arg) {
    Shared *shared = (Shared *) arg;
    for (int i=0; i<NUM_ELEMENTS; i++) {
        printf("adding item %d\n", i);
        queue_push(shared->queue, i);
    }
    pthread_exit(NULL);
}

void *consumer_entry(void *arg) {
    Shared *shared = (Shared *) arg;

    for (int i=0; i<NUM_ELEMENTS; i++) {
        int item = queue_pop(shared->queue);
        printf("consuming item %d\n", item);
    }
    pthread_exit(NULL);
}

// THREAD

pthread_t make_thread(void *(*entry)(void *), Shared *shared) {
    pthread_t thread;

    int ret = pthread_create(&thread, NULL, entry, (void *) shared);
    if (ret != 0) {
        perror_exit("pthread_create failed");
    }
    return thread;
}

void join_thread(pthread_t thread) {
    int ret = pthread_join(thread, NULL);
    if (ret == -1) {
        perror_exit("pthread_join failed");
    }
}

int main() {
    pthread_t child[NUM_CHILDREN];

    Shared *shared = make_shared();

    child[0] = make_thread(producer_entry, shared);
    child[1] = make_thread(consumer_entry, shared);

    for (int i=0; i<NUM_CHILDREN; i++) {
        join_thread(child[i]);
    }

    return 0;
}
