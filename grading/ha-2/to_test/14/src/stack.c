//
// Created by George Watson on 31/05/2018.
// Forked from puzankova
//

#include "stack.h"

// the stack size is 50 elements
static const unsigned char STACK_MAX = 50;
// current size
static unsigned char size = 0;

struct Node
{
    double value;
    struct Node* next;
    struct Node* prev;

};

struct Node *stack = NULL; // it is your stack to work with it

int push(double value)
{
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the stack
    //  2 - other

    // not enough free space in stack
    if (size == STACK_MAX)
        return 1;

    // allocate memory for node
    struct Node* curr = malloc(sizeof(struct Node));

    if (curr == NULL)
        // special case of __malloc__()
        return 2;

    if (size > 0) {
        // assign prev of new element
        curr->prev = stack;
        // assign next from prev element
        stack->next = curr;
    }
    // assign current to stack
    stack = curr;

    // set prev and next as null
    if (!size) {
        stack->next = NULL;
        stack->prev = NULL;
    }

    // assign value to stack
    stack->value = value;
    // increment size
    size++;
    return 0;
}

double pop()
{
    // returns top value and delete it from stack
    // if stack is empty returns -infinity and print error message to the screen

    // if stack empty
    if (size == 0) {
        printf("Error in function pop(): no elements in the stack.\n");
        return -INF;
    }
    size--;
    // save stack value
    double temp = stack->value;
    // save node for freeing space
    struct Node* _temp = stack;
    // rearrange elements
    if (!size)
        stack = NULL;
    else {
        stack = stack->prev;
        stack->next = NULL;
    }
    /*
     * Free unused variables (node)
     * Undefined behaviour if _temp somehow
     * was not allocated by malloc.
     */
    free(_temp);

    return temp;
}

double pick()
{
    // just returns the top value
    // if stack is empty returns -infinity and print error message to the screen

    // if stack empty
    if (size == 0) {
        printf("Error in function pop(): no elements in the stack.\n");
        return -INF;
    }

    return stack->value;
}