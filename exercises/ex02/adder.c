/*
 * Author: Isabel Blancett
 * Software Systems Ex. 2
 */

#define MAX 20
#define BUFFER 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* GET_INTEGER: Reads input from user, triggers errors when the user types an
 * integer larger than 9 digits or uses letters/other non-numerical characters.
 *
 * Returns 1 if user triggers an error or presses ^D
 * Returns 0 if user can continue to enter integers
 */
int get_integer(int *int_pntr) {
  char str[BUFFER];
  fgets(str,BUFFER+1,stdin);
  if (strlen(str) == sizeof str - 1){
    puts("I don't like numbers bigger than 9 digits.  Start over!");
    return 1;
  }
  if (feof(stdin)) {
    return 1;
  }
  else {
    *int_pntr = atoi(str);
    if (*int_pntr == 0) {
      puts("I don't like letters.  Start over!");
      return 1;
    }
    return 0;
  }
}

/* MAIN: Continually reads integers into an array size 20 and adds them all up
 * when the user is done
 */
int main() {
  int array[MAX];
  int integer;
  int counter = 0;
  int total = 0;
  puts("Type a number to add on each line.  When you're done, press ^D.\n");
  while(1) {
    if (get_integer(&integer)) {
      break;
    }
    if (counter >= MAX) {
      puts("Enter less than 20 integers next time!");
      break;
    }
    else {
      array[counter] = integer;
      counter ++;
    }
  }
  for (int i=0; i<counter; i++) {
    total = total + array[i];
  }
  printf("Your total is %i\n", total);
}
