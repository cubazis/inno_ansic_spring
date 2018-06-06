//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "vector_int.h"
#include <stdlib.h>
#include <stdio.h>

#define NELEMS(x) (sizeof (x)/sizeof (x[0]))

int comp_vectors_int(const void *a, const void *b)
/* Returns -ve if a<b, 0 if a==b, +ve if a>b */
{
	return *((int*)a) - *((int*)b);
}

START_TEST(test_vector_qsort)
{
	Vector* vector = vector_create_int(5);
	for (int i = 0; i < 100; ++i) {
		vector_push_back_int(vector, 100 - i);
	}
	qsort(vector->data, vector->size, vector->itemsize, comp_vectors_int);
	for (int i = 1; i < 100; ++i) {
		ck_assert(((int*)vector->data)[i] > ((int*)vector->data)[i-1]);
	}
}
END_TEST


Suite* str_suite (void) {
	Suite *suite = suite_create("Assignment 4");
	TCase *tcase = tcase_create("case");


	tcase_add_test(tcase, test_vector_qsort);

	suite_add_tcase(suite, tcase);
	return suite;
}

int main (int argc, char *argv[]) {
	int number_failed;
	Suite *suite = str_suite();
	SRunner *runner = srunner_create(suite);
	srunner_run_all(runner, CK_NORMAL);
	number_failed = srunner_ntests_failed(runner);
	srunner_free(runner);
	return number_failed;
}