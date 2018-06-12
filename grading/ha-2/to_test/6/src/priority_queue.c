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
struct Node *queue = NULL; // it is your queue to work with it
int insert(double value, int key)
{
    // return the exit code:
    //	0 - success
    //	1 - not enough free space in the queue
    //  2 - other

    // the queue size is 100 elements

    /* YOUR CODE */

    struct Node* newNode = malloc(sizeof(struct Node));     //create new node
    newNode -> value = value;
    newNode ->key = key;
    newNode -> next = NULL;
    newNode -> prev = NULL;

    if(queue == NULL){                                      //if queue is empty, place new node in it
        queue = newNode;
        return 0;
    } else{                                                 //else place node if size less then 100
        if(queue_size() >= 100){
            printf("ERROR: CANNOT PLACE %f IN QUEUE - IT IS FULL!\n", value);
            return 1;
        }
        struct Node* current = queue;                         //find the position there new node must be placed
        while((current->key)<key && (current->next) != NULL){
            current = current -> next;
        }
        if(current->key >= key){                              //after last element with smaller key
            if(current->prev != NULL) (current->prev)->next = newNode;
            else queue = newNode;
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev = newNode;
            return 0;

        } else{                                                //of before first element with bigger or equal key
            current->next=newNode;
            newNode->prev = current;
            return 0;
        }
    }
    return 2;

}

double extract_min()
{
	// returns the min value and delete it from queue
	// if queue is empty returns -infinity and print error message to the screen
	/* YOUR CODE */

    if (queue == NULL){
        printf("ERROR: EXTRACTING FROM EMPTY QUEUE!\n");
        return -INFINITY;
    } else{
        double result = queue->value;
        struct Node* trash = queue;
        queue = queue->next;
        free(trash);
        if(queue != NULL) queue->prev = NULL;
    }
}

int queue_size(){
    //return number of elements in queue
    int size = 0;
    struct Node* top = (queue);
    while(top != NULL){
        (size)++;
        top = (top) -> next;
    }
    return size;
}

