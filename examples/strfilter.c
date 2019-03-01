#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strfilter1(char *string, char *letters) {
    char buffer[strlen(string)+1];
    int j = 0;

    // TODO: hoist strlen out of the loop!
    // See "Accidentally quadratic"
    for (int i=0; i<strlen(string); i++) {
        char *ptr = strchr(letters, string[i]);
        if (ptr) {
            buffer[j++] = string[i];
        }
    }
    buffer[j] = '\0';
    return strdup(buffer);
}

char *strfilter2(char *string, char *letters) {
    char buffer[strlen(string)+1];
    char *dest = buffer;
    char c;

    while (c = *string++) {
        char *ptr = strchr(letters, c);
        if (ptr) {
            *dest++ = c;
        }
    }
    *dest = '\0';
    return strdup(buffer);
}

// TODO: Find everything wrong with the following two functions

char *strfilter3(char *string, char *letters) {
    int length = strlen(string);
    char buffer[length];
    int j = 0;

    for (int i=0; i<length; i++) {
        char *ptr = strchr(letters, string[i]);
        if (ptr) {
            buffer[j++] = string[i];
        }
    }
    return buffer;
}

char *strfilter4(char *string, char *letters) {
    char buffer[100];
    char c;

    while (c = *string++) {
        char *ptr = strchr(letters, c);
        if (ptr) {
            strcat(buffer, c);
        }
    }
    int length = sizeof(buffer);
    char *res = (char *) malloc (length * sizeof(char));
    strcpy(buffer, res);
    return res;
}

int main() {
    char string[] = "equation";
    char letters[] = "aeiou";

    char *filtered = strfilter1(string, letters);
    printf("%s\n", filtered);

    char *filtered2 = strfilter2(string, letters);
    printf("%s\n", filtered2);

    char *filtered3 = strfilter3(string, letters);
    printf("%s\n", filtered3);

    char *filtered4 = strfilter4(string, letters);
    printf("%s\n", filtered4);

    return 0;
}
