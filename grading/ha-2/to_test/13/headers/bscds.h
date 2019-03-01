#ifndef LAB_1_BSCDS_H
#define LAB_1_BSCDS_H

typedef struct Node {
	struct Node *next, *previous;
	int value;
} NODE;

typedef struct PQNode {
	int value, priority;
} PQ_NODE;

typedef struct Stack {
	NODE* top;
	int size;
} STACK;

typedef struct PriorityQueue {
	PQ_NODE ** heap;
	int size, max_size;
} PQ;

#endif //LAB_1_BSCDS_H
