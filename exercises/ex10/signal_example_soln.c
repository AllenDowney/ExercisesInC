/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: MIT License

Based on an example from
https://raw.githubusercontent.com/twcamper/head-first-c/master/10/math-master.c

Based on an example in Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int score = 0;

/* Set up a signal handler.

   sig: signal number
   handler: signal handler function
*/
int catch_signal(int sig, void (*handler) (int)) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

/* Signal handler: End the game.
 */
void end_game(int sig)
{
    printf("\nFinal score: %i\n", score);
    exit(EXIT_SUCCESS);
}

int end_flag = 0;

/* Signal handler: Notify the user and raise SIGINT.
*/
void times_up(int sig) {
    //puts("\nTIME'S UP!");
    //raise(SIGINT);
    end_flag = 1;
}

int main(void) {
    int a, b, answer;
    char txt[4];

    // when the alarm goes off, call times_up
    catch_signal(SIGALRM, times_up);

    // if we get interrupted, end the game
    catch_signal(SIGINT, end_game);

    // seed the random number generator
    srandom((unsigned int) time(NULL));

    while(1) {
        a = rand() % 11;
        b = rand() % 11;
        printf("\nWhat is %d times %d? ", a, b);

        alarm(5);
	    while (1) {
	        char *ret = fgets(txt, 4, stdin);
	        if (ret) break;
	    }

        answer = atoi(txt);
        if (answer == a * b) {
            printf("\nRight!\n");
            score++;
        } else {
            printf("\nWrong!\n");
        }
        printf("Score: %i\n", score);

	    if (end_flag) {
	        end_game(0);
	    }
    }
    return 0;
}
