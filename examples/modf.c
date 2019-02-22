/* Example code for Software Systems at Olin College.

Copyright 2018 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

1) Write a function called `get_int_part` that takes as parameters
an array of doubles and the integer number of elements in the array.
It should allocate an array of doubles the same size as the input,
and then use modf to compute the integer part of each element in
the array, storing the result in the new array, and then returning
the new array.

2) Write a function called `get_both_parts` that takes the
same parameters as `get_int_part`, plus an additional pointer.
It should returns the same value as `get_int_part`, and it
should also allocate an array of doubles to contain the fraction part
of the elements from the array.  It should "return" this second array
by setting the pointer it got as an argument.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* get_int_part: Compute the integer part of the elements in an array.

array: array of doubles
length: number of elements in the array

returns: new array, caller must free
*/
// TODO: Write this function

void test_get_int_part()
{
    double array[] = {1.2, 2.718, 3.1412, 5.6};
    double expected[] = {1, 2, 3, 5};
    int length = sizeof(array) / sizeof(double);

    double *int_part = get_int_part(array, length);

    for (int i=0; i<length; i++) {
        //printf("%lf\n", result[i]);
        assert(int_part[i] == expected[i]);
    }
}


/* get_both_parts: Compute the int and frac parts of the elements in an array.

array: array of doubles
length: number of elements in the array
p: location where the address of the frac_array should go

returns: new array, caller must free
*/
//TODO: Write this function


void test_get_both_parts()
{
    double array[] = {1.2, 2.718, 3.14159, 5.6};
    double expected_int[] = {1, 2, 3, 5};
    double expected_frac[] = {0.2, 0.718, 0.14159, 0.6};
    double *frac_part;
    int length = sizeof(array) / sizeof(double);

    double *int_part = get_both_parts(array, length, &frac_part);

    for (int i=0; i<length; i++) {
        printf("%.18lf  %.18lf\n", int_part[i], expected_int[i]);
        printf("%.18lf  %.18lf\n", frac_part[i], expected_frac[i]);
        assert(int_part[i] == expected_int[i]);
        assert(frac_part[i] == expected_frac[i]);
    }
}

int main (int argc, char *argv[])
{
    test_get_int_part();
    test_get_both_parts();
    printf("All tests passed\n");
}
