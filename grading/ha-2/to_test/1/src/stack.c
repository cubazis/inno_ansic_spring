//
// Created by puzankova 30.05.18
//

#include "stack.h"
#include <math.h>

#define MIN_SIZE 0
#define MAX_SIZE 50

static int count = 0;

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
	
	// the stack size is 50 elements
	
	if (count == MAX_SIZE) {
		printf("%s\n", "The stack is full.");
		return 1;
	}
	else if (count == MIN_SIZE) {
		stack = malloc(sizeof(struct Node));
		stack->prev = NULL;
		stack->next = NULL;
		stack->value = value;
		++count;
	}
	else {
		struct Node *temp = malloc(sizeof(struct Node));
		temp->value = value;
		temp->next = NULL;
		temp->prev = stack;
		stack->next = temp;
		stack = temp;
		++count;
	}
	if (stack->value != value || count < 0 || count > 50)
	return 2;
	return 0;
}
 
double pop()
{
	// returns top value and delete it from stack
	// if stack is empty returns -infinity and print error message to the screen
	if (count == MIN_SIZE) {
		printf("%s\n", "The stack is empty.");
		return -INFINITY;
	}
	double value = stack->value;
	if (count == MIN_SIZE + 1) {
	    free(stack);
	    stack = NULL;
	}
	else {
        stack = stack->prev;
        free(stack->next);
        stack->next = NULL;
	}
	--count;
    return value;
}

double pick()
{
	// just returns the top value
	// if stack is empty returns -infinity and print error message to the screen

	if (count == MIN_SIZE) {
		printf("%s\n", "The stack is empty.");
		return -INFINITY;
	}
	else
		return stack->value;
}
