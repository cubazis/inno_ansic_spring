//
// Created by puzankova 30.05.18
//

#include <math.h>
#include "stack.h"

struct Node 
{
	double value;
	struct Node* next;
	struct Node* prev;

};

static int len = 0;
struct Node *stack = NULL; // it is your stack to work with it

int push(double value)
{
	// return the exit code:
	//	0 - success
	//	1 - not enough free space in the stack
	//  2 - other
	
	// the stack size is 50 elements
    int real_len = 0;
    struct Node* current = stack;
//    printf("LEN: %d\n", len);
    while (current != NULL){
        current = (*current).prev;
        ++real_len;
    }

    //printf("%d %d\n", len, real_len);

    if (real_len != len){
        return (2);
    }

	if (len == 50){
		return(1);
	} else if (len > 50 || len < 0 || (stack != NULL && len == 0) || (stack == NULL && len != 0)){
        return (2);
	}

	if (stack == NULL)
    {
        struct Node* buff = (struct Node*)malloc(sizeof(struct Node));
        if (buff == NULL)
            return (2);
        stack = buff;
        (*stack).value = value;
        (*stack).next = NULL;
        (*stack).prev = NULL;
        ++len;
        return (0);
    }
	struct Node* prev = stack;
    struct Node* buff = (struct Node*)malloc(sizeof(struct Node));
    if (buff == NULL)
        return (2);
    stack = buff;
    (*prev).next = stack;
    (*stack).value = value;
	(*stack).prev = prev;
    (*stack).next = NULL;
    if (stack->prev == stack)
    {
        printf("***PREV = CURRENT!!!***\n");
        return (2);
    }
	++len;
	return(0);
}
 
double pop()
{
	// returns top value and delete it from stack
	// if stack is empty returns -infinity and print error message to the screen
    if (stack == NULL){
        printf("***ERROR : Nothing to pop!!!***");
        return (-INFINITY);
    }
    struct Node* prev = (*stack).prev;
    double val = (*stack).value;
    free(stack);
    stack = prev;
    if (prev != NULL){
        (*prev).next = NULL;
    }
    --len;
    return (val);
}

double pick()
{
	// just returns the top value
	// if stack is empty returns -infinity and print error message to the screen

    if (stack != NULL) {
        double val = stack -> value;
        return (val);
    }
    printf("***ERROR : Nothing to pick!!!***\n");
    return (-INFINITY);
}

