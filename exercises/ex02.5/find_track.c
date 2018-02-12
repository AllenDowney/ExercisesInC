/* Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{
  int i;
  int comp_status;
  int exec_status;
  regex_t r;

  for (i=0; i<NUM_TRACKS; i++) {

    comp_status = regcomp(&r,pattern,REG_EXTENDED|REG_NOSUB);

    // if regcomp returns a number not 0, print error
    if (comp_status != 0) {
      printf("Error Compiling Regex: %i", comp_status);
      exit(1);
    }

    exec_status = regexec(&r,tracks[i],(size_t)0,NULL,0);
    if(exec_status == 0) {
      printf("Track %i: '%s'\n", i, tracks[i]);
    }

    // if regexec returns a number not 0 or 1, print error
    else if(exec_status != 1) {
      printf("Error Executing Regex: %i", exec_status);
      exit(1);
    }

    // free up regex data structure
    regfree(&r);
  }
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    //find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
