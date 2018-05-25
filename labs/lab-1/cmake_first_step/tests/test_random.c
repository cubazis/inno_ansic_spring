//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include "random.h"
#include "math.h"

#include <float.h>
#include <stdlib.h>

#define MAX_L 1000000

const double tolerance = 1e-3;
const double tolerance_strict = 1e-9;

#define ck_assert_double_eq_tol(val, ref, tol) \
	ck_assert(fabs(((val))-((ref))) < tol);

#define ck_assert_double_eq(val, ref) \
	ck_assert_double_eq_tol(val, ref, tolerance_strict);

START_TEST (test_bin)
{
	double samples[MAX_L];
	double sum = 0;
	for (int i = 0; i < MAX_L; ++i) {
		samples[i] = uniform_distribution();
		//printf("%lf\n", samples[i]);
		sum += samples[i];
	}
	double res = 0;
	printf("%lf\n", res = sum/MAX_L);
	ck_assert_double_eq_tol(res, .499, tolerance);
	//ck_assert_double_eq(res, .499);
}
END_TEST

START_TEST (test_bin2)
{
	printf("%i\n", DBL_MANT_DIG);
	printf("%d\n", RAND_MAX);
	printf("%lf\n", DBL_EPSILON);
}
END_TEST

Suite* str_suite (void)
{
	Suite *suite = suite_create("random");
	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test_bin);
	tcase_add_test(tcase, test_bin2);
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