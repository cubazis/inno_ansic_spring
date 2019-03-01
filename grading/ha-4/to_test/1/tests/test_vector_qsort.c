//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "vector_int.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int comp_vectors_int(const void *a, const void *b)
/* Returns -ve if a<b, 0 if a==b, +ve if a>b */
{
	return (*(int*)(a) - *(int*)(b));
}

START_TEST(test_vector_qsort)
{
	struct Vector *v = vector_create_int(0);
	for (int i = 0; i < 100; ++i) {
		vector_push_back_int(v, 100 - i);
		vector_push_back_int(v, -100 + i);
	}
	qsort(vector_get_begin(v), vector_get_size(v), vector_get_item_size(v), comp_vectors_int);
	for (int i = 0; i < vector_get_size(v)-1; ++i) {
		int element1 = *(int*)vector_get_element(v, (size_t)i);
		int element2 = *(int*)vector_get_element(v, (size_t)(i+1));
		ck_assert_int_le(element1, element2);
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