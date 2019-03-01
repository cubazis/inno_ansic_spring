//
// Created by madina on 31.05.18.
//


#include "priority_queue.h"
#include "math.h"

struct Node {
    double value;
    int key;
    struct Node *next;
    struct Node *prev;
};

struct Node *queue = NULL; // it is your queue to work with it

int size = 0;
char empty = 1;

void construct(struct Node *node) {
    if (node->prev != NULL && node->key < node->prev->key) {
        int temp_key = node->key;
        double temp_value = node->value;
        node->key = node->prev->key;
        node->value = node->prev->value;
        node->prev->value = temp_value;
        node->prev->key = temp_key;
        construct(node->prev);

    }
}

int insert(double value, int key) {
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the queue
    //  2 - other

    // the queue size is 100 elements

    /* YOUR CODE */

    if (size >= 100) {
        return 1;
    }

    if (!queue || size == 0) {
        queue = (struct Node *) malloc(sizeof(struct Node));
        if (!queue) {
            return 2;
        }
        queue->value = value;
        queue->key = key;
        queue->prev = NULL;
        queue->next = NULL;
        size++;
        empty = 0;
        return 0;
    }

    struct Node *new = (struct Node *) malloc(sizeof(struct Node));
    if (!new) {
        return 2;
    }
    new->value = value;
    new->key = key;
    queue->next = new;
    new->prev = queue;
    new->next = NULL;
    size++;
    queue = queue->next;

    construct(new);

    return 0;
}

double extract_min() {
    // returns the min value and delete it from queue
    // if queue is empty returns -infinity and print error message to the screen
    /* YOUR CODE */
    if (empty == 1) {
        printf("Error message! Queue is empty!\n");
        return INFINITY;
    }
    struct Node *temp = queue;
    while (temp->prev != NULL) {
        temp = temp->prev;
    }
    if (temp->next != NULL) {
        temp->next->prev = NULL;
    }
    size--;
    if (size == 0) {
        empty = 1;
    }
    double result = temp->value;
    free(temp);

    return result;
}