//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include "stack.h"

START_TEST (test_pop)
		{
			//YOUR CODE HERE
		}
END_TEST


START_TEST (test_peek)
{
	//YOUR CODE HERE
}
END_TEST

START_TEST (test_push)
{
	//YOUR CODE HERE												
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