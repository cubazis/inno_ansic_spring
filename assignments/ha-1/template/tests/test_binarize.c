//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include "binarize.h"


START_TEST (test_bin)
{
	printf("unsigned UINT_MAX: ");
	binarize_u(UINT_MAX);

	unsigned long x = 1608637542;
	signed long y = -1608637542;

	printf("unsigned long x: %lu\n", x);
	printf("signed long x: %ld\n", y);

	binarize_u(x);
	binarize_s(y);
}
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("binarize");
	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test_bin);
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