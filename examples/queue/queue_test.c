#include <assert.h>
#include "queue.h"

void queue_test() {
    int i;
    int item;
    int length = 128;

    Queue *queue = make_queue(length);
    assert(queue_empty(queue));
    for (i=0; i<length; i++) {
        queue_push(queue, i);
    }
    assert(queue_full(queue));
    for (i=0; i<10; i++) {
        item = queue_pop(queue);
        assert(i == item);
    }
    assert(!queue_empty(queue));
    assert(!queue_full(queue));
    for (i=0; i<10; i++) {
        queue_push(queue, i);
    }
    assert(queue_full(queue));
    for (i=0; i<10; i++) {
        item = queue_pop(queue);
    }
    assert(item == 19);
}

int main() {
    queue_test();
    return 0;
}
