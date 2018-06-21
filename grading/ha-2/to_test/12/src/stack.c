//
// Template created by puzankova 30.05.18
// Implemented by Alexander Trushin (Golf Team)
//

#include <sched.h>
#include "stack.h"
#include "limits.h"

struct StackNode{
	double value;
	struct StackNode* next;
};

typedef struct{
	struct StackNode* head;
	unsigned int size;
} Stack ;

Stack* stack = NULL; // it is your stack to work with it

int create_stack() {
	stack = (Stack*) malloc(sizeof(Stack*));
	stack->size = 0;
	return 0;
}

int push(double value)
{
	if (stack->size < 50) {
		struct StackNode* pointer = (struct StackNode*) malloc(sizeof(struct StackNode));
		pointer->next = stack->head;
		pointer->value = value;

		stack->head = pointer;
		stack->size++;
		return 0;
	} else return 1;
}
 
double pop()
{
	if (stack->size != 0) {
		struct StackNode* pointer = stack->head;
        double result = stack->head->value;
        stack->head = stack->head->next;
		free(pointer);

		stack->size--;
		return result;
	} else {
//		printf("Stack is empty\n");
		return INT_MIN;
	}
}

double pick()
{
	if (stack->size != 0) {
		return stack->head->value;
	} else {
//		printf("Stack is empty\n");
		return INT_MIN;
	}
}

int print_stack()
{
	printf("----Stack----\n");
	struct StackNode* pointer = stack->head;
	for (int i = 0; i < stack->size; ++i) {
		printf("[%lf]\n", pointer->value);
		pointer = pointer->next;
	}
	return 0;
}

int delete_stack() {
	struct StackNode* current = stack->head;
	struct StackNode* next = NULL;

//  --Nodes Removing--
	for (int i = 0; i < stack->size; ++i) {
		next = current->next;
		free(current);
		current = next;
	}

//  --Stack Removing--
	free(stack);
	return 0;
}






