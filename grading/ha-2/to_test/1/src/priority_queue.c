#include <math.h>
#include "priority_queue.h"

struct Node {
    double value;
    int key;
    struct Node *next;
    struct Node *prev;

};

int size = 0; // current size of queue
struct Node *queue = NULL; // it is your queue to work with it
//struct Node *first=NULL;

int insert(double value, int key) {
    // return the exit code:
    //  0 - success
    //  1 - not enough free space in the queue
    //  2 - other

    // the queue size is 100 elements
    int prev_size = size;

    if (size == 100) {
        return 1;
    }

    struct Node *new = malloc(sizeof(struct Node));
    (*new).value = value;
    (*new).key = key;

    if (size == 0) {
        queue = new;
    } else if (size == 1) {
        if (queue->key > key) {
            queue->prev = new;
            new->next = queue;
            queue = new;
        } else {
            queue->next = new;
            new->prev = queue;
        }
    } else {

        struct Node *find_place = queue;
        while (((*find_place).next != NULL) && ((*find_place).key <= key)) {
            find_place = find_place->next;
        }
        if (find_place->next == NULL && find_place->key < new->key) {
            find_place->next = new;
            new->prev = find_place;
        } else {
            if (find_place != queue) {
                new->prev = (*find_place).prev;
                (*(*find_place).prev).next = new;
                new->next = find_place;
                (*find_place).prev = new;
            } else {
                queue->prev = new;
                new->next = queue;
                queue = new;

            }
        }
    }


    size++;

    struct Node *check = queue;
    for (int i = 0; i < size - 1; i++) {
        if (check != NULL && check->next != NULL && check->next->key < check->key) {
            return 2;
        }
        check = check->next;
    }
    if (size != prev_size + 1)
        return 2;
    return 0;


}

double extract_min() {
    // returns the min value and delete it from queue
    // if queue is empty returns -infinity and print error message to the screen
    /* YOUR CODE */
    if (size == 0) {
        fprintf(stderr, "Queue is empty\n");
        return -INFINITY;
    } else if (size == 1) {
        double res = queue->value;
        queue = NULL;
        size--;
    } else {

        double res = queue->value;
        // struct Node *tofree = queue;

        queue = queue->next;

//        if (queue != NULL) {
//            free(tofree);
//        }
        size--;
        return res;
    }
}