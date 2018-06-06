//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include "../src/stack.h"


START_TEST (test_pop)
		{
		    printf("%s\n", "Test POP");
			push(10);
            ck_assert_int_eq(pop(), 10);
			ck_assert(pop()== -INFINITY);

            printf("%s\n", "");
        }
END_TEST


START_TEST (test_peek)
    {
        printf("%s\n", "Test PEEK");
        push(10);
        ck_assert_int_eq(pick(), 10);
        ck_assert_int_eq(pick(), 10);
        pop();
        ck_assert(pick()== -INFINITY);

        printf("%s\n", "");
    }
END_TEST

START_TEST (test_push)
    {
        printf("%s\n", "Test PUSH");
        for(int i=0;i<50;i++)
            ck_assert_int_eq(push(i), 0);

        ck_assert_int_eq(push(10), 1);
        ck_assert_int_eq(pick(), 49);

        pop();
        ck_assert_int_eq(push(10), 0);
        ck_assert_int_eq(pick(), 10);

        printf("%s\n", "");
    }
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("HA 2. Stack Test Suite");
	TCase *tcase = tcase_create("case");

	tcase_add_test(tcase, test_pop);
	tcase_add_test(tcase, test_peek);
    tcase_add_test(tcase, test_push);

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