#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Array style
char *palindrome1(char *s) {
    int n = strlen(s);
    char *dest = malloc((2*n+1) * sizeof(char));
    for (int i=0; i<n; i++) {
        dest[i] = s[i];
        dest[2*n-i-1] = s[i];
    }
    dest[2*n] = 0;
    return dest;
}

// Pointer style
char *palindrome2(char *s) {
    int n = strlen(s);
    char *res = malloc((2*n+1) * sizeof(char));

    char *dest = res;     // need to make a copy before modifying
    char *from = s;

    for (int i=0; i<n; i++) {
        *dest++ = *from++;
    }

    from = s + n - 1;;
    for (int i=0; i<n; i++) {
        *dest++ = *from--;
    }
    *dest = 0;
    return res;
}

void inplace_reverse(char * str) {
    // from https://stackoverflow.com/questions/784417/reversing-a-string-in-c

    char * end = str + strlen(str) - 1;

    // swap the values in the two given variables
    // XXX: fails when a and b refer to same memory location
#   define XOR_SWAP(a,b) do\
    {\
        a ^= b;\
        b ^= a;\
        a ^= b;\
    } while (0)

    // walk inwards from both ends of the string,
    // swapping until we get to the middle
    while (str < end)
    {
        XOR_SWAP(*str, *end);
        str++;
        end--;
    }
#   undef XOR_SWAP
}

// library style
char *palindrome3(char *s) {
    int n = strlen(s);
    char *dest = malloc((2*n+1) * sizeof(char));
    strcpy(dest, s);
    char *rev = strdup(s);
    inplace_reverse(rev);
    strcat(dest, rev);
    return dest;
}


// bad style
char *palindrome4(char *s) {
    int n = strlen(s);
    char dest[100];

    for (int i=0; i<n; i++) {
        dest[i] = s[i];
        dest[2*n-i-1] = s[i];
    }
    dest[2*n] = 0;
    return strdup(dest);
}


// bad style
char *palindrome5(char *s) {
    int n = strlen(s);
    char *dest = malloc((2*n+1) * sizeof(char));
    strcpy(dest, s);
    inplace_reverse(s);
    strcat(dest, s);
    return dest;
}


// bad style
char *palindrome6(char *s) {
    int n = strlen(s);
    char *dest = malloc((2*n+1) * sizeof(char));
    for (int i=0; i<n; i++) {
        *(dest+i) = *(s+i);
        *(dest+2*n-i-1) = *(s+i);
    }
    *(dest+2*n) = 0;
    return dest;
}


// very illegal, but for some reason a just a warning
char *palindrome7(char *s) {
    int n = strlen(s);
    char dest[100];

    for (int i=0; i<n; i++) {
        dest[i] = s[i];
        dest[2*n-i-1] = s[i];
    }
    dest[2*n] = 0;
    return dest;
}


// wrong API
void palindrome8(char *s, char *dest) {
    int n = strlen(s);

    for (int i=0; i<n; i++) {
        dest[i] = s[i];
        dest[2*n-i-1] = s[i];
    }
    dest[2*n] = 0;
}


int main() {
    char string[] = "red";

    char *res = palindrome1(string);
    printf("%s\n", string);
    printf("%s\n", res);

    res = palindrome2(string);
    printf("%s\n", string);
    printf("%s\n", res);

    res = palindrome3(string);
    printf("%s\n", string);
    printf("%s\n", res);

    res = palindrome4(string);
    printf("%s\n", string);
    printf("%s\n", res);

    res = palindrome5(string);
    printf("%s\n", string);
    printf("%s\n", res);

    res = palindrome6(string);
    printf("%s\n", string);
    printf("%s\n", res);

    char dest[128];
    palindrome8(string, dest);
    printf("%s\n", string);
    printf("%s\n", dest);

    return 0;
}
