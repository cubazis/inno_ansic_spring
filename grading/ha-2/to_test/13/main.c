#include <stdio.h>
#include "headers/bds.h"

int main() {

	PQ* q = create_pq();

	pq_insert(q, 1, 3);
	pq_insert(q, 2, 2);
	pq_insert(q, 3, 4);
	pq_insert(q, 4, 1);

	printf("%d\n", pq_extract_head(q));
	printf("%d\n", pq_extract_head(q));
	printf("%d\n", pq_extract_head(q));
	printf("%d\n", pq_extract_head(q));

	return 0;
}