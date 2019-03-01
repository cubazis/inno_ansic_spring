# Home Assignment 4

___

## Project template

Now you have [template](https://github.com/cubazis/inno_ansic_spring/tree/dev/assignments/ha-4) for your first home assignment. 

Project Architecture

```
src/vector.h
src/vector.c
src/vector_int.h
src/vector_int.c
tests/test_vector.c
tests/test_vector_int.c
tests/test_vector_qsort.c
```

## Tasks

`tests/test_vector.c` and `tests/test_vector_int.c` are just for your
independent work. Code of these tests will not be graded.

Test `tests/test_vector_qsort.c` has not complete tcase

```C
START_TEST(test_vector_qsort)
{
	struct Vector *v;
	for (int i = 0; i < NELEMS(v); ++i) {
		/** Initialisation */
	}
	qsort(&v, NELEMS(v), sizeof v[0], comp_vectors_int);
	for (int i = 0; i < NELEMS(v); ++i) {
		/** printf */
	}
}
END_TEST
```

Here you should complete initialisation of vector by some unordered sequence of integers.
Then you have to use `qsort` from the `stdlib.h` to sort your vector. 
For this purpose the `comp_vectors_int` have to be finished.

I wrote some initial strings of `comp_vectors_int` code to "help" you. LOL.
```C
int comp_vectors_int(const void *a, const void *b)
/* Returns -ve if a<b, 0 if a==b, +ve if a>b */
{
	struct Vector *v1 = (struct Vector *)a;
	struct Vector *v2 = (struct Vector *)b;
	/** YOUR CODE HERE */
}
```

## Deadline 
After **15.20 06/06** you commits will not be checked.