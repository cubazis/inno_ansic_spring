//
// Created by puzankova 30.05.18
//

#include <math.h>
#include "priority_queue.h"


#define MAX_QUEUE_SIZE 100

static int size = 0;

struct Node {
    double value;
    int key;
    struct Node *next;
};

struct Node *queue = NULL; // it is your queue to work with it

int insert(double value, int key) {
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the queue
    //  2 - other

    // the queue size is 100 elements

    if (size == MAX_QUEUE_SIZE)
        return 1;
    else if (!queue) {
        size++;
        queue = malloc(sizeof(struct Node));
        *queue = (struct Node) {.value = value, .key = key, .next = NULL};
    } else {
        size++;
        struct Node *node = malloc(sizeof(struct Node));
        *node = (struct Node) {.value = value, .key = key, .next = NULL};
        if (key < queue->key) {
            node->next = queue;
            queue = node;
        } else {
            struct Node *i = queue;
            for (; i->next && key >= i->next->key; i = i->next);
            node->next = i->next;
            i->next = node;
        }
        return 0;
    }
}

double extract_min() {
    // returns the min value and delete it from queue
    // if queue is empty returns -infinity and print error message to the screen
    if (!queue) {
        printf("  _      ____   ____   _____ ______ _____  \n"
               " | |    / __ \\ / __ \\ / ____|  ____|  __ \\ \n"
               " | |   | |  | | |  | | (___ | |__  | |__) |\n"
               " | |   | |  | | |  | |\\___ \\|  __| |  _  / \n"
               " | |___| |__| | |__| |____) | |____| | \\ \\ \n"
               " |______\\____/ \\____/|_____/|______|_|  \\_\\\n");
        return -INFINITY;
    }
    else {
        double res = queue->value;
        struct Node *new_queue = queue->next;
        free(queue);
        queue = new_queue;
        size--;
        return res;
    }
}
