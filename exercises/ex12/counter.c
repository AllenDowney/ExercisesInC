/*     This file contains an example program from The Little Book of
       Semaphores, available from Green Tea Press, greenteapress.com

       Copyright 2014 Allen B. Downey
       License: Creative Commons Attribution-ShareAlike 3.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_CHILDREN 2

// UTILITY FUNCTIONS

/*  perror_exit
 *  
 *  Prints an error message and exits.
 *
 *  s: message to print
 *
 */
void perror_exit (char *s)
{
    perror (s);
    exit (-1);
}

/*  check_malloc
 *  
 *  Calls malloc and checks the result.
 *
 *  size: number of bytes to allocate
 *
 */
void *check_malloc(int size)
{
    void *p = malloc (size);
    if (p == NULL) perror_exit ("malloc failed");
    return p;
}

// Semaphore

typedef sem_t Semaphore;

/*  make_semaphore
 *  
 *  Allocates and initializes a Semaphore.
 *
 *  n: initial value
 *
 *  returns: pointer to new Semaphore
 */
Semaphore *make_semaphore (int n)
{
    Semaphore *sem = check_malloc (sizeof(Semaphore));
    int ret = sem_init(sem, 0, n);
    if (ret == -1) perror_exit ("sem_init failed");
    return sem;
}

/*  sem_signal
 *  
 *  Signals a semaphore.
 *
 *  sem: pointer to Semaphore
 *
 *  returns: 0 on success, -1 on error
 */
int sem_signal(Semaphore *sem)
{
    return sem_post(sem);
}

// Shared

typedef struct {
    int counter;
    int end;
    int *array;
} Shared;

/*  make_shared
 *  
 *  Initializes the environment shared by threads.
 *
 *  end: size of the shared array
 *
 *  returns: pointer to new Shared
 */
Shared *make_shared (int end)
{
    int i;
    Shared *shared = check_malloc (sizeof (Shared));

    shared->counter = 0;
    shared->end = end;
  
    shared->array = check_malloc (shared->end * sizeof(int));
    for (i=0; i<shared->end; i++) {
        shared->array[i] = 0;
    }
    return shared;
}

/*  make_thread
 *  
 *  Allocates and initializes a POSIX thread.
 *
 *  entry: pointer to the entry function
 *  shared: pointer to the shared environment
 *
 *  returns: ID of the new thread, which has integer semantics
 *
 */
pthread_t make_thread(void *(*entry)(void *), Shared *shared)
{
    int ret;
    pthread_t thread;

    ret = pthread_create (&thread, NULL, entry, (void *) shared);
    if (ret != 0) perror_exit ("pthread_create failed");
    return thread;
}

/*  join_thread
 *  
 *  Waits for the given thread to exit.
 *
 *  thread: ID of the thread we should wait for
 *
 */
void join_thread (pthread_t thread)
{
    int ret = pthread_join (thread, NULL);
    if (ret == -1) perror_exit ("pthread_join failed");
}

/*  child_code
 *  
 *  Increments the values in an array.
 *
 *  If access to shared->counter is synchonized, every element in
 *  the array should be incremented exactly once.
 *
 *  If there are race conditions, some elements will be incremented
 *  zero times or more than once.  We can detect these synchronization
 *  errors by inspecting the array after all threads exit.
 *
 *  shared: pointer to shared environment
 *
 */
void child_code (Shared *shared)
{
    printf ("Starting child at counter %d\n", shared->counter);

    while (1) {
	    if (shared->counter >= shared->end) {
	        return;
	    }
	    shared->array[shared->counter]++;
	    shared->counter++;

	    if (shared->counter % 100000 == 0) {
	        printf ("%d\n", shared->counter);
	    }
    }
}

/*  entry
 *  
 *  Starting point for child threads,
 *
 *  arg: pointer to the shared environment
 *
 */
void *entry (void *arg)
{
    Shared *shared = (Shared *) arg;
    child_code (shared);
    printf ("Child done.\n");
    pthread_exit (NULL);
}

/*  check_array
 *  
 *  Checks whether every element of the shared array is 1.
 *  Prints the number of synchronization errors.
 *
 *  shared: pointer to shared environment
 *
 */
void check_array (Shared *shared)
{
    int i, errors=0;

    printf ("Checking...\n");

    for (i=0; i<shared->end; i++) {
	    if (shared->array[i] != 1) errors++;
    }
    printf ("%d errors.\n", errors);
}

/*  main
 *  
 *  Creates the given number of children and runs them concurrently.
 *
 */
int main ()
{
    int i;
    pthread_t child[NUM_CHILDREN];

    Shared *shared = make_shared (100000000);

    for (i=0; i<NUM_CHILDREN; i++) {
	child[i] = make_thread (entry, shared);
    }

    for (i=0; i<NUM_CHILDREN; i++) {
	    join_thread (child[i]);
    }

    check_array (shared);
    return 0;
}
