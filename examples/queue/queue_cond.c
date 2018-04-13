/* Example code for Think OS.

Copyright 2015 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include "utils.h"

// QUEUE

typedef struct {
    int *array;
    int length;
    int next_in;
    int next_out;
    Mutex *mutex;
    Cond *nonempty;
} Queue;

/* Create an empty queue.

length: maximum queue length
*/
Queue *make_queue(int length)
{
    Queue *queue = (Queue *)check_malloc(sizeof(Queue));

    // we have to add 1 because the implementation wastes one element
    queue->length = length + 1;
    queue->array = (int *)check_malloc(length * sizeof(int));
    queue->next_in = 0;
    queue->next_out = 0;
    queue->mutex = make_mutex();
    queue->nonempty = make_cond();
    return queue;
}

/* Add one and wrap.

Private function.
*/
int queue_incr(Queue *queue, int i)
{
    return (i+1) % queue->length;
}

/* Check whether the queue is empty.

    NOTE: you must hold the mutex to call this function.
*/
int queue_empty(Queue *queue)
{
    // queue is empty if next_in and next_out are the same
    int res = (queue->next_in == queue->next_out);
    return res;
}

/* Check whether the queue is full.

    NOTE: you must hold the mutex to call this function.
*/
int queue_full(Queue *queue)
{
    // queue is full if incrementing next_in lands on next_out
    int res = (queue_incr(queue, queue->next_in) == queue->next_out);
    return res;
}

/* Add an element to the queue.
*/
void queue_push(Queue *queue, int item) {
    mutex_lock(queue->mutex);
    if (queue_full(queue)) {
        mutex_unlock(queue->mutex);
        perror_exit("queue is full");
    }

    queue->array[queue->next_in] = item;
    queue->next_in = queue_incr(queue, queue->next_in);
    mutex_unlock(queue->mutex);
    cond_signal(queue->nonempty);
}

int queue_pop(Queue *queue) {
    mutex_lock(queue->mutex);
    while (queue_empty(queue)) {
        cond_wait(queue->nonempty, queue->mutex);
    }

    int item = queue->array[queue->next_out];
    queue->next_out = queue_incr(queue, queue->next_out);
    mutex_unlock(queue->mutex);
    return item;
}

