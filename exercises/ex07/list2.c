/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2018 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;


/* Makes a new node structure.
*
* val: value to store in the node.
* next: pointer to the next node
*
* returns: pointer to a new node
*/
Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

/* Prints the values in a list.
*
* list: pointer to first node
*/
void print_list(Node *list) {
    Node *current = list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}

/* Removes the first element of a list, stores the value.
*
* list: pointer to first node
  value_p: location to store the popped value
*
* returns: head of modified list
*/
Node *pop(Node *list, int *value_p) {
    // FILL THIS IN!
    return NULL;
}

/* Swaps the first two elements of the list.
*
* list: pointer to first node
  value_p: location to store the popped value
*
* returns: head of modified list
*/
Node *swap(Node *list) {
    // FILL THIS IN!
    return NULL;
}

/* Adds a new element to the beginning of the list.
*
* list: pointer to first node
* value: value to add

* returns: address of modified list
*/
Node *push(Node *list, int value) {
    Node *head = list;
    Node *new_head = make_node(value, head);
    return new_head;
}

int main() {
    Node *list = make_node(1, NULL);
    list->next = make_node(2, NULL);
    list->next->next = make_node(3, NULL);

    print_list(list);

    list = push(list, 0);
    print_list(list);

    int value;
    list = pop(list, &value);
    printf("popped value = %d\n", value);
    print_list(list);

    list = swap(list);
    print_list(list);
}
