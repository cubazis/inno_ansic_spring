//
// Created by puzankova 30.05.18
//

#include "priority_queue.h"

#define MAX_QUEUE_SIZE 100

struct Node {
    double value;
    int key;
    struct Node *next;
    struct Node *prev;

};

struct Node *queue = NULL; // it is your queue to work with it
static int size_of_the_queue = 0;

int insert(double value, int key) {
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the queue
    //  2 - other

    // the queue size is 100 elements

    if (size_of_the_queue >= MAX_QUEUE_SIZE) {
        return 1;
    } else {
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

        if (new_node == NULL) {
            return 2;
        }
        new_node->value = value;
        new_node->key = key;
        new_node->prev = NULL;
        new_node->next = NULL;

        if (queue == NULL) {
            queue = new_node;
        } else {
            struct Node *current = queue;
            while (current->next != NULL && key >= (current->key)) {
                current = current->next;
            }
            if (key >= current->key) {
                //Current is left

                //Fix right
                if (current->next != NULL) {
                    new_node->next = current->next;
                    current->next->prev = new_node;
                }

                //Fix left
                current->next = new_node;
                new_node->prev = current;
            } else {
                //Current is right

                //Fix left
                if (current->prev != NULL) {
                    current->prev->next = new_node;
                    new_node->prev = current->prev;
                } else {
                    queue = new_node;
                }

                //Fix right
                new_node->next = current;
                current->prev = new_node;
            }
        }

        if (new_node->value != value) {
            return 2;
        }

        ++size_of_the_queue;
        return 0;
    }
    return 2;
}

double extract_min() {
    // returns the min value and delete it from queue
    // if queue is empty returns -infinity and print error message to the screen

    if (queue == NULL) {
        printf("QueueUnderflow: QUEUE IS EMPTY\n");
        return -INFINITY;
    } else {
        double value_to_return = queue->value;
        struct Node *old_node = queue;
        queue = old_node->next;

        if (queue != NULL) {
            queue->prev = NULL;
        }

        free(old_node);
        --size_of_the_queue;
        return value_to_return;
    }
}
