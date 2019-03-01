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

struct Node *stack = NULL; // it is your stack to work with it

int push(double value)
{
	// return the exit code:
	//	0 - success
	//	1 - not enough free space in the stack
	//  2 - other

	// the stack size is 50 elements

	/* YOUR CODE */
	struct Node* newNode = malloc(sizeof(struct Node));     //create new node
	newNode -> value = value;
	newNode -> next = NULL;
	newNode -> prev = NULL;


	if(stack == NULL){                     //if stack is empty, place new node in it
		stack = newNode;
        return 0;
	} else {
		int size = stack_size();           //else place node if size less than 50

		if(size>=50){
            printf("ERROR: CANNOT PUT %f IN STACK - IT IS FULL!\n", value);
			return 1;
		}
		else {
			stack->prev = newNode;
			newNode -> next = stack;
			stack = newNode;
			return 0;

		}
	}
	return 2;
}

double pop()
{
	// returns top value and delete it from stack
	// if stack is empty returns -infinity and print error message to the screen
	/* YOUR CODE */
	if(stack == NULL){
		printf("ERROR: POPPING FROM EMPTY STACK!\n");
		return -INFINITY;
	} else {
        double value = stack->value;
        struct Node* trash = stack;
        stack = stack->next;
        free(trash);
        if(stack != NULL) stack->prev = NULL;
        return value;
    }

}

double peek()
{
	// just returns the top value
	// if stack is empty returns -infinity and print error message to the screen
	/* YOUR CODE */
    if (stack == NULL) return -INFINITY;
    else return stack->value;
}


int stack_size(){
    //return the number of elements in the stack
    int size = 0;
    struct Node* top = (stack);
        while(top != NULL){
            (size)++;
            top = (top) -> next;
        }
    return size;
}
