//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include <math.h>
#include "stack.h"

START_TEST (test_pop)
		{
            double eps = 10e-9;
            for (int i=0;i<50;i++){
                ck_assert(push((double)i) == 0);
                ck_assert(abs((double)i - pick()) <= eps);
            }
            for (int i=49;i>=1;i--){
                double val = pop();
//                printf("%f\n", val);
                ck_assert(abs((double)i - val) <= eps);
            }
            push(1.0);
            ck_assert(abs((double)1 - pop()) <= eps);
            ck_assert(abs((double)0 - pop()) <= eps);
            ck_assert(pop() == -INFINITY);
		}
END_TEST


START_TEST (test_peek)
{
    double eps = 10e-9;
    ck_assert(pick() == -INFINITY);
    for (int i=0;i<50;i++){
        ck_assert(push((double)i) == 0);
        ck_assert(abs((double)i - pick()) <= eps);
    }
}
END_TEST

START_TEST (test_push)
{
    double eps = 10e-9;
    for (int i=0;i<50;i++){
        ck_assert(push((double)i) == 0);
        ck_assert(abs((double)i - pick()) <= eps);
    }
    ck_assert(push(1.0) == 1);
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
