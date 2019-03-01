//
// Created by Максим on 31.05.2018.
//

#include "priority_queue.h"
#include <float.h>

#define MAX_SIZE 100 // queue's max_size

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

    if (size < MAX_SIZE) {
        if (!queue) { // the queue is empty -> crete a new queue
            queue = malloc(sizeof(struct Node));
            if (!queue) {
                return 2;
            }
            queue->prev = NULL;
            queue->next = NULL;
            queue->value = value;
            queue->key = key;
        }
        else { // the queue is not empty -> insert to the queue
            struct Node *iterator = queue;
            struct Node *last;
            while (iterator && iterator->key < key) {
                last = iterator;
                iterator = iterator->next;
            }
            struct Node *new_node = malloc(sizeof(struct Node));
            if (!new_node) {
                return 2;
            }
            new_node->value = value;
            new_node->key = key;
            if (iterator) { // insert to non-end
                new_node->prev = iterator->prev;
                if (new_node->prev) {
                    new_node->prev->next = new_node;
                }
                new_node->next = iterator;
                iterator->prev = new_node;
                if (!new_node->prev) { // new_node if begining of queue
                    queue = new_node;
                }
            }
            else { // insert to the end
                last->next = new_node;
                new_node->prev = last;
                new_node->next = NULL;
            }
            new_node = NULL;
            last = NULL;
        }
        ++size;
        return 0;
    }
    return 1;

}

double extract_min()
{
    // returns the min value and delete it from queue
    // if queue is empty returns -infinity and print error message to the screen

    if (size > 0) {
        double value = queue->value;
        struct Node *temp_ptr = queue;
        queue = queue->next;
        free(temp_ptr);
        temp_ptr = NULL;
        if (queue) {
            queue->prev = NULL;
        }
        --size;
        return value;
    }
    else {
        printf("Failed: an attempt to extract from an empty queue\n");
        return -DBL_MAX;
    }
}

