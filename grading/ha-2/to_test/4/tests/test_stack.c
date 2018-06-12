//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include "stack.h"

START_TEST (test_pop)
		{
			push(2.0);
			push(5.0);
			push(3.0);
			ck_assert_double_eq(pop(),3.0);
			ck_assert_double_eq(pop(),5.0);
			ck_assert_double_eq(pop(),2.0);
			ck_assert_double_eq(pop(),-INFINITY);
		}
END_TEST


START_TEST (test_peek)
{
	push(2.0);
	push(5.0);
	push(3.0);
	ck_assert_double_eq(pick(),3.0);
	pop();
	ck_assert_double_eq(pick(),5.0);
	pop();
	ck_assert_double_eq(pick(),2.0);
	pop();
	ck_assert_double_eq(pick(),-INFINITY);
}
END_TEST

START_TEST (test_push)
{
	for(int i = 0; i < 50; i++){		 			//
		push(i);									// Filling out our Stack
	}												//

	ck_assert_double_eq(push(4.0),1);				// Test for checking overflow in th stack

	for(int i = 49; i >= 0; i--){					//
		ck_assert_double_eq(pick(), i);
		pop();										// Make stack empty
	}												//
}
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("stack");
	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test_push);
	tcase_add_test(tcase, test_pop);
	tcase_add_test(tcase, test_peek);
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