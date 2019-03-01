#include "../headers/bscds.h"
#include "../headers/pq_node.h"
#include <stdlib.h>

PQ_NODE * create_node() {
    PQ_NODE * node = (PQ_NODE*) malloc(sizeof(PQ_NODE));
    node->value = 0;
    node->priority = 0;
    return node;
}

void delete_node(PQ_NODE* node) {
    free(node);
}
