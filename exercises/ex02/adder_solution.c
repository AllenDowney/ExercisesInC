/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 10
#define BUFFER_SIZE 20

enum ErrorCode {ALL_GOOD=0, EOF_HIT=-1, TOO_LONG=-2, NOT_DIGIT=-3};


/* add_array: Adds up the elements of an array.
*
*  array: int pointer
*  n: number of elements in the array
*
*  returns: total
*/
int add_array(int array[], int n) {
    int i;
    int total = 0;

    for (i=0; i<n; i++) {
        total += array[i];
    }
    return total;
}

/* read_integer: Reads an integer from stdin.
*
*  array: int pointer
*  n: number of elements in the array
*
*  returns: total
*/
enum ErrorCode read_integer(int *result) {
    char *res;
    char buffer[BUFFER_SIZE];
    int number;

    // read a string
    res = fgets(buffer, sizeof(buffer), stdin);
    if (res == NULL) {
        return EOF_HIT;
    }

    // check if the length of the string it too long
    if (strlen(buffer) == BUFFER_SIZE) {
        return TOO_LONG;
    }

    //printf("%s, %d\n", buffer, (int)strlen(buffer));

    // convert to integer
    number = atoi(buffer);

    // check for invalid input.  Notice that atoi returns 0
    // for invalid input, so we can't allow the used to enter 0.
    if (number == 0) {
        return NOT_DIGIT;
    }
    *result = number;
    return ALL_GOOD;
}

int main()
{
    int i;
    int status;
    int res;
    int array[ARRAY_SIZE];

    for (i=0; i<ARRAY_SIZE; i++) {
        status = read_integer(&res);
        //printf("%d\n", res);

        if (status == EOF_HIT) {
            int total = add_array(array, i);
            printf("total %d\n", total);
            return 0;
        }

        if (status == NOT_DIGIT) {
            printf("That wasn't an integer.\n");
            return -1;
        }
        if (status == TOO_LONG) {
            printf("That number was too long.\n");
            return -1;
        }
        array[i] = res;
    }

    // if we get to the end of the loop, the user entered
    // too many numbers
    printf("Too many numbers.\n");
    return -1;
}
