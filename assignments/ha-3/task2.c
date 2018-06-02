#include "stdio.h"

struct Node
{
	double value;
	struct Node* next;
	struct Node* prev;
};

int main(int argc, char const *argv[])
{
	struct Node node1;
	struct Node node2;

	node1.value = 1;
	node2.value = 2;

	node1.next = &node2;
	node2.prev = &node1;

	(*(node1.next)).value = 3;

	(*(*node1.next).prev).value = 4;

	printf("%f\n", node1.value);

	
	return 0;
}