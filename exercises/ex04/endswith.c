/* Example code for Software Systems at Olin College.

Copyright 2017 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "endswith.h"

/* endswith: Checks whether s ends with suffix.

s: string
suffix: string
returns: 1 if true, 0 otherwise
*/
int endswith(char *s, char *suffix)
{
    int n1 = strlen(s);
    int n2 = strlen(suffix);
    char *location = s + n1 - n2;

    char *found = strstr(s, suffix);
    return found == location;
}
