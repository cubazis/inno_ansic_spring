//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "vector_int.h"
#include "vector.c"
#include <stdlib.h>
#include <stdio.h>

int comp_vectors_int(const void *a, const void *b)
/* Returns -ve if a<b, 0 if a==b, +ve if a>b */
{
	// struct Vector *v1 = (struct Vector *)a;
	// struct Vector *v2 = (struct Vector *)b;
	if (*(int*)(a) > *(int*)(b)) return 1;
	else if (*(int*)(a) < *(int*)(b)) return -1;
	else return 0;
}

START_TEST(test_vector_qsort)
{
	struct Vector *v = (struct Vector*)malloc(10 * sizeof(struct Vector));
	for (int i = 0; i < 10; ++i) {
		((int*)v->data)[i] = 10 - i;
	}
	qsort(&v, 10, sizeof v[0], comp_vectors_int);
	for (int i = 0; i < 10; ++i) {
		printf("%d ", ((int*)v->data)[i]);
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