//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "vector_int.h"
#include <stdlib.h>

#define NELEMS(x) (sizeof (x)/sizeof (x[0]))

int comp_vectors_int(const void *a, const void *b)
/* Returns -ve if a<b, 0 if a==b, +ve if a>b */
{
	struct Vector *v1 = (struct Vector *)a;
	struct Vector *v2 = (struct Vector *)b;
	/** YOUR CODE HERE */
}

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