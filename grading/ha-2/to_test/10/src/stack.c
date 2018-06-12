//
// Created by madina on 31.05.18.
//


#include "stack.h"
#include <check.h>

struct Node {
	double value;
	struct Node *next;
	struct Node *prev;
};

size_t size = 0;
struct Node *stack = NULL; // it is your stack to work with it

int push(double value) {
	// return the exit code:
	//	0 - success
	//	1 - not enough free space in the stack
	//  2 - other

	// the stack size is 50 elements

	/* YOUR CODE */

	if (size >= 50) {
		return 1;
	}

	if (!stack) {
		stack = (struct Node *) malloc(sizeof(struct Node));
		if (!stack) {
			return 2;
		}
		stack->value = value;
		stack->prev = NULL;
		stack->next = NULL;
		size++;

		return 0;
	}

	struct Node *new = (struct Node *) malloc(sizeof(struct Node));
	if (!new) {
		return 2;
	}
	new->value = value;
	stack->next = new;
	new->prev = stack;
	new->next = NULL;
	stack = new;
	size++;

	return 0;
}

double pop() {
	// returns top value and delete it from stack
	// if stack is empty returns -infinity and print error message to the screen
	/* YOUR CODE */

	if (!stack) {
		fprintf(stderr, "Stack is empty, cannot pop the value.\n");
		return -INFINITY; // math.h contains infinity
	}

	double returnvalue = stack->value;

	struct Node *old = stack;
	stack = stack->prev;
	if (stack) {
		stack->next = NULL;
	}
	free(old);
	size--;

	return returnvalue;
}

double pick() {
	// just returns the top value
	// if stack is empty returns -infinity and print error message to the screen
	/* YOUR CODE */

	if (!stack) {
		fprintf(stderr, "Stack is empty, cannot pick the value.\n");
		return -INFINITY; // math.h contains infinity
	}

	return stack->value;
}

