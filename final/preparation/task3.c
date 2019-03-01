#include <stdio.h>
#include "stdlib.h"
#include <string.h>

/** Demanded output:
 * >
 *  Dequeued Samuel
 *  Dequeued Sally
 *  Dequeued Susan
 *
 *  Process finished with exit code 0
 */

typedef	struct	_student
{
	char first_name[32];
	unsigned char score;
} Student;

typedef	struct _node
{
	void *data;
	struct _node *next;
} Node;

typedef	struct _linkedList {
	Node *head;
	Node *tail;
	Node *current;
} LinkedList;

typedef	LinkedList Queue;

void init_list(LinkedList *list) {
	/** YOUR CODE HERE */

	/** YOUR CODE HERE */
}

void append(LinkedList *list, void* data) {
	/** YOUR CODE HERE */

	/** YOUR CODE HERE */
}

void init_queue(Queue *queue) {
	/** YOUR CODE HERE */

	/** YOUR CODE HERE */
}

void enqueue(Queue *queue, void *node) {
	/** YOUR CODE HERE */

	/** YOUR CODE HERE */
}

void *dequeue(Queue *queue)
{
	Node *tmp = queue->head;
	void *data;
	/** YOUR CODE HERE */

	/** YOUR CODE HERE */
	return data;
}

int main() {
	Queue queue;

	Student *samuel = (Student*) malloc(sizeof(Student));
	strcpy(samuel->first_name, "Samuel");
	samuel->score = 99;
	/** YOUR CODE HERE */

	/** YOUR CODE HERE */

	init_queue(&queue);
	enqueue(&queue, samuel);

	/** YOUR CODE HERE */

	/** YOUR CODE HERE */

	void *data = dequeue(&queue);

	printf("Dequeued %s\n", ((Student*) data)->first_name);
	data = dequeue(&queue);
	/** YOUR CODE HERE */

	/** YOUR CODE HERE */
}