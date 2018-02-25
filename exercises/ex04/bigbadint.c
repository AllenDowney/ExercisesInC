/* Example code for Exercises in C.

This program shows a way to represent a BigInt type (arbitrary length integers)
using C strings, with numbers represents as a string of decimal digits in reverse order.

This program contains two deliberate errors as a debugging exercise.

1) Compile and run this program like this:

gcc -g -std=c99 bigbadint.c
./a.out

You should see that reverse_string passes its test,
but itoc and add_digits don't.

2) Read the GDB tutorial at

http://web.eecs.umich.edu/~sugih/pointers/summary.html

3) Start gdb like this:

gdb a.out

4) At the gdb prompt, type

run

to run the program.  Since itoc is failing, let's look at
its source code:

list itoc

And set a break point at the beginning of itoc

break itoc

Now if you run the program again, it should stop every time
itoc is called, and you'll be able to see the value of the parameter.

To run a single line of code, type

step

To print the value of a variable

print i

5) Read the descriptions of step and next, try them out, and make
sure you know the difference.

6) See if you can find the error in itoc, and fix it.

7) In main, uncomment the line that calls test_reverse_string_again.
Compile and run the program again.  You should see that
reverse_string is actually not correct, even though it passes
its test.  See if you can debug it.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/* reverse_string: Returns a new string with the characters reversed.

It is the caller's responsibility to free the result.

s: string
returns: string
*/
char *reverse_string(char *s) {
    int n = strlen(s);
    char *t = malloc(n+1);
    char *to = t;
    char *from = s + n - 1;

    while(1) {
        *to = *from;
        to++;
        from--;
        if (from < s) {
            break;
        }
    }
    return t;
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
    assert(i >= 0 && i <=9);
    return 0 + i;
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
    int sum = ctoi(a) + ctoi(b) + ctoi(c);
    *total = itoc(sum % 10);
    *carry = itoc(sum / 10);
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

    /* OPTIONAL TODO: Modify this function to allocate and return z
    *  rather than taking an empty buffer as a parameter.
    *  Hint: you might need a helper function.
    */

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

void test_reverse_string() {
    char *s = "123";
    char *t = reverse_string(s);
    if (strcmp(t, "321") == 0) {
        printf("reverse_string passed\n");
    } else {
        printf("reverse_string failed\n");
    }
}

void test_itoc() {
    char c = itoc(3);
    if (c == '3') {
        printf("itoc passed\n");
    } else {
        printf("itoc failed\n");
    }
}

void test_add_digits() {
    char total, carry;
    add_digits('7', '4', '1', &total, &carry);
    if (total == '2' && carry == '1') {
        printf("add_digits passed\n");
    } else {
        printf("add_digits failed\n");
    }
}

void test_add_bigint() {
    char *s = "1";
    char *t = "99999999999999999999999999999999999999999999";
    char *res = "000000000000000000000000000000000000000000001";

    BigInt big1 = make_bigint(s);
    BigInt big2 = make_bigint(t);
    BigInt big3 = malloc(100);

	add_bigint(big1, big2, '0', big3);

    if (strcmp(big3, res) == 0) {
        printf("add_bigint passed\n");
    } else {
        printf("add_bigint failed\n");
    }
}

void test_reverse_string_again() {
    char *buffer = malloc(400);
    for (int i=0; i<400; i++) {
        buffer[i] = i;
    }
    free(buffer);
    char *reversed = reverse_string("123");
    printf("%s\n", reversed);
}

int main (int argc, char *argv[])
{
    test_reverse_string();
    test_itoc();
    test_add_digits();

    //TODO: When you have the first three functions working,
    //      uncomment the following, and it should work.
    // test_add_bigint();

    // test_reverse_string_again();

    return 0;
}
