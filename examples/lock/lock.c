/* Example code for Software Systems at Olin College.

Copyright 2012 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include "lock.h"

Lock *make_lock ()
{
  Lock *lock = (Lock *) malloc (sizeof(Lock));
  lock->value = 0;
  return lock;
}

/* WARNING: this is a deliberately broken implementation of acquire.
   It will probably work most of them time. */
void lock_acquire (Lock *lock)
{
  while (lock->value == 1);
  lock->value = 1;
}

void lock_release (Lock *lock)
{
  lock->value = 0;
}
