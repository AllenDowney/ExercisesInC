#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include "semaphore.h"

typedef struct lock {
  Semaphore *sem;
} Lock;

Lock *make_lock ()
{
  Lock *lock = (Lock *) malloc (sizeof(Lock));
  lock->sem = make_semaphore(1);
  return lock;
}

void lock_acquire (Lock *lock)
{
  semaphore_wait(lock->sem);
}

void lock_release (Lock *lock)
{
  semaphore_signal(lock->sem);
}
