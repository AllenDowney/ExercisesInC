/*
 * Author: Isabel Blancett
 * Adapted from cards exercise in Head First C
 * Software Systems Ex. 1
 */


#include <stdio.h>
#include <stdlib.h>


/* Prompts the user for input and puts the reply in the given buffer.

   User input is truncated to the first two characters.

   prompt: string prompt to display
   card_name: buffer where result is stored
*/
void get_card_name(char *prompt, char *card_name) {
  puts(prompt);
  scanf("%2s", card_name);
}

/* Calculates new count based on value

   count: current counter
   val: assigned card value
   returns: count
*/
int update_counter(int count, int val) {
  if ((val > 2) && (val < 7)) {
    count++;
  } else if (val == 10) {
    count--;
  }
  return count;
}

/* Check if value is a card number

   val: assigned card value
*/
void check_value(int val) {
  if ((val < 1) || (val > 10)) {
    puts("I don't understand that value!");
  }
}

int main()
{

  char card_name[3];
  int count = 0;

  // pedantic option produces warnings as errors
  // val declaration was moved out of the loop to avoid re-declaration
  int val;
  while (card_name[0] != 'X') {

    get_card_name("Enter the card_name: ", card_name);
    val = 0;

    switch(card_name[0]) {

    case 'K':
    case 'Q':
    case 'J':
      val = 10;
      break;

    case 'A':
      val = 11;
      break;

    case 'X':
      continue;

    default:
      val = atoi(card_name);
      check_value(val);
    }

    count = update_counter(count, val);
    printf("Current count: %i\n", count);
  }
  return 0;

}
