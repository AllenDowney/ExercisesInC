/* Example code for Software Systems at Olin College.

Copyright 2012 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

typedef struct {
    // put variables here that you want to share between threads
    int counter;
} Environment;

Environment *make_environment ()
{
    Environment *env = (Environment *) malloc (sizeof (Environment));

    // initialize the contents of the environment
    env->counter = 0;

    return env;
}

void *entry (void *arg)
{
    // take the argument and cast it to be an Env pointer
    Environment *env = (Environment *) arg;

    // now you can access the shared variables
    env->counter++;
    pthread_exit (NULL);
}

int main()
{
    Environment *env;
    int ret;
    pthread_t child;

    // main is in charge of creating the shared environment
    env = make_environment ();

    // and passing it to the new thread as an argument
    ret = pthread_create (&child, NULL, entry, (void *) env);
    if (ret == -1) {
        perror ("pthread_create failed");
        exit (-1);
    }

    // now the parent and child thread are running concurrently
    env->counter++;
    printf ("%d\n", env->counter);

    return 0;
}
