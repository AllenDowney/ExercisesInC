/* Example code for Think OS.

Copyright 2018 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

#define NUM_CHILDREN 5

/* Structure that contains variables shared between threads.
*/
typedef struct {
    int counter;
    Mutex *mutex;
} Shared;

/* Allocate the shared structure.
*/
Shared *make_shared()
{
    Shared *shared = check_malloc(sizeof(Shared));
    shared->counter = 0;
    shared->mutex = make_mutex();
    return shared;
}

/* Code run by the child threads.
*/
void child_code(Shared *shared)
{
    // TODO: Rewrite this function so that
    // 1) All access to shared variables is thread safe.
    // 2) No thread prints the ``part 2'' message until after
    //    all threads have printed the ``part 1'' message, and
    // 3) Threads are blocked when waiting; they do not busy wait.

    // Notice that the `Shared` structure already contains a Mutex
    // you can use; you may add one or more additional Mutex or Cond
    // objects.

    printf("Child part 1\n");
    shared->counter++;
    while (shared->counter < NUM_CHILDREN) {
        // do nothing
        // Running this loop over and over is called busy waiting.
    }
    printf("Child part 2\n");
}

/* Entry point for the child threads.
*/
void *entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    child_code(shared);
    pthread_exit(NULL);
}

/* Create a child thread.
*/
pthread_t make_thread(void *(*entry)(void *), Shared *shared)
{
    int ret;
    pthread_t thread;

    ret = pthread_create(&thread, NULL, entry, (void *) shared);
    if (ret != 0) {
        perror_exit("pthread_create failed");
    }
    return thread;
}

/* Wait for a child thread.
*/
void join_thread(pthread_t thread)
{
    int ret = pthread_join(thread, NULL);
    if (ret == -1) {
        perror_exit("pthread_join failed");
    }
}

int main()
{
    pthread_t child[NUM_CHILDREN];

    Shared *shared = make_shared();

    for (int i=0; i<NUM_CHILDREN; i++) {
        child[i] = make_thread(entry, shared);
    }

    for (int i=0; i<NUM_CHILDREN; i++) {
        join_thread(child[i]);
    }

    printf("Parent exiting\n");
    return 0;
}
