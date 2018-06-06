//
// Created by cubazis on 25.05.18.
//

#include <check.h>
#include <math.h>
#include "stack.h"
#include "priority_queue.h"
#include <time.h>
#include <stdlib.h>

START_TEST (test_priority_queue)
{
	int output = 0;
	double min = 0.0;

	/**Fill all queue with 100 elements*/
	for(int i = 0; i<100; i++){
		output = insert(i,i);
		ck_assert(output == 0);
	}

	/**Try to place element in the full queue (1)*/
	output = insert(200, 200);
	ck_assert(output == 1);

	/**Extract all elements from queue*/
	for(int i = 0; i<100; i++){
		min = extract_min();
		ck_assert(fabs(min - i)<0.000001);
	}

	/**Try to extract min from empty queue (2)*/
	min = extract_min();
	ck_assert(min == -INFINITY);

/**
	*Output after test:
	*1: ERROR: CANNOT PLACE 200.000000 IN QUEUE - IT IS FULL!
	*2: ERROR: EXTRACTING FROM EMPTY QUEUE!
*/

}
END_TEST

START_TEST (test_stack)
{
	int output = 0;
	double element = 0.0;

	//random step for picking
	srand(time(NULL));
	int index = rand() % 50;

	/**Fill all stack with 50 elements*/
	for(int i = 0; i<50; i++){
		output = push(i);

		/**Pick top in random step of cycle*/
		if(i == index){
			element = peek();
			ck_assert(element == index);
		}

		ck_assert(output == 0);
	}

	/**Try to place element in the full stack (1)*/
	output = push(200);
	ck_assert(output == 1);

	/**Extract all elements from stack*/
	for(int i = 49; i>-1; i--){
		element = pop();
		ck_assert(fabs(element - i)<0.000001);
	}

	/**Try to extract min from empty stack (2)*/
	element = pop();
	ck_assert(element == -INFINITY);

/**
	*Output after test:
	*1: ERROR: CANNOT PLACE 200.000000 IN STACK - IT IS FULL!
	*2: ERROR: EXTRACTING FROM EMPTY STACK!
*/
}
END_TEST


Suite* str_suite (void) {
	Suite *suite = suite_create("Home assignment 1");
	TCase *tcase = tcase_create("case");


	tcase_add_test(tcase, test_stack);
	tcase_add_test(tcase, test_priority_queue);
	/** YOUT TEST CASES HERE */

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