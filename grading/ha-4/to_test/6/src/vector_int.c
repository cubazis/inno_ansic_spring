//
// Created by cubazis on 05.06.18.
//

#include "vector_int.h"
#include <assert.h>

Vector *vector_create_int(size_t capacity)
{
	return vector_create(capacity, sizeof (int));
}

int vector_push_back_int(Vector *v, int item)
{
	assert(vector_get_item_size(v) == sizeof (int));
	return vector_push_back(v, &item);
}

int vector_pop_back_int(Vector *v)
{
	int i;
	assert(vector_get_item_size(v) == sizeof (int));
	vector_pop_back(v, &i);
	return i;
}