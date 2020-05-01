/* Example code for Software Systems at Olin College.

Copyright 2012 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

typedef struct {
    volatile int value;
} Lock;


Lock *make_lock ();
void lock_acquire (Lock *lock);
void lock_release (Lock *lock);
