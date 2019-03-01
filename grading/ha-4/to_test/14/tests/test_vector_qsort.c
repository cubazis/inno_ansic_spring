//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "vector_int.h"
#include <stdlib.h>
#include "stdio.h"
#include "ranlib.h"

int comp_vectors_int(const void *a, const void *b)
/* Returns -ve if a<b, 0 if a==b, +ve if a>b */
{
    return *(int*)a > *(int*)b ? 1 : *(int*)a < *(int*)b ? -1 : 0;
}

START_TEST(test_vector_qsort)
{
	struct Vector *v = vector_create_int(10);

	/*
	 * Test 1
	 */
    printf("Test 1:\n");
    vector_push_back_int(v, 0);
	for (int i = 0; i < 5; ++i) {
	    int j = (int)random() % 5 + 1;
        vector_push_back_int(v, j);
	}
	/* before qsort */
    for (int i = 0; i < vector_get_size(v); ++i) {
        printf("%d ", *(int*)vector_get_element(v, (size_t)i));
    }
    printf("\n");

	qsort(vector_get_begin(v), vector_get_size(v), sizeof(int), comp_vectors_int);

    /* after qsort */
	for (int i = 0; i < vector_get_size(v); ++i) {
		printf("%d ", *(int*)vector_get_element(v, (size_t)i));
		if (i < vector_get_size(v) - 1)
		    ck_assert_int_le(*(int*)vector_get_element(v, (size_t)i), *(int*)vector_get_element(v, (size_t)(i + 1)));
	}
	printf("\n\n");

    /*
     * Test 2
     */

    struct Vector *v2 = vector_create_int(10);
    printf("Test 2:\n");
    for (int i = 1; i < 6; ++i) {
        int j = 6 - i;
        vector_push_back_int(v2, j);
    }

    /* before qsort */
    for (int i = 0; i < vector_get_size(v2); ++i) {
        printf("%d ", *(int*)vector_get_element(v2, (size_t)i));
    }
    printf("\n");

    qsort(vector_get_begin(v2), vector_get_size(v2), sizeof(int), comp_vectors_int);

    /* after qsort */
    for (int i = 0; i < vector_get_size(v2); ++i) {
        printf("%d ", *(int*)vector_get_element(v2, (size_t)i));
        if (i < vector_get_size(v2) - 1)
        ck_assert_int_le(*(int*)vector_get_element(v2, (size_t)i), *(int*)vector_get_element(v2, (size_t)(i + 1)));
    }
    printf("\n\n");
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