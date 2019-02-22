#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strsplit1(char *string, char sep, char *first, char *second) {
    char *sep_ptr = strchr(string, sep);
    int n = sep_ptr - string;
    strncpy(first, string, n);
    first[n] = '\0';
    strcpy(second, sep_ptr+1);
}

void strsplit2(char *string, char sep, char *first, char *second) {
    int i;
    for (i=0; ; i++) {
        if (string[i] == sep) {
            first[i] = '\0';
            break;
        }
        first[i] = string[i];
    }
    for (int j=0; ; j++) {
        i++;
        if (string[i] == '\0') {
            second[j] = '\0';
            break;
        }
        second[j] = string[i];
    }
}

void strsplit3(char *string, char sep, char *first, char *second) {
    while (*string != sep) {
        *first++ = *string++;
    }
    *first = '\0';
    string++;
    while (*string != '\0') {
        *second++ = *string++;
    }
    *second = '\0';
}

void strsplit4(char *string, char sep, char *first, char *second) {
    char *copy = strdup(string);

    char *token;
    char sep_str[2];
    sep_str[0] = sep;
    sep_str[1] = '\0';

    token = strtok(copy, sep_str);
    strcpy(first, token);

    token = strtok(NULL, sep_str);
    strcpy(second, token);
}

void strsplit5(char *string, char sep, char *first, char *second) {
    // Variable length arrays!
    // https://gcc.gnu.org/onlinedocs/gcc/Variable-Length.html
    // The following line is legal now, as of the C99 standard
    char temp[strlen(string)+1];

    strcpy(temp, string);
}

void strsplit6(char *string, char sep, char *first, char *second) {
    char *copy = strdup(string);
    char *sep_ptr = strchr(copy, sep);
    *copy = '\0';

    // to see what's wrong with the following,
    first = copy;
    second = sep_ptr + 1;
    // TODO: draw the stack diagram at this point
}

void strsplit7(char *string, char sep, char **first, char **second) {
    char *copy = strdup(string);

    char *sep_ptr = strchr(copy, sep);
    *sep_ptr = '\0';
    *first = copy;
    *second = sep_ptr + 1;
    // TODO: draw the stack diagram at this point
}

void reset(char *first, char *second) {
    strcpy(first, "undefined");
    strcpy(second, "undefined");
}

int main() {
    char string[] = "Hello World";
    char first[32] = "undefined";
    char second[32] = "undefined";

    strsplit1(string, ' ', first, second);
    printf("%s\n", first);
    printf("%s\n", second);
    printf("%s\n\n", string);

    reset(first, second);
    strsplit2(string, ' ', first, second);
    printf("%s\n", first);
    printf("%s\n", second);
    printf("%s\n\n", string);

    reset(first, second);
    strsplit3(string, ' ', first, second);
    printf("%s\n", first);
    printf("%s\n", second);
    printf("%s\n\n", string);

    reset(first, second);
    strsplit4(string, ' ', first, second);
    printf("%s\n", first);
    printf("%s\n", second);
    printf("%s\n\n", string);

    reset(first, second);
    strsplit6(string, ' ', first, second);
    printf("%s\n", first);
    printf("%s\n", second);
    printf("%s\n\n", string);

    reset(first, second);
    char *first_ptr;
    char *second_ptr;
    strsplit7(string, ' ', &first_ptr, &second_ptr);
    printf("%s\n", first_ptr);
    printf("%s\n", second_ptr);
    printf("%s\n\n", string);

    return 0;
}
