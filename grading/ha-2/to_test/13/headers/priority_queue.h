#ifndef LAB_1_PQ_H
#define LAB_1_PQ_H

#include <stdlib.h>
#include "bscds.h"

PQ * create_pq();
void delete_pq(PQ* queue);
int pq_extract_head(PQ *queue);
void pq_insert(PQ *queue, int val, int priority);
int pq_head(PQ* queue);

#endif //LAB_1_PQ_H
