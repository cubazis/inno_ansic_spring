
#include <math.h>
#include "priority_queue.h"

static int size = 0;
struct Node *queue = NULL;
struct Node {
    double value;
    int key;
    struct Node *next;
    struct Node *prev;

};

struct Node *get_node(double value, int key, struct Node *next, struct Node *prev) {
    struct Node *buff = malloc(sizeof(struct Node));
    buff->value = value;
    buff->key = key;
    buff->prev = prev;
    buff->next = next;
    return buff;
}

int insert(double value, int key) {
    if (size == 100) {
        return 1;
    }
    if (queue == NULL) {
        struct Node *temp = get_node(value, key, NULL, NULL);
        queue = temp;
        size++;
        return 0;

    } else {
        struct Node *buf = queue;
        while (buf->key <= key && buf != NULL) {
            if (buf->next == NULL) {
                struct Node *temp = get_node(value, key, NULL, buf);
                buf->next = temp;
                size++;
                return 0;
            }
            buf = buf->next;
        }
        struct Node *temp = get_node(value, key, buf, buf->prev);
        if (buf->prev == NULL) {
            buf->prev = temp;
            queue = buf->prev;
        }
        else {
            buf->prev->next = temp;
            buf->prev = temp;
        }
        size++;
        return 0;
    }
}

void show_list() {
    struct Node *buf = queue;
    int i = 0;
    printf("List:\n");
    while (i < size) {
        printf("(%d,%d)", buf->key, (int) buf->value);
        buf = buf->next;
        i++;
    }
    printf("\n");
}

double extract_min() {
    if (size==0){
        printf("Error!Queue is empty\n");
        return -INFINITY;
    }
    double res=queue->value;
    struct Node * buf= queue;
    queue=queue->next;
    free(buf);
    if (queue!=NULL){
        queue->prev=NULL;
    }
    size--;
    return res;
}
