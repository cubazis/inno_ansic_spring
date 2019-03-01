//
// Created by KILO 1.06.18
//
#include "stack.h"


struct Node {
    double value;
    struct Node *next;
    struct Node *prev;

};

struct Node *stack = NULL; // it is your stack to work with it


int push(double value) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next=NULL;

    if (stack == NULL) {
        stack = newNode;
        stack->prev=NULL;
        return 0;
    } else {
        struct Node *p = stack;
        int i;
        for (i = 1; i < 50 && p->next != NULL; i++, p = p->next);
        if (i == 50)
            return 1;
        else {
            p->next = newNode;
            newNode->prev = p;
            return 0;
        }

    }
    return 2;

    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the stack
    //  2 - other

    // the stack size is 50 elements

    /* YOUR CODE */
}

double pop() {

    struct Node *STACK = stack;
    if (stack == NULL) {
        printf("%s\n", "The stack is empty");
        return -INFINITY;
    } else {
        struct Node *p = stack;
        while (p->next != NULL)
            p = p->next;

        double res = p->value;
        if (p->prev != NULL) {
            p = p->prev;
            free(p->next);
            p->next = NULL;
        } else {
            free(p);
            stack = NULL;
        }
        return res;
    }
    // returns top value and delete it from stack
    // if stack is empty returns -infinity and print error message to the screen
    /* YOUR CODE */
}

double pick() {
    struct Node *STACK = stack;

    if (stack == NULL) {
        printf("%s\n", "The stack is empty");
        return -INFINITY;
    } else {
        struct Node *p = stack;
        while (p->next != NULL)
            p = p->next;
        return p->value;
    }
    // just returns the top value
    // if stack is empty returns -infinity and print error message to the screen
    /* YOUR CODE */
}
