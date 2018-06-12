#include <check.h>
#include <math.h>
#include "stack.h"

START_TEST (test_push)
    {
        struct Node * root;
        push(228.0);
        push(1337.0);
        ck_assert_double_eq_tol(pop(), 1337.0, 0.01);
        push(211);
        ck_assert_double_eq_tol(pop(), 211.0, 0.01);
        ck_assert_double_eq_tol(pop(), 228.0, 0.01);
        ck_assert_double_eq(pop(), -INFINITY);
    }

    {
        struct Node * root;
        push(1);
        push(9);
        ck_assert_double_eq_tol(pick(), 9, 0.01);
        ck_assert_double_eq_tol(pop(), 9, 0.01);
        ck_assert_double_eq_tol(pick(), 1, 0.01);
        ck_assert_double_eq_tol(pop(), 1, 0.01);
        ck_assert_double_eq_tol(pick(), -INFINITY);
    }

    {
        struct Node * root;
        ck_assert_double_eq(push(1), 0);
        ck_assert_double_eq(push(2), 0);
        ck_assert_double_eq(push(3), 0);
        ck_assert_double_eq(push(4), 0);
        ck_assert_double_eq(push(5), 0);
        ck_assert_double_eq(push(6), 0);
        ck_assert_double_eq(push(7), 0);
        ck_assert_double_eq(push(8), 0);
        ck_assert_double_eq(push(9), 0);
        ck_assert_double_eq(push(0), 0);
        ck_assert_double_eq(push(1), 0);
        ck_assert_double_eq(push(2), 0);
        ck_assert_double_eq(push(3), 0);
        ck_assert_double_eq(push(4), 0);
        ck_assert_double_eq(push(5), 0);
        ck_assert_double_eq(push(6), 0);
        ck_assert_double_eq(push(7), 0);
        ck_assert_double_eq(push(8), 0);
        ck_assert_double_eq(push(9), 0);
        ck_assert_double_eq(push(0), 0);
        ck_assert_double_eq(push(1), 0);
        ck_assert_double_eq(push(2), 0);
        ck_assert_double_eq(push(3), 0);
        ck_assert_double_eq(push(4), 0);
        ck_assert_double_eq(push(5), 0);
        ck_assert_double_eq(push(6), 0);
        ck_assert_double_eq(push(7), 0);
        ck_assert_double_eq(push(8), 0);
        ck_assert_double_eq(push(9), 0);
        ck_assert_double_eq(push(0), 0);
        ck_assert_double_eq(push(1), 0);
        ck_assert_double_eq(push(2), 0);
        ck_assert_double_eq(push(3), 0);
        ck_assert_double_eq(push(4), 0);
        ck_assert_double_eq(push(5), 0);
        ck_assert_double_eq(push(6), 0);
        ck_assert_double_eq(push(7), 0);
        ck_assert_double_eq(push(8), 0);
        ck_assert_double_eq(push(9), 0);
        ck_assert_double_eq(push(0), 0);
        ck_assert_double_eq(push(1), 0);
        ck_assert_double_eq(push(2), 0);
        ck_assert_double_eq(push(3), 0);
        ck_assert_double_eq(push(4), 0);
        ck_assert_double_eq(push(5), 0);
        ck_assert_double_eq(push(6), 0);
        ck_assert_double_eq(push(7), 0);
        ck_assert_double_eq(push(8), 0);
        ck_assert_double_eq(push(9), 0);
        ck_assert_double_eq(push(0), 0);
        ck_assert_double_eq(push(1), 1);
        ck_assert_double_eq(push(2), 1);
        ck_assert_double_eq(push(3), 1);
        ck_assert_double_eq(push(4), 1);
    }

END_TEST

Suite *str_suite(void) {
    Suite *suite = suite_create("Home assignment 2");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_push);


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