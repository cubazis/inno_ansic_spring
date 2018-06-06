#include "priority_queue.h"
#include <float.h>

int size = 0;
struct Node *queue = NULL; // it is your queue to work with it


struct Node
{
    double value;
    int key;
    struct Node* next;
    struct Node* prev;

};

int insert(double value, int key)
{
    // return the exit code:
    // 0 - success
    // 1 - not enough free space in the queue
    //  2 - other

    // the queue size is 100 elements

    if (size<100){
        if (queue==NULL){
            queue=malloc(sizeof(struct Node*));
            queue->value=value;
            queue->key=key;
            queue->prev=NULL;
            queue->next=NULL;
            size++;
            return 0;

        } else{
            struct Node *pointer ;
            struct Node *previous = malloc(sizeof(struct Node*));
            pointer=queue;

            while (pointer!=NULL&&key>=pointer->key){
                previous=pointer;
                pointer=pointer->next;
            }
            if (pointer==NULL) {
                pointer=malloc(sizeof(struct Node*));
                pointer->key=key;
                pointer->value=value;
                size++;
                pointer->prev=previous;
                pointer->next=NULL;
                previous->next=pointer;
                return 0;
            }
            else{
                struct Node *temp=malloc(sizeof(struct Node*));
                temp->value=value;
                temp->key=key;
                temp->prev=pointer->prev;
                temp->next=pointer;
                pointer->prev=temp;
                queue=temp;
                size++;
                return 0;

            }
        }
    }
    else{
        return 1;
    }
}

double extract_min()
{
    // returns the min value and delete it from queue
    // if queue is empty returns -infinity and print error message to the screen
    if(queue==NULL){
        printf("%s","Error: Queue is empty");
        return DBL_MIN;
    }
    else{
        double val = queue->value;
//        struct Node *pointer;
//        pointer=queue;
        if(queue->next!=NULL){
            queue=queue->next;
            size--;
        }
        else{
            queue=NULL;
            size--;
        }
        return val;
    }
}