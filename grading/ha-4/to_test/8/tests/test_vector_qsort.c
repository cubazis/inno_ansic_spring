//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "vector_int.h"
#include <stdlib.h>
#include <stdio.h>
#include "vector.c"
#include "time.h"

#define NELEMS(x) (sizeof (x)/sizeof (x[0]))

int comp_vectors_int(const void *a, const void *b)
/* Returns -ve if a<b, 0 if a==b, +ve if a>b */
{
//	struct Vector *v1 = (struct Vector *)a;
//	struct Vector *v2 = (struct Vector *)b;
    //What is going on with this template???
	/** YOUR CODE HERE */
	return (*(int*)a - *(int*)b);
}

START_TEST(test_vector_qsort)
{
	Vector *v;
	v = vector_create_int(10);  //init
	srand(time(NULL));  //set seed for rand()
    int max_size = 100; //Size of a vector
    int mod = 1000;   //Upper bound for the absolute value of vector element

	for (int i = 0; i < max_size; ++i) {  //NELEMS gives error here
        int temp = ((rand() % 2) ? 1 : -1) *(rand() % mod);  //get random integer
        vector_push_back_int(v, temp);
	}

	//Print all element of vector
	printf("\n");
    for (int i = 0; i < max_size; ++i) {
        /** printf */
        printf("%d ", *((int*)vector_get_element(v, (size_t)i)));
    }
    printf("\n");

    //SORT
    qsort(v->data, max_size, sizeof(int), comp_vectors_int);

    //Output sorted array
    for (int i = 0; i < max_size; ++i) {
        /** printf */
        printf("%d ", *((int*)vector_get_element(v, (size_t)i)));

    }
    printf("\n");

    //Asserts :)
    for (int i = 1;i < max_size;++i){
        int curr = *((int*)vector_get_element(v, (size_t)i));
        int prev = *((int*)vector_get_element(v, (size_t)(i-1)));
        ck_assert(prev <= curr);
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