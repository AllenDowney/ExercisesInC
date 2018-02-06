/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

// Expected output:  If an array was returned before the fault, this program
// would print out five 42's.  However, the program happens to create these
// two arrays at the exact same address, causing a segmentation fault.

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
