//
// Created by madina on 31.05.18.
//

#include <check.h>
#include <values.h>
#include "stack.h"

double abs_d(double a) {
	return a > 0 ? a : -a;
}

/*
 * Double equality assertion.
 * Used because libcheck
 * cannot compare doubles.
 */
void assert_double_eq(double a, double b) {
	double eps = 1e-9;

	ck_assert(abs_d(a - b) <= eps);
}

START_TEST(test_stack_1)
	{
		ck_assert_int_eq(0, push(2)); // push() returns exit codes
		ck_assert_int_eq(0, push(3)); // see push() implementation
		ck_assert_int_eq(0, push(4));

		assert_double_eq(4, pick());
		assert_double_eq(4, pop());
		assert_double_eq(3, pick());
		assert_double_eq(3, pop());
		assert_double_eq(2, pick());
		assert_double_eq(2, pop());
		ck_assert(isinf(pop())); // empty stack should return negative infinity
		ck_assert(isinf(pick()));
	}
END_TEST

START_TEST(test_stack_2)
	{
		ck_assert(isinf(pop()));
		assert_double_eq(0, push(3));
		assert_double_eq(0, push(2));
		assert_double_eq(0, push(11));
		assert_double_eq(11, pick());
		assert_double_eq(11, pick());
		assert_double_eq(0, push(-36));
		assert_double_eq(-36, pop());
		assert_double_eq(11, pop());
		assert_double_eq(2, pop());
		assert_double_eq(3, pop());
		ck_assert(isinf(pick()));
	}
END_TEST

START_TEST(test_stack_3)
	{
		assert_double_eq(0, push(3.65));
		assert_double_eq(0, push(-6.987521));
		assert_double_eq(0, push(-6.987521));
		assert_double_eq(0, push(-6.987521));
		assert_double_eq(-6.987521, pick());
		assert_double_eq(-6.987521, pop());
		assert_double_eq(-6.987521, pop());
		assert_double_eq(-6.987521, pop());
		assert_double_eq(3.65, pick());
		assert_double_eq(3.65, pop());
		ck_assert(isinf(pop()));
		assert_double_eq(0,push(-0.2456987136));


	}
END_TEST

START_TEST(test_stack_4)
	{
		ck_assert(isinf(pop()));
		int i = 0;
		while(i < 30){
			ck_assert_int_eq(0, push(i));
			i++;
		}
		assert_double_eq(29, pick());
		i = 29;
		while(i  != -1){
			assert_double_eq(i , pop());
			i--;
		}
		ck_assert(isinf(pop()));
	}
END_TEST

START_TEST(test_stack_5)
	{
		for(int i = 0; i < 50; i++){
			ck_assert_int_eq(0, push(INT8_MIN));
		}
		ck_assert_int_eq(1, push(23));
	}
END_TEST

START_TEST(test_stack_6)
    {
        ck_assert_int_eq(0, push(0.123456));
        ck_assert_int_eq(0, push(5));
        ck_assert_int_eq(0, push(7.56982));
        ck_assert_int_eq(0, push(58931478523));
        ck_assert_int_eq(0, push(INT8_MAX));

        int size = 0;
        while (!isinf(pick())){
        	pop();
        	size++;
        }

        ck_assert_int_eq(5, size);
    }
END_TEST

START_TEST(test_stack_7)
	{
		ck_assert(isinf(pop()));
		ck_assert_int_eq(0, push(0.2365874555));
		int i = 0;

		for (i; i <= 48; i++)
			ck_assert_int_eq(0, push(1.23));
		ck_assert_int_eq(1, push(-1.25));
		assert_double_eq(1.23, pop());
	}
END_TEST

START_TEST(test_stack_8)
	{
		int size = 0;
		for(int i = 0; i < 50; i++){
			ck_assert_int_eq(0, push(INT8_MIN));
		}
		ck_assert_int_eq(1, push(23));
		while (!isinf(pick())){
			pop();
			size++;
		}
		ck_assert_int_eq(50, size);
	}
END_TEST

START_TEST(test_stack_9)
	{
		test_stack_7;
		ck_assert_int_eq(0, push(.2));
		assert_double_eq(0.2, pop());
		ck_assert(isinf(pick()));
	}
END_TEST

Suite *test_suite(void) {
	Suite *suite = suite_create("Stack test suite");
	TCase *tCase = tcase_create("Stack test case");

	tcase_add_test(tCase, test_stack_1);
	tcase_add_test(tCase, test_stack_2);
	tcase_add_test(tCase, test_stack_3);
	tcase_add_test(tCase, test_stack_4);
	tcase_add_test(tCase, test_stack_5);
	tcase_add_test(tCase, test_stack_6);
	tcase_add_test(tCase, test_stack_7);
	tcase_add_test(tCase, test_stack_8);
	tcase_add_test(tCase, test_stack_9);
	suite_add_tcase(suite, tCase);
	return suite;
}

int main() {
	int num_failed;
	Suite *suite = test_suite();
	SRunner *runner = srunner_create(suite);
	srunner_run_all(runner, CK_NORMAL);
	num_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return num_failed;
}