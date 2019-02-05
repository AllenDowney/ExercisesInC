#include <stdio.h>
#include <stdlib.h>

int main() {

    char *pointer = "String literal";
    char array1[] = "String literal";
    char array2[32] = "String literal";

    printf("sizeof(pointer) = %ld\n", sizeof(pointer));
    printf("sizeof(array1) = %ld\n", sizeof(array1));
    printf("sizeof(array2) = %ld\n", sizeof(array2));

    array1[1] = 'p';
    printf("array1 = %s\n", array1);

    array2[1] = 'p';
    printf("array2 = %s\n", array2);

    // pointer[1] = 'p';     // segfault

    pointer = array1;
    printf("pointer = %s\n", pointer);

    // error: assignment to expression with array type
    // array1 = array2;
}
