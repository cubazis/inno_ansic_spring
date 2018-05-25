//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include "binarize.h"


START_TEST (test_bin_u)
{
	unsigned long x = 1608637542;

	binarize_u(x);
}
END_TEST

START_TEST (test_bin_s)
{
	signed long x = -1608637542;
	binarize_s(x);
}
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("binarize");
	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test_bin_u);
	tcase_add_test(tcase, test_bin_s);
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