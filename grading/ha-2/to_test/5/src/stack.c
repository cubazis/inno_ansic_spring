//
// Created by puzankova 30.05.18
//

#include <math.h>
#include "stack.h"
#define MAX_STACK_SIZE 50

static int size = 0;

struct Node
{
	double value;
	struct Node* next;
};

struct Node *stack = NULL;

int push(double value)
{
	// return the exit code:
	//	0 - success
	//	1 - not enough free space in the stack
	//  2 - other

	// the stack size is 50 elements

	if(size == MAX_STACK_SIZE) return 1;

	struct Node *a = malloc(sizeof(struct Node));
	a->next = stack;
	a->value = value;
	stack = a;
	size++;
	return 0;
}
 
double pop()
{
	// returns top value and delete it from stack
	// if stack is empty returns -infinity and print error message to the screen
	if(!stack) {
        printf("  _      ____   ____   _____ ______ _____  \n"
               " | |    / __ \\ / __ \\ / ____|  ____|  __ \\ \n"
               " | |   | |  | | |  | | (___ | |__  | |__) |\n"
               " | |   | |  | | |  | |\\___ \\|  __| |  _  / \n"
               " | |___| |__| | |__| |____) | |____| | \\ \\ \n"
               " |______\\____/ \\____/|_____/|______|_|  \\_\\\n");
        return -INFINITY;
    }
	else {
		double res = stack->value;
		struct Node *new_stack = stack->next;
		free(stack);
		stack = new_stack;
		size--;
		return res;
	}
}

double pick()
{
	// just returns the top value
	// if stack is empty returns -infinity and print error message to the screen
    if(!stack) {
        printf("  _      ____   ____   _____ ______ _____  \n"
               " | |    / __ \\ / __ \\ / ____|  ____|  __ \\ \n"
               " | |   | |  | | |  | | (___ | |__  | |__) |\n"
               " | |   | |  | | |  | |\\___ \\|  __| |  _  / \n"
               " | |___| |__| | |__| |____) | |____| | \\ \\ \n"
               " |______\\____/ \\____/|_____/|______|_|  \\_\\\n");
        return -INFINITY;
    } else
	    return stack->value;
}
