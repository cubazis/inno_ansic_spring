//
// Created by cubazis on 05.06.18.
//

#ifndef LAB4_EXPANDABLE_VECTOR_H
#define LAB4_EXPANDABLE_VECTOR_H

#include <stddef.h> /* for size t */
typedef struct Vector Vector;

/* Vector creation and destruction. */

Vector *vector_create(size_t capacity, size_t itemsize);

void vector_destroy(Vector *v);

/* Vector access operations. */

int vector_push_back(Vector *v, const void *item);

void vector_pop_back(Vector *v, void *item);

void* vector_get_element(Vector *v, size_t index);

void* vector_get_begin(Vector *v);

void* vector_get_end(Vector *v);

/* Size operations. */
size_t vector_get_item_size(const Vector *v);

size_t vector_get_size(const Vector *v);

size_t vector_get_capacity(const Vector *v);

int vector_set_size(Vector *v, size_t size);

int vector_set_capacity(Vector *v, size_t size);

#endif //LAB4_EXPANDABLE_VECTOR_H
