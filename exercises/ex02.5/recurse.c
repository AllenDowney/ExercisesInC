/* Example code for Exercises in C.

*/

#include <stdio.h>
#include <stdlib.h>

/* factorial: Computes factorial(n).
*/
int factorial(int n) {
    printf("local variable n at %p has value %d\n", &n, n);

    if (n == 0) {
        return 1;
    } else {
        int res = factorial(n-1);
        return n * res;
    }
}


/* fibonacci: Computes fibonacci(n).

    Specifically, the Fibonacci series with F(0) = 0 and F(1) = 1
*/
int fibonacci(int n) {
    printf("local variable n at %p has value %d\n", &n, n);
    if (n <= 1) {
        return n;
    } else {
        int a = fibonacci(n-1);
        int b = fibonacci(n-2);
        return a + b;
    }
}


int main (int argc, char *argv[])
{
    int res = factorial(4);
    printf("factorial(3) = %d\n", res);

    int res2 = fibonacci(4);
    printf("fibonacci(3) = %d\n", res2);

    printf("Location of factorial code is %p\n", factorial);
    printf("Location of fibonacci code is %p\n", fibonacci);
    printf("Location of main code is %p\n", main);
}
