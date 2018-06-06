#include "stack.h"
#include "math.h"

struct Node {
    double value;
    struct Node *next;
    struct Node *prev;

};

int StackSize = 50;                                                     // Initialization of the stack size
int curSize = 0;                                                        // Current size of stack (at the beginning
// it's zero)
struct Node *head = NULL;                                               // Pointer to the head element of the stack

int push(double value) {
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the stack
    //  2 - other

    // the stack size is 50 elements

    struct Node *node = (struct Node *) malloc(sizeof(struct Node));    //Allocating space in the memory for node



    if (node == NULL) {
        return 2;
    }
    if (curSize == StackSize) {
        return 1;
    }
    node->value = value;                                                //
    node->next = head;                                                  //
    node->prev = NULL;                                                  //
    // Changing pointers
    if (head != NULL) {                                                 //
        head->prev = node;                                              //
    }                                                                   //

    if (node->value != value)
    {
        return 2;
    }

    head = node;                                                        // New pointer to the head of the stack
    curSize++;                                                          // New size of the stack

    return 0;
}

double pop() {
    // returns top value and delete it from stack
    // if stack is empty returns -infinity and print error message to the screen
    if (curSize == 0) {
        fprintf(stderr, "Stack is empty\n");
        return -INFINITY;
    }

    struct Node *tmp = head;
    double element = head->value;
    head = head->next;
    if (curSize != 1) {
        head->prev = NULL;
    }
    free(tmp);
    curSize--;
    return element;
}

double pick() {
    // just returns the top value
    // if stack is empty returns -infinity and print error message to the screen
    if (curSize == 0) {
        fprintf(stderr, "Stack is empty\n");
        return -INFINITY;
    }
    return head->value;
}

struct Node *stack = NULL; // it is your stack to work with it