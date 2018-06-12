#ifndef LAB_1_STACK_H
#define LAB_1_STACK_H
#include "bscds.h"

STACK * const create_stack();
void stack_put(STACK *stack, int val);
int stack_pull(STACK *stack);
int stack_peek(STACK *stack);
int stack_size(STACK *stack);
void delete_stack(STACK* stack);

#endif //LAB_1_STACK_H
