/* Example code for Software Systems at Olin College.

Copyright 2012 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include "lock.h"

Lock *make_lock ()
{
    Lock *lock = (Lock *) malloc (sizeof(Lock));
    pthread_mutex_init (lock->mutex, NULL);
    return lock;
}

void acquire (Lock *lock)
{
    pthread_mutex_lock (lock->mutex);
}

void release (Lock *lock)
{
    pthread_mutex_unlock (lock->mutex);
}
