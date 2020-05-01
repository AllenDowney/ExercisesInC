#include <pthread.h>
#include "cond.h"

typedef struct {
  int value, wakeups;
  pthread_mutex_t pmutex[1];
  Cond *cond;
} Semaphore;

Semaphore *make_semaphore (int value);
void semaphore_wait (Semaphore *semaphore);
void semaphore_signal (Semaphore *semaphore);
