/* Example code for Software Systems at Olin College.

Copyright 2012 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include "lock.h"

#define SIZE 100000

typedef struct {
  int next_id;
  int array[SIZE];
  Lock *lock;
} Environment;

Environment *make_environment ()
{
  int i;

  Environment *env = (Environment *) malloc (sizeof (Environment));
  if (env == NULL) {
    perror ("malloc failed");
    exit (-1);
  }
  env->next_id = 0;

  for (i=0; i<SIZE; i++) {
    env->array[i] = 0;
  }

  env->lock = make_lock ();
  return env;
}

int get_next_id (Environment *env)
{
  int id = env->next_id;
  env->next_id++;
  return id;
}

void loop_and_count (pthread_t self, Environment *env)
{
  int id;

  while (1) {
    lock_acquire (env->lock);
    id = get_next_id (env);
    lock_release (env->lock);

    // printf ("%d got %d\n", self, id);

    if (id >= SIZE) return;
    env->array[id]++;
  }
}

void check_array (Environment *env)
{
  int i, count=0;

  printf ("Checking...\n");

  for (i=0; i<SIZE; i++) {
    if (env->array[i] != 1) {
      count++;
    }
  }
  printf ("%d errors found\n", count);

}

/* The entry procedure is where the child thread will start executing. */

void *entry (void *arg)
{
  pthread_t self = pthread_self ();

  /* The entry procedure takes a single pointer as an argument.
     It is a pointer to the Environment structure that contains
     all the variables the parent and child will share. */

  Environment *env = (Environment *) arg;

  /* the child keeps getting ids and incrementing array
     elements until it gets an id that is bigger than the
     array; then it quits */

  loop_and_count (self, env);
  printf ("Child done looping.\n");

  pthread_exit (NULL);
}

void main ()
{
  int i;
  Environment *env;
  pthread_t self;
  pthread_t child;
  int ret;

  self = pthread_self ();

  env = make_environment ();

  /* the parent thread uses sproc to create the new thread, passing
     a pointer to card as an argument */

  ret = pthread_create (&child, NULL, entry, (void *) env);
  if (ret == -1) {
    perror ("pthread_create failed");
    exit (-1);
  }

  loop_and_count (self, env);

  printf ("Parent done looping.\n");

  ret = pthread_join (child, NULL);
  if (ret == -1) {
    perror ("pthread_join failed");
    exit (-1);
  }

  check_array (env);
  exit (0);
}
