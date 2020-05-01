#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>

typedef struct lock {
  pthread_mutex_t mutex[1];
} Lock;

Lock *make_lock ()
{
  Lock *lock = (Lock *) malloc (sizeof(Lock));
  pthread_mutex_init (lock->mutex, NULL);
  return lock;
}

void lock_acquire (Lock *lock)
{
  pthread_mutex_lock (lock->mutex);
}

void lock_release (Lock *lock)
{
  pthread_mutex_unlock (lock->mutex);
}
