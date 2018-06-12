//
// Created by George Watson on 01/06/2018.
// Forked from puzankova
//

#include "priority_queue.h"

// the queue size is 50 elements
static const unsigned char QUEUE_MAX = 100;
// current size
static unsigned char size = 0;


struct Node
{
    double value;
    int key;
    struct Node* next;
    struct Node* prev;

};

struct Node *queue = NULL; // it is your queue to work with it


int insert(double value, int key)
{
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the queue
    //  2 - other

    // the queue size is 100 elements

    // if max size exceeded
    if (size == QUEUE_MAX)
        return 1;

    struct Node* curr = malloc(sizeof(struct Node));

    if (curr == NULL)
        // special case of __malloc__()
        return 2;

    curr->key = key;
    curr->value = value;

    if (!size) {
        queue = curr;
        queue->next = NULL;
        queue->prev = NULL;
    }
    else {
        curr->prev = queue;
        queue->next = curr;
        queue = curr;
        queue->next = NULL;

        // swap before keys are going to be accurate
        while (curr->prev != NULL && curr->key >= curr->prev->key) {
            // swap items
            int k1 = curr->prev->key;
            double d1 = curr->prev->value;
            curr->prev->key = curr->key;
            curr->prev->value = curr->value;
            curr->key = k1;
            curr->value = d1;
            // sett curr to temp (prev value)
            curr = curr->prev;
        }
    }

    size++;
    return 0;
}

double extract_min()
{
    // returns the min value and delete it from queue
    // if queue is empty returns -infinity and print error message to the screen

    // prints -INF if queue is empty
    if (!size) {
        printf("Error in function extract_min(): no elements in the queue.\n");
        return -INF;
    }
    // else returns min value and deletes it
    double temp = queue->value;
    struct Node* _temp = queue;

    // decrease size
    size--;
    if (!size)
        queue = NULL;
    else {
        queue = queue->prev;
        queue->next = NULL;
    }
    /*
     * Free unused variables (node)
     * Undefined behaviour if _temp somehow
     * was not allocated by malloc.
     */
    free(_temp);

    return temp;
}