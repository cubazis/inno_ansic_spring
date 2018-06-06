//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include <stdlib.h>
#include "vector_int.h"
#include <time.h>
#include <stdio.h>

#define NELEMS(x) (vector_get_capacity(x))

int comp_vectors_int(const void *a, const void *b)
/* Returns -ve if a<b, 0 if a==b, +ve if a>b */
{
	Vector *v1 = (Vector *)a;
	Vector *v2 = (Vector *)b;
	/** YOUR CODE HERE */

	return *(int *)v1 - *(int *)v2;                 //compare two numbers

}

START_TEST(test_vector_qsort)
{
	srand(time(NULL));
	int size = 100;
	Vector *v = vector_create_int(size);                        //Create vector
	for (int i = 0; i < NELEMS(v); ++i) {                     //Fill with random numbers
		/** Initialisation */
		int r = rand()%10000;
		vector_push_back_int(v, r);

	}

	int* to_sort = (int *)(vector_get_begin(v));              //Get array
	printf("Before sort: \n");                                //Print array before sort
	for (int i = 0; i < NELEMS(v); ++i) {
		/** printf */
		printf("%d ",to_sort[i] );
	}


	qsort(to_sort, NELEMS(v), vector_get_item_size(v), comp_vectors_int);        //Sort array


	printf("\nAfter sort: \n");                                  //Print array after sort
	for (int i = 0; i < NELEMS(v); ++i) {
		/** printf */
		printf("%d ", to_sort[i] );
	}
	printf("\n");
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