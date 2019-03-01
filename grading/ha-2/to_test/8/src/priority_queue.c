//
// Created by bogdan on 6/1/18.
//

#include "priority_queue.h"

struct Node
{
    double value;
    int key;
    struct Node* next;
    struct Node* prev;

};

struct Node *queue = NULL; // it is your queue to work with it
int size = 0;

int insert(double value, int key)
{
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the queue
    //  2 - other

    // the queue size is 100 elements
    //struct Node* current = &queue;

    if (size == 100) {
        return 1;
    }

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return 2;
    }

    ++size;

    if (queue == NULL) {
        new_node -> prev = NULL;
        new_node -> next = NULL;
        new_node -> value = value;
        new_node -> key = key;

        queue = new_node;

        while (queue -> prev != NULL) {
            queue = queue -> prev;
        }

        return 0;

    } else while (queue -> key <= key) {

        if (queue -> next != NULL) {
            queue = queue -> next;
        } else {

            queue -> next = new_node;

            new_node -> prev = queue;
            new_node -> next = NULL;
            new_node -> value = value;
            new_node -> key = key;

            queue = new_node;

            while (queue -> prev != NULL) {
                queue = queue -> prev;
            }

            return 0;
        }
    }

    new_node -> prev = queue -> prev;
    new_node -> next = queue;

    if (queue -> prev != NULL) {
        queue -> prev -> next = new_node;
    }

    queue -> prev = new_node;

    new_node -> value = value;
    new_node -> key = key;

    queue = new_node;

    while (queue -> prev != NULL) {
        queue = queue -> prev;
    }

    return 0;
}

double extract_min()
{
    // returns the min value and delete it from queue
    // if queue is empty returns -infinity and print error message to the screen

    if (queue == NULL) {
        printf("Error. Queue is already empty.");
        return -INFINITY;
    } else {
        --size;

        double min_value = queue -> value;

        struct Node* next = queue -> next;

        free(queue);

        queue = next;

        if (queue != NULL) {
            queue -> prev = NULL;
        }

        return min_value;
    }
}

