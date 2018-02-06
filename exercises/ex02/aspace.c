/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    void *q = malloc(128);
    void *t = malloc(2);
    void *r = malloc(27);
    char *s = "Literal string";

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("Address of p is %p\n", p);
    printf ("Address of s is %p\n", s);
    // t and r are 32 bytes apart
    printf ("Address of t is %p\n", t);
    printf ("Address of r is %p\n", r);

    return 0;
}
