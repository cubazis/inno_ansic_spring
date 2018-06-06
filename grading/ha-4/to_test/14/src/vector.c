//
// Created by cubazis on 05.06.18.
//

#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/** initial vector capacity */
static const float GrowthRate = 1.6f; /* geometric growth of vector capacity */
static const size_t StartSize = 5;
typedef struct Vector {
	void *data;
	size_t capacity;
	size_t size;
	size_t itemsize;
} Vector;

/**
typedef struct Vector {
	void *begin;
	void *end;
	void *last;
	size_t itemsize;
} Vector;
 */

Vector *vector_create(size_t capacity, size_t itemsize)
/** Initialise a vector with the specified capacity for items of size itemsize. */
{
	Vector *v = (Vector *)malloc(sizeof (Vector));
	if (v) {
		v->data = malloc(capacity*itemsize);
		v->capacity = (v->data == NULL) ? 0 : capacity;
		v->size = 0;
		v->itemsize = itemsize;
	}
	return v;
}

/** Release memory owned by vector. */
void vector_destroy(Vector *v)
{
	free(v->data);
	free(v);
}

/** Add element to back of vector.
 * Return index of new element if successful, and -1 if fails.
 */

int vector_push_back(Vector *v, const void *item)
{
	/* If out-of-space, allocate more. */
	if (v->size == v->capacity) {
		size_t newsize = (v->capacity == 0) ? StartSize : (size_t)(v->capacity*GrowthRate + 1.0);
		void *p = realloc(v->data, newsize*v->itemsize);
		if (p == NULL)
			return -1;
		v->capacity = newsize; /* allocate succeeds, update data-structure */
		v->data = p;
	}
	/* We have enough room. */
	memcpy((char*)v->data + v->size * v->itemsize, item, v->itemsize);
	return v->size++;
}


/** Return element from back of vector, and remove it from the vector. */

void vector_pop_back(Vector *v, void *item)
{
	assert(v->size > 0);
	--v->size;
	memcpy(item, (char*)v->data + v->size * v->itemsize, v->itemsize);
}

/** Return pointer to the element at the specified index. */

void* vector_get_element(Vector *v, size_t index)
{
	assert(index >= 0 && index < v->size);
	return (char*)v->data + index * v->itemsize;
}

/** Return pointer to beginning of array (ie, to first element of array). */
void* vector_get_begin(Vector *v)
{
	return v->data;
}

/** Return pointer to one-past-end of array. */
void* vector_get_end(Vector *v)
{
	return (char*)v->data + v->size*v->itemsize;
}

/** Inquire after size of vector item. */
size_t vector_get_item_size(const Vector *v)
{
	return v->itemsize;
}

/** Inquire after vector size */

size_t vector_get_size(const Vector *v)
{
	return v->size;
}

/** Inquire after vector capacity */
size_t vector_get_capacity(const Vector *v)
{
	return v->capacity;
}

/** Set vector size. Return 0 if successful, -1 if fails. */
int vector_set_size(Vector *v, size_t size)
{
	if (size > v->capacity) {
		void *p = realloc(v->data, size*v->itemsize);
		if (p == NULL)
			return -1;
		v->capacity = size; /* allocate succeeds, update data-structure */
		v->data = p;
	}
	v->size = size;
	return 0;
}

/** Shrink or grow allocated memory reserve for array.
 * A size of 0 deletes the array.
 * Return 0 if successful, -1 if fails. */
int vector_set_capacity(Vector *v, size_t size){
	if (size != v->capacity) {
		void *p = realloc(v->data, size * v->itemsize);
		if (p == NULL && size > 0)
			return -1;
		v->capacity = size;
		v->data = p;
	}
	if (size < v->size)
		v->size = size;
	return 0;
}