#include "../headers/priority_queue.h"
#include "../headers/pq_node.h"
#include <stdlib.h>

PQ * create_pq(){
	PQ* pq = (PQ*) malloc(sizeof(PQ));

	pq->size = 0;
	pq->max_size = 32;
	pq->heap = (PQ_NODE**)malloc((size_t)pq->max_size);

	return pq;
}

static void sift_up(PQ* pq, int i) {
	if (i > 0) {
		PQ_NODE *node = pq->heap[i];
		PQ_NODE *parent = pq->heap[(i - 1) / 2];
		if (node->priority > parent->priority) {
			pq->heap[i] = parent;
			pq->heap[(i - 1) / 2] = node;
			sift_up(pq, (i - 1) / 2);
		}
	}
}

static void sift_down(PQ* pq, int i) {
	if ((i) < (pq->size-1)/2) {
		PQ_NODE *node = pq->heap[i];
		PQ_NODE *left = pq->heap[i * 2 + 1];
		PQ_NODE *right = pq->heap[i * 2 + 2];
		if (node->priority < left->priority || node->priority < right->priority) {
			if (node->priority < left->priority && left->priority > right->priority) {
				pq->heap[i] = left;
				pq->heap[i * 2 + 1] = node;
				sift_down(pq, i * 2 + 1);
			} else {
				pq->heap[i] = right;
				pq->heap[i * 2 + 2] = node;
				sift_down(pq, i * 2 + 2);
			}
		}
	}
}

static void increase_array(PQ* pq) {
	pq->max_size *= 2;
	PQ_NODE** new_heap = (PQ_NODE**)malloc((size_t)pq->max_size);

	for (int i = 0; i < pq->size; i++) {
		new_heap[i] = pq->heap[i];
	}

	pq->heap = new_heap;
}

void delete_pq(PQ* pq) {
	for (int i = pq->size; i > 0; i--) pq_extract_head(pq);
	free(pq->heap);
	free(pq);
}

int pq_extract_head(PQ *pq) {
	PQ_NODE** heap = pq->heap;
	int val = heap[0]->value;

	delete_node(heap[0]);
	heap[0] = heap[pq->size - 1];

	sift_down(pq, 0);

	pq->size--;
	return val;
}

void pq_insert(PQ *pq, int val, int priority) {
	PQ_NODE* node = create_node();
	node->priority = priority;
	node->value = val;

	pq->heap[pq->size] = node;

	sift_up(pq, pq->size);

	pq->size++;
  
	if (pq->size >= (pq->max_size-1) / 2) {
		increase_array(pq);
	}
}

int pq_head(PQ* pq) {
	return (pq->size != 0) ? pq->heap[0]->value : -1;
}
