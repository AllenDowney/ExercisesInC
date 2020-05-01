/* Example code for Software Systems at Olin College.

Copyright 2012 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

typedef struct {
  pthread_something mutex;
} Lock;


Lock *make_lock ();
void acquire (Lock *lock);
void release (Lock *lock);
