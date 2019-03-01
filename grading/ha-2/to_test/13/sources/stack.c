#include "../headers/stack.h"
#include "../headers/node.h"
#include <stdlib.h>

STACK * const create_stack() {
	STACK * stack = (STACK*) malloc(sizeof(STACK));
	stack->size = 0;
	stack->top = NULL;
	return stack;
}

void stack_put(STACK *stack, int val) {
	NODE* node = create_node();
	node->value = val;

	if (stack->top == NULL) stack->top = node;
	else {
		stack->top->next = node;
		node->previous = stack->top;
		stack->top = node;
	}

	stack->size++;
}

int stack_pull(STACK *stack) {
	int val = stack->top->value;
	NODE* node = stack->top;

	stack->top = stack->top->previous;
	if (stack->top != NULL) stack->top->next = NULL;
	delete_node(node);

	stack->size--;

	return val;
}

int stack_peek(STACK *stack) {
	return stack->top->value;
}

int stack_size(STACK *stack) {
	return stack->size;
}

void delete_stack(STACK* stack) {
	for (int i = stack->size; i > 0; i--) stack_pull(stack);
	free(stack);
}
