//
// Created by puzankova 30.05.18
//

#include "priority_queue.h"

struct Node 
{
	double value;
	int key;
	struct Node* next;
	struct Node* prev;

};

int insert(double value, int key)
{
	// return the exit code:
	//	0 - success
	//	1 - not enough free space in the queue
	//  2 - other
	
	// the queue size is 100 elements

	/* YOUR CODE */
}

double extract_min()
{
	// returns the min value and delete it from queue
	// if queue is empty returns -infinity and print error message to the screen
	/* YOUR CODE */
}

struct Node *queue = NULL; // it is your queue to work with it