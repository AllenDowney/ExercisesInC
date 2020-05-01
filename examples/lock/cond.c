#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include "lock.h"
#include "cond.h"

static void perror_exit (char *s)
{
  perror (s);
  exit (-1);
}

Cond *make_cond ()
{
  int n;
  Cond *cond = (Cond *) malloc (sizeof(Cond));
  if (cond == NULL) perror_exit ("malloc failed");

  n = pthread_cond_init (cond, NULL);
  if (n != 0) perror_exit ("make_cond failed");

  return cond;
}

void cond_wait (Cond *cond, pthread_mutex_t *mutex)
{
  int n = pthread_cond_wait (cond, mutex);
  if (n != 0) perror_exit ("cond_wait failed");
}

void cond_signal (Cond *cond)
{
  int n = pthread_cond_signal (cond);
  if (n != 0) perror_exit ("cond_wait failed");
}
