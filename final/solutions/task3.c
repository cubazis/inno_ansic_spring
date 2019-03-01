#include <stdio.h>
#include "stdlib.h"
#include <string.h>
typedef	struct _employee{
	char name[32];
	unsigned char age;
} Employee;

typedef	struct _node {
	void *data;
	struct _node *next;
} Node;

typedef	struct _linkedList {
	Node *head;
	Node *tail;
	Node *current;
} LinkedList;

typedef	LinkedList Stack;

void initializeList(LinkedList *list) {
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
}

void addHead(LinkedList	*list, void* data)	{
	Node *node = (Node*)	malloc(sizeof(Node));
	node->data = data;
	if (list->head == NULL)	{
		list->tail = node;
		node->next = NULL;
	}else{
		node->next = list->head;
	}
	list->head = node;
}

void initializeStack(Stack *stack){
	initializeList(stack);
}

void push(Stack *stack,	void* data)	{
	addHead(stack, data);
}

void *pop(Stack	*stack)	{
	Node *node = stack->head;
	if (node == NULL) {
		return NULL;
	} else if (node == stack->tail) {
		stack->head = stack->tail = NULL;
		void *data = node->data;
		free(node);
		return data;
	} else {
		stack->head = stack->head->next;
		void *data = node->data;
		free(node);
		return data;
	}
}

int main(){
	Employee *samuel = (Employee*) malloc(sizeof(Employee));
	strcpy(samuel->name, "Samuel");
	samuel->age = 32;
	Employee *sally	= (Employee*) malloc(sizeof(Employee));
	strcpy(sally->name, "Sally");
	sally->age = 28;
	Employee *susan	= (Employee*) malloc(sizeof(Employee));
	strcpy(susan->name, "Susan");
	susan->age = 45;
	Stack stack;
	initializeStack(&stack);
	push(&stack, samuel);
	push(&stack, sally);
	push(&stack, susan);
	Employee *employee;
	while((employee	= (Employee*) pop(&stack)) != NULL){
		printf("Popped	%s\n",	employee->name);
	}
}