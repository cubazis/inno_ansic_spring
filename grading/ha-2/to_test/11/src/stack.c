#include <math.h>
#include "stack.h"

struct Node {
    double value;
    struct Node *next;
    struct Node *prev;
};

const int CAPACITY = 50;
int size = 0;
struct Node *stack = NULL; // it is your stack to work with it

int push(double value) {
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the stack
    //  2 - other

    // the stack size is 50 elements
    if (stack == NULL) {
        stack = (struct Node *) malloc(sizeof(struct Node));
        size = 1;
    } else {
        if (size >= CAPACITY)
            return 1;
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
        new_node->next = stack;
        stack->prev = new_node;
        stack = new_node;
        size++;
    }
    stack->value = value;
    return 0;
}

double pop() {
    // returns top value and delete it from stack
    // if stack is empty returns -infinity and print error message to the screen
    if (size == 0) {
        printf("Stack is empty!\n");
        return -INFINITY;
    }
    double ret_val = stack->value;
    void *old_node_ptr = stack;
    stack = stack->next;
    size--;
    free(old_node_ptr);
    return ret_val;
}

double pick() {
    // just returns the top value
    // if stack is empty returns -infinity and print error message to the screen
    if (size == 0) {
        printf("Stack is empty!\n");
        return -INFINITY;
    }
    return stack->value;
}
