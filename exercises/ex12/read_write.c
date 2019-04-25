/* Example code for Think OS.

Copyright 2018 Allen Downey
License: GNU GPLv3

TODO: Modify reader_code and writer_code so that any number of
reader threads can "read the thing" concurrently, but only one
writer can "write the thing" at a time, and no readers can read
concurrently with a writer who is writing.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

#define NUM_READERS 3
#define NUM_WRITERS 3

/* Structure that contains variables shared between threads.
*/
typedef struct {
    int counter;
    Mutex *mutex;
    Cond *cond;
} Shared;

/* Allocate the shared structure.
*/
Shared *make_shared()
{
    Shared *shared = check_malloc(sizeof(Shared));
    shared->counter = 0;
    shared->mutex = make_mutex();
    shared->cond = make_cond();
    return shared;
}

/* Code run by the reader threads.
*/
void reader_code(Shared *shared)
{
    printf("I am reading the thing.\n");
}

/* Code run by the writer threads.
*/
void writer_code(Shared *shared)
{
    printf("I am writing the thing.\n");
}

/* Entry point for the reader threads.
*/
void *reader_entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    reader_code(shared);
    pthread_exit(NULL);
}

/* Entry point for the writer threads.
*/
void *writer_entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    writer_code(shared);
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
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    Shared *shared = make_shared();

    for (int i=0; i<NUM_READERS; i++) {
        readers[i] = make_thread(reader_entry, shared);
    }

    for (int i=0; i<NUM_WRITERS; i++) {
        writers[i] = make_thread(writer_entry, shared);
    }

    for (int i=0; i<NUM_READERS; i++) {
        join_thread(readers[i]);
    }

    for (int i=0; i<NUM_WRITERS; i++) {
        join_thread(writers[i]);
    }

    printf("Parent exiting\n");
    return 0;
}
