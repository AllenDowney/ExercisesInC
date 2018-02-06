/* Example code for Exercises in C.

Add two BigInts, represented as strings of decimal digits.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* reverse_string: Returns a new string with the characters reversed.

It is the caller's responsibility to free the result.

s: string
returns: string
*/
char *reverse_string(char *s) {
    //TODO: Fill this in.
    return NULL;
}

/* ctoi: Converts a character to integer.

c: one of the characters '0' to '9'
returns: integer 0 to 9
*/
int ctoi(char c) {
    assert(isdigit(c));
    return c - '0';
}

/* itoc: Converts an integer to character.

i: integer 0 to 9
returns: character '0' to '9'
*/
char itoc(int i) {
    //TODO: Fill this in, with an appropriate assertion.
    return '0';
}

/* add_digits: Adds two decimal digits, returns the total and carry.

For example, if a='5', b='6', and carry='1', the sum is 12, so
the output value of total should be '2' and carry should be '1'

a: character '0' to '9'
b: character '0' to '9'
c: character '0' to '9'
total: pointer to char
carry: pointer to char

*/
void add_digits(char a, char b, char c, char *total, char *carry) {
    //TODO: Fill this in.
}

/* Define a type to represent a BigInt.
   Internally, a BigInt is a string of digits, with the digits in
   reverse order.
*/
typedef char * BigInt;

/* add_bigint: Adds two BigInts

Stores the result in z.

x: BigInt
y: BigInt
carry_in: char
z: empty buffer
*/
void add_bigint(BigInt x, BigInt y, char carry_in, BigInt z) {
    char total, carry_out;
    int dx=1, dy=1, dz=1;
    char a, b;

    //TODO: Modify this function to allocate and return z rather
    //      than taking an empty buffer as a parameter.
    //      Hint: you might need a helper function.

    if (*x == '\0') {
        a = '0';
        dx = 0;
    }else{
        a = *x;
    }
    if (*y == '\0') {
        b = '0';
        dy = 0;
    }else{
        b = *y;
    }

    // printf("%c %c %c\n", a, b, carry_in);
    add_digits(a, b, carry_in, &total, &carry_out);
    // printf("%c %c\n", carry_out, total);

    // if total and carry are 0, we're done
    if (total == '0' && carry_out == '0') {
        *z = '\0';
        return;
    }
    // otherwise store the digit we just computed
    *z = total;

    // and make a recursive call to fill in the rest.
    add_bigint(x+dx, y+dy, carry_out, z+dz);
}

/* print_bigint: Prints the digits of BigInt in the normal order.

big: BigInt
*/
void print_bigint(BigInt big) {
    char c = *big;
    if (c == '\0') return;
    print_bigint(big+1);
    printf("%c", c);
}

/* make_bigint: Creates and returns a BigInt.

Caller is responsible for freeing.

s: string of digits in the usual order
returns: BigInt
*/
BigInt make_bigint(char *s) {
    char *r = reverse_string(s);
    return (BigInt) r;
}

int main (int argc, char *argv[])
{
    char *s = "1";
    char *t = "99999999999999999999999999999999999999999999";
    char total, carry;
    BigInt big3 = malloc(100);

    BigInt big1 = make_bigint(s);
    print_bigint(big1);
    printf("\n");

    BigInt big2 = make_bigint(t);
    print_bigint(big2);
    printf("\n");

    add_bigint(big1, big2, '0', big3);
    print_bigint(big3);
    printf("\n");

    return 0;
}
