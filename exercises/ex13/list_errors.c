/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct node {
    int val;
    struct node * next;
} Node;

Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

int pop(Node **head) {
    int retval;
    Node *next_node;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    *head = next_node;

    return retval;
}

// Add a new element to the beginning of the list.
void push(Node **head, int val) {
    Node *new_node = make_node(val, *head);
    *head = new_node;
}

// Remove the first element with the given value; return the number
// of nodes removed.
int remove_by_value(Node **head, int val) {
    Node *node = *head;
    Node *victim;

    if (node == NULL) {
        return 0;
    }

    if (node->val == val) {
        pop(head);
        return 1;
    }

    for(; node->next != NULL; node = node->next) {
        if (node->next->val == val) {
            victim = node->next;
            node->next = victim->next;
            return 1;
        }
    }
    return 0;
}

// Reverse the elements of the list without allocating new nodes.
void reverse(Node **head) {
    Node *node = *head;
    Node *next, *temp;

    if (node == NULL || node->next == NULL) {
        return;
    }

    next = node->next;
    node->next = NULL;

    while (next != NULL) {
        temp = next->next;
        next->next = node;
        node = next;
        next = temp;
    }
    *head = node;
}

// Adds a new element to the list before the indexed element.
// Index 0 adds an element to the beginning.  Index 1 adds an
// element between the first and second elements.
// Returns 0 if successful, -1 if the index is out of range.
int insert_by_index(Node **head, int val, int index) {
    int i;
    Node *node = *head;

    if (index == 0) {
        push(head, val);
        return 0;
    }

    for (i=0; i<index-1; i++) {
        if (node == NULL) return -1;
        node = node->next;
    }
    if (node == NULL) return -1;
    node->next = make_node(val, node->next);
    return 0;
}

// Makes a mysterious data structure.
Node *make_something() {
    Node *node1 = make_node(1, NULL);
    Node *node2 = make_node(2, NULL);
    Node *node3 = make_node(3, NULL);

    int val = pop(&node1);
    push(&node2, val);
    node3->next = node2;

    return node3;
}

int main() {
    // make a list of even numbers
    Node *test_list = make_node(2, NULL);
    test_list->next = make_node(4, NULL);
    test_list->next->next = make_node(6, NULL);

    // insert the odd numbers
    insert_by_index(&test_list, 1, 0);
    insert_by_index(&test_list, 3, 2);
    insert_by_index(&test_list, 5, 4);
    insert_by_index(&test_list, 7, 6);

    // this index is out of bounds; should return -1
    int res = insert_by_index(&test_list, 9, 8);
    assert(res == -1);

    printf("test_list\n");
    print_list(test_list);

    // make an empty list
    printf("empty\n");
    Node *empty = NULL;

    // add an element to the empty list
    insert_by_index(&empty, 1, 0);
    print_list(empty);

    Node *something = make_something();
    free(something);

    return 0;
}
