//
// Created by puzankova 30.05.18
//

#include <math.h>
#include "priority_queue.h"

struct Node
{
	double value;
	int key;
	struct Node* next;
	struct Node* prev;

};

int size = 0;

int insert(double value, int key) {
	// return the exit code:
	// 0 - success
	// 1 - not enough free space in the queue
	//  2 - other

	// the queue size is 100 elements

	/* YOUR CODE */

	extern struct Node *queue;
	extern int size;

	if (size == 0) {

		struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
		new_node->value = value;
		new_node->key = key;
		new_node->next = NULL;
		new_node->prev = NULL;

		queue = new_node;
		size++;
		return 0;
	}

	else if (size == 100) {
		printf("%s", "Not enough free space in the queue");
		return 1;
	}

	else {
		struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
		new_node->value = value;
		new_node->key = key;

		if (key < queue->key) {
			new_node->prev = queue;
			new_node->next = NULL;
			queue->next = new_node;
			queue = new_node;
		}
		else {
			struct Node *t;
			t = queue;

			while (new_node->key >= t->key) {
				if (t->prev != NULL) {
					t = t->prev;
				}
				else {
					break;
				}
			}

			if (t->prev != NULL) {
				struct Node* a = t->next;
				struct Node* b = t;

				new_node->next = a;
				new_node->prev = b;
				t->next->prev = new_node;
				t->next = new_node;
			}
			else {
				t->prev = new_node;
				new_node->next = t;
				new_node->prev = NULL;
			}

		}

		size++;
		return 0;
	}
}


double extract_min()
{
	// returns the min value and delete it from queue
	// if queue is empty returns -infinity and print error message to the screen
	/* YOUR CODE */
    extern struct Node *queue;
    if (size == 0){
        printf("%s", "ERROR, queue is empty!");
        return -INFINITY;
    }
    else{
        double minValue = queue->value;
        queue = queue->prev;
        size--;
        return minValue;
    }

}

struct Node *queue = NULL; // it is your queue to work with it

