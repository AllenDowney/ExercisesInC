/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
* list: pointer to pointer to Node
*/
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
*
* list: pointer to pointer to Node
*
* returns: int or -1 if the list is empty
*/
int pop(Node **list) {
    int retval;
    Node *head = *list;

    if (head == NULL) {
        return -1;
    }

    Node *next_node = head->next;
    retval = head->val;
    free(head);
    *list = next_node;

    return retval;
}


/* Adds a new element to the beginning of the list.
*
* list: pointer to pointer to Node
* val: value to add
*/
void push(Node **list, int val) {
    Node *new_node = make_node(val, *list);
    *list = new_node;
}


/* Removes the first element with the given value
*
* Frees the removed node.
*
* list: pointer to pointer to Node
* val: value to remove
*
* returns: number of nodes removed
*/
int remove_by_value(Node **list, int val) {
    Node *node = *list;

    if (node == NULL) {
        return 0;
    }

    if (node->val == val) {
        pop(list);
        return 1;
    }

    for(; node->next != NULL; node = node->next) {
        if (node->next->val == val) {
            Node *victim = node->next;
            node->next = victim->next;
            free(victim);
            return 1;
        }
    }
    return 0;
}

/* Reverses the elements of the list.
*
* Does not allocate or free nodes.
*
* list: pointer to pointer to Node
*/
void reverse(Node **list) {
    Node *node = *list;
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
    *list = node;
}



/* Adds a new element to the list before the indexed element.

Index 0 adds an element to the beginning.
Index 1 adds an element between the first and second elements.

Returns 0 if successful, -1 if the index is out of range.
*/
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

/* Makes a mysterious data structure.
*/
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
    print_list(&test_list);

    // make an empty list
    printf("empty\n");
    Node *empty = NULL;

    // add an element to the empty list
    insert_by_index(&empty, 1, 0);
    print_list(&empty);

    Node *something = make_something();
    free(something);

    return 0;
}
