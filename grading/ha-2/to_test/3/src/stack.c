//
// Created by puzankova 30.05.18
//

#include <stdint.h>
#include "stack.h"

#define MAX_STACK_SIZE 50

struct Node {
    double value;
    struct Node *next;
    struct Node *prev;

};

struct Node *stack = NULL; // it is your stack to work with it
static int size_of_the_stack = 0;

int push(double value) {
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the stack
    //  2 - other

    // the stack size is 50 elements

    //We need to check if the size of the stack is already MAX_STACK_SIZE
    if (size_of_the_stack >= MAX_STACK_SIZE) {
        return 1;
    } else {
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

        if (new_node==NULL) {
            return 2;
        }
        new_node->value = value;
        new_node->prev = NULL;
        new_node->next = NULL;

        if (stack == NULL) {
            stack = new_node;
        } else {
            struct Node *old = stack;

            stack = new_node;
            stack->next = old;
            old->prev = new_node;
        }

        if (stack->value != value) {
            return 2;
        }

        ++size_of_the_stack;
        return 0;
    }
    return 2;
}

double pop() {
    // returns top value and delete it from stack
    // if stack is empty returns -infinity and print error message to the screen
    if (stack == NULL) {
        printf("StackUnderflow: STACK IS EMPTY\n");
        return -INFINITY;
    } else {
        double value_to_return = stack->value;
        struct Node *old_node = stack;

        stack = stack->next;

        if (stack != NULL) {
            stack->prev = NULL;
        }

        free(old_node);
        --size_of_the_stack;
        return value_to_return;
    }

}

double pick() {
    // just returns the top value
    // if stack is empty returns -infinity and print error message to the screen
    if (stack == NULL) {
        printf("StackUnderflow: STACK IS EMPTY\n");
        return -INFINITY;
    } else {
        return stack->value;
    }
}