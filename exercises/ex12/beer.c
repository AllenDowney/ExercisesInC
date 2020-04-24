/* Example code from Head First C Chapter 12

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void error(char* msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int beers = 2000000;

void* drink_lots()
{
    for (int i = 0; i < 100000; i++) {
        beers = beers - 1;
    }
    printf("beers = %i\n", beers);
    return NULL;
}

pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;

void* drink_safely()
{
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&beers_lock);
        beers = beers - 1;
        pthread_mutex_unlock(&beers_lock);
    }
    printf("beers = %i\n", beers);
    return NULL;
}

void* drink_alone()
{
    pthread_mutex_lock(&beers_lock);
    for (int i = 0; i < 100000; i++) {
        beers = beers - 1;
    }
    pthread_mutex_unlock(&beers_lock);
    printf("beers = %i\n", beers);
    return NULL;
}

int main()
{
    pthread_t threads[20];
    int t;

    printf("%i bottles of beer on the wall\n", beers);
    printf("%i bottles of beer\n", beers);

    for (t = 0; t < 20; t++) {
        pthread_create(&threads[t], NULL, drink_lots, NULL);
    }

    void* result;
    for (t = 0; t < 20; t++) {
        pthread_join(threads[t], &result);
    }
    printf("There are now %i bottles of beer on the wall\n", beers);
    return 0;
}
