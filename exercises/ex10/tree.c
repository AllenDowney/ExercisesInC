/* Example from

https://www.geeksforgeeks.org/binary-tree-set-1-introduction/

1) Draw a stack diagram that shows the state of main before calling
   rotate_right()

2) Draw a stack diagram that shows the state of main after calling
   rotate_right()

3) Fill in the body of rotate_left() and test it.

*/

#include <stdio.h>
#include <stdlib.h>


struct node
{
    int data;
    struct node* left;
    struct node* right;
};

/* newNode() allocates a new node with the given data and NULL left and
right pointers. */
struct node* newNode(int data)
{
    // Allocate memory for new node
    struct node* node = (struct node*)malloc(sizeof(struct node));

    // Assign data to this node
    node->data = data;

    // Initialize left and right children as NULL
    node->left = NULL;
    node->right = NULL;
    return(node);
}

/* Print the data in the tree in in-order.
*/
void print_tree(struct node* root) {
    if (root == NULL) return;
    print_tree(root->left);
    printf("%d ", root->data);
    print_tree(root->right);
}

int COUNT = 10;

// Function to print binary tree in 2D
// It does reverse inorder traversal
// From https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void print2D(struct node* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2D(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    // Process left child
    print2D(root->left, space);
}


/* Rotates the tree around the given node.

root: root of the tree to rotate

returns: pointer to the new root
*/
struct node *rotate_right(struct node* root) {
    struct node* pivot = root->left;
    root->left = pivot->right;
    pivot->right = root;
    return pivot;
}


struct node *rotate_left(struct node* root) {
    // TODO: fill this in
    // See
}


int main()
{
    /*create root*/
    struct node *root = newNode(5);

    root->left = newNode(3);
    root->right = newNode(7);

    root->left->left = newNode(2);
    root->left->right = newNode(4);

    print2D(root, 0);
    printf("-----\n");

    root = rotate_right(root);
    print2D(root, 0);

    return 0;
}
