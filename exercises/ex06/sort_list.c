/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
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


/* Counts the Nodes in a list.
*
* list: pointer to pointer to Node
* returns: number of nodes
*/
int list_length(Node **list) {
    Node *current = *list;

    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


/* Puts the Nodes in a list into an array.
 *
 * list: pointer to pointer to Node
 * returns: newly-allocated array of pointer to Node
 */
 Node **list_to_array(Node **list, int n) {
     Node *current = *list;
     Node **array = malloc(n * sizeof(Node *));

     for (int i=0; i<n; i++) {
         array[i] = current;
         current = current->next;
     }
     return array;
 }

 /* Links the Nodes in an array up into a list.
  *
  * array: array of pointer to Node
  * returns: pointer to the first Node
  */
 Node *array_to_list(Node **array, int n) {
     if (n == 0) {
         return NULL;
     }
     for (int i=0; i<n-1; i++) {
         array[i]->next = array[i+1];
     }
     array[n-1]->next = NULL;
     return array[0];
}

/* Compare Nodes by value.

Comparator function for qsort.
a: pointer to pointer to Node
b: pointer to pointer to Node

returns: >0 if a > b
         <0 if a < b
          0 if a==b
*/
int compare_nodes(const void* a, const void* b) {
    // FILL THIS IN!
    return 0;
}

int main() {
    // make the list
    Node *head = make_node(4, NULL);
    head->next = make_node(1, NULL);
    head->next->next = make_node(3, NULL);
    head->next->next->next = make_node(2, NULL);

    // print it
    Node **list = &head;
    print_list(list);

    // count the length
    int length = list_length(list);
    printf("%d\n", length);

    // convert to array
    Node **array = list_to_array(list, length);

    // sort the array
    qsort(array, length, sizeof(Node *), compare_nodes);

    // link the nodes back up
    Node *sorted = array_to_list(array, length);

    // print the list again
    list = &sorted;
    print_list(list);
}
