#include "stack.h"

#define LIMIT 50


struct Node *STACK_ROOT = NULL;
unsigned int size = 0;


struct Node {
    double value;
    struct Node *next;
};

/**
 * Creates new node with data {@param value} and returns a pointer to it
 * @param value Value to put in a new node
 * @return Pointer to a new node
 */
struct Node *createNode(double value) {
    struct Node *newNode =
            (struct Node *) malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

/**
 * Pops a value from the top of the stack
 * If the stack is empty, prints an error message and returns minus infinity
 * @return Top value or -INF if the stack is empty
 */
double pop() {
    if (!STACK_ROOT) {
        printf("Stack is empty\n");
        return -INFINITY;
    }

    struct Node *temp = STACK_ROOT;
    STACK_ROOT = STACK_ROOT->next;
    double popped = temp->value;
    free(temp);

    --size;
    return popped;
}

/**
 * Peeks a value from the top of the stack
 * If stack is empty, prints an error message and returns minus infinity
 * @return Top value or -INF if stack is empty
 */
double peek() {
    if (!STACK_ROOT) {
        printf("Stack is empty\n");
        return -INFINITY;
    }
    return STACK_ROOT->value;
}

/**
 * Pushes {@param value} to the top of the stack and {@return status} of pushing
 * {@return 0} if everything is ok, {@return 1} if stack is full, {@return 2} if some error occurred
 * @param value Value to push
 * @return Status code
 */
int push(double value) {
    if (size == LIMIT)
        return 1;

    struct Node *stackNode = createNode(value);
    stackNode->next = STACK_ROOT;
    STACK_ROOT = stackNode;

    if (peek() != value) return 2;

    ++size;
    return 0;
}
/*
int main() {
    printf("Pushed 1337 - return %i, pushed 228 - return %i\n", push(1337), push(228));
    printf("Peeked %f, popped %f, popped %f\n", peek(), pop(), pop());
    printf("Trying to pop... ");
    printf("Return %f\n", pop());
    return 0;
}
*/
