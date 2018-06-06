#include <math.h>
#include "priority_queue.h"

struct Node 
{
	double value;
	int key;
	struct Node* next;
	struct Node* prev;

};

int size = 0; // current size of queue
struct Node *queue = NULL; // it is your queue to work with it

int insert(double value, int key)
{
	// return the exit code:
	//	0 - success
	//	1 - not enough free space in the queue
	//  2 - other
	
	// the queue size is 100 elements

	if (size == 100)
    {
        return 1;
    }

    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));

	if (newNode == NULL)
    {
        return 2;
    }

	newNode->key = key;
	newNode->value = value;
	newNode->next = NULL;
	newNode->prev = NULL;

    if(size == 0)
    {
        queue = newNode;
    }
    else
    {
        struct Node *currentNode = queue;
        while(currentNode->key <= newNode->key && currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }

        if (currentNode->key <= newNode->key)
        {
            if (currentNode->next != NULL)
            {
                currentNode->next->prev = newNode;
            }
            newNode->next = currentNode->next;
            newNode->prev = currentNode;
            currentNode->next = newNode;
        }
        else
        {
            if (currentNode->prev != NULL)
            {
                currentNode->prev->next = newNode;
            }
            else
            {
                queue = newNode;
            }
            newNode->prev = currentNode->prev;
            newNode->next = currentNode;
            currentNode->prev = newNode;
        }

    }

    if (newNode->value != value)
    {
        return 2;
    }

    size++;
    return 0;

}

double extract_min()
{
	// returns the min value and delete it from queue
	// if queue is empty returns -infinity and print error message to the screen
    if (size == 0)
    {
        fprintf(stderr, "Queue is empty\n");
        return -INFINITY;
    }

    struct Node* minNode = queue;
    double value = minNode->value;
    queue = minNode->next;
    if (queue != NULL)
    {
        queue->prev = NULL;
    }
    free(minNode);
    size--;
    return value;
}