/* Example code for Think OS.

Copyright 2015 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

// QUEUE: incomplete struct definition here because different
// implementations have different fields.
typedef struct queue Queue;

Queue *make_queue(int length);
int queue_empty(Queue *queue);
int queue_full(Queue *queue);
void queue_push(Queue *queue, int item) ;
int queue_pop(Queue *queue);
