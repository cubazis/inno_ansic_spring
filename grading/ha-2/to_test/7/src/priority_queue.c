#include "priority_queue.h"

#define LIMIT 100


struct Node *QUEUE_ROOT = NULL;
unsigned int size = 0;


struct Node {
    double value;
    int priority;
    struct Node *next;
};

/**
 * Creates new node with data {@param value}, priority {@param priority} and {@return} a pointer to it
 * @param value Value to put in a new node
 * @param priority Priority of a node
 * @return Pointer to a new node
 */
struct Node *createNode(double value, int priority) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->priority = priority;
    newNode->next = NULL;

    return newNode;
}

/**
 * Pushes {@param value} with {@param priority} to the queue and {@return status} of pushing
 * {@return 0} if everything is ok, {@return 1} if stack is full, {@return 2} if some error occurred
 * @param value Value to push
 * @param priority Priority of a value
 * @return Status code
 */
int insert(double value, int priority) {
    if (size == LIMIT)
        return 1;

    if (QUEUE_ROOT == NULL) {
        QUEUE_ROOT = createNode(value, priority);
        ++size;
        return 0;
    }

    struct Node *start = QUEUE_ROOT;
    struct Node *temp = createNode(value, priority);
    if (QUEUE_ROOT->priority > priority) {
        temp->next = QUEUE_ROOT;
        QUEUE_ROOT = temp;
    } else {
        while (start->next != NULL && start->next->priority > priority)
            start = start->next;

        temp->next = start->next;
        start->next = temp;
    }

    if ((temp->priority != priority) || (temp->value != value))
        return 2;

    ++size;
    return 0;

}

/**
 * Pops a value from the priority queue with the least priority
 * If the priority queue is empty, prints an error message and returns minus infinity
 * @return Top value or -INF if the priority queue is empty
 */
double extract_min() {
    if (!QUEUE_ROOT) {
        printf("Priority queue is empty\n");
        return -INFINITY;
    }
    struct Node *temp = QUEUE_ROOT;
    QUEUE_ROOT = QUEUE_ROOT->next;
    double value = temp->value;
    free(temp);

    --size;
    return value;
}

/*
int main() {
    printf("Pushed 1337, prior 1 - return %i; pushed 228. prior 2 - return %i\n", insert(1337, 1), insert(228, 3));
    printf("Extracted %f, extracted %f, extracted %f\n", extract_min(), extract_min(), extract_min());
    printf("Trying to pop... ");
    printf("Return %f\n", extract_min());
    return 0;
}
*/
