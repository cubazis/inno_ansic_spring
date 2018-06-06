//
// Created by Максим on 31.05.2018.
//

#include "stack.h"
#include <float.h>

#define MAX_SIZE 50 // stack's max_size

struct Node
{
    double value;
    struct Node* next;
    struct Node* prev;

};

struct Node *stack = NULL; // it is your stack to work with it
int size = 0; // current size of the stack

int push(double value)
{
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the stack
    //  2 - other

    // the stack size is 50 elements

    if (size < MAX_SIZE) {
        if (!stack) {
            stack = malloc(sizeof(struct Node));
            if (!stack) {
                return 2;
            }
            stack->prev = NULL;
        }
        else {
            stack->next = malloc(sizeof(struct Node));
            if (!(stack->next)) {
                return 2;
            }
            stack->next->prev = stack;
            stack = stack->next;
        }
        stack->value = value;
        stack->next = NULL;
        ++size;
        return 0;
    }
    return 1;
}

double pop()
{
    // returns top value and delete it from stack
    // if stack is empty returns -infinity and print error message to the screen

    if (size > 0) {
        double value = stack->value;
        struct Node *temp_ptr = stack;
        stack = stack->prev;
        free(temp_ptr);
        temp_ptr = NULL;
        if (stack) {
            stack->next = NULL;
        }
        --size;
        return value;
    }
    else {
        printf("Failed: an attempt to pop from an empty stack\n");
        return -DBL_MAX; // return -infinity
    }
}

double pick()
{
    // just returns the top value
    // if stack is empty returns -infinity and print error message to the screen

    if (size > 0) {
        return stack->value;
    }
    else {
        printf("Failed: an attempt to pick from an empty stack\n");
        return -DBL_MAX; // return -infinity
    };
}