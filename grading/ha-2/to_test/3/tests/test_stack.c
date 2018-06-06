//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include "stack.h"

#define TOL_STRICT 1e-9

START_TEST (test_pop)
    {
        ck_assert_int_eq(push(3), 0);
        ck_assert_double_eq_tol(pop(), 3, TOL_STRICT);
        ck_assert_int_eq(push(5), 0);
        ck_assert_int_eq(push(3), 0);
        ck_assert_int_eq(push(1.1111), 0);
        ck_assert_int_eq(push(7), 0);
        ck_assert_int_eq(push(102), 0);
        ck_assert_int_eq(push(12456), 0);
        ck_assert_int_eq(push(0), 0);
        ck_assert_double_eq_tol(pop(), 0, TOL_STRICT);
        ck_assert_double_eq_tol(pop(), 12456, TOL_STRICT);
        ck_assert_double_eq_tol(pop(), 102, TOL_STRICT);
        ck_assert_int_eq(push(228), 0);
        ck_assert_double_eq_tol(pop(), 228, TOL_STRICT);
        ck_assert_int_eq(push(1337), 0);
        ck_assert_int_eq(push(228), 0);
        ck_assert_double_eq_tol(pop(), 228, TOL_STRICT);
        ck_assert_double_eq_tol(pop(), 1337, TOL_STRICT);
        ck_assert_int_eq(push(8943), 0);
        ck_assert_int_eq(push(1212), 0);
        ck_assert_int_eq(push(1212112), 0);
        ck_assert_int_eq(push(9997), 0);
        ck_assert_double_eq_tol(pop(), 9997, TOL_STRICT);
        ck_assert_double_eq_tol(pop(), 1212112, TOL_STRICT);
        ck_assert_double_eq_tol(pop(), 1212, TOL_STRICT);
        ck_assert_double_eq_tol(pop(), 8943, TOL_STRICT);
        ck_assert_double_eq_tol(pop(), 7, TOL_STRICT);
        ck_assert_double_eq_tol(pop(), 1.1111, TOL_STRICT);
        ck_assert_double_eq_tol(pop(), 3, TOL_STRICT);
        ck_assert_double_eq_tol(pop(), 5, TOL_STRICT);
        ck_assert_double_eq(pop(), -INFINITY);

    }
END_TEST


START_TEST (test_peek)
    {
        ck_assert_double_eq(pick(), -INFINITY);
        for (int i = 0; i < MAX_STACK_SIZE; ++i) {
            ck_assert_int_eq(push(i), 0);
            ck_assert_double_eq_tol(pick(), i, TOL_STRICT);
        }
        ck_assert_int_eq(push(228), 1);
        ck_assert_double_eq_tol(pick(), 49, TOL_STRICT);
        ck_assert_int_eq(push(228), 1);
        ck_assert_double_eq_tol(pick(), 49, TOL_STRICT);
        ck_assert_int_eq(push(228), 1);
        ck_assert_double_eq_tol(pick(), 49, TOL_STRICT);

        for (int j = MAX_STACK_SIZE - 1; j >= 0; --j) {
            ck_assert_double_eq_tol(pop(), j, TOL_STRICT);
            if (j != 0) {
                ck_assert_double_eq_tol(pick(), j - 1, TOL_STRICT);
            } else {
                ck_assert_double_eq(pick(), -INFINITY);
            }
        }
        ck_assert_double_eq(pop(), -INFINITY);
        ck_assert_double_eq(pick(), -INFINITY);

    }
END_TEST

START_TEST (test_push)
    {
        for (int i = 0; i < MAX_STACK_SIZE; ++i) {
            ck_assert_int_eq(push(i), 0);
        }
        ck_assert_int_eq(push(228), 1);
        ck_assert_int_eq(push(228), 1);
        ck_assert_int_eq(push(228), 1);
        for (int j = MAX_STACK_SIZE - 1; j >= 0; --j) {
            ck_assert_double_eq_tol(pop(), j, TOL_STRICT);
        }
        ck_assert_double_eq(pop(), -INFINITY);

        //And then again
        for (int i = 0; i < MAX_STACK_SIZE; ++i) {
            ck_assert_int_eq(push(i), 0);
        }
        ck_assert_int_eq(push(228), 1);
        ck_assert_int_eq(push(228), 1);
        ck_assert_int_eq(push(228), 1);
        for (int j = MAX_STACK_SIZE - 1; j >= 0; --j) {
            ck_assert_double_eq_tol(pop(), j, TOL_STRICT);
        }
        ck_assert_double_eq(pop(), -INFINITY);
        ck_assert_int_eq(push(5), 0);
        ck_assert_double_eq_tol(pop(), 5, TOL_STRICT);
    }
END_TEST

Suite *str_suite(void) {
    Suite *suite = suite_create("stack");
    TCase *tcase = tcase_create("case");
    tcase_add_test(tcase, test_push);
    tcase_add_test(tcase, test_pop);
    tcase_add_test(tcase, test_peek);
    suite_add_tcase(suite, tcase);
    return suite;
}

int main(int argc, char *argv[]) {
    int number_failed;
    Suite *suite = str_suite();
    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return number_failed;
}