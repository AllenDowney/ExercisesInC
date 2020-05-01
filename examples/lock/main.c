/* Example code for Software Systems at Olin College.

Copyright 2012 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include "lock.h"


int main()
{
    Lock *lock = make_lock();

    lock_acquire (lock);
    printf ("%d\n", lock->value);
    lock_release (lock);
    printf ("%d\n", lock->value);
    return 0;
}
