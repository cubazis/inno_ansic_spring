//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include "stack.h"

START_TEST (test_pop)
    {
        ck_assert_double_eq(pop(), -INFINITY);
        push(3.3);
        push(7.7);
        push(1.1);
        push(5.5);
        push(9.9);
        ck_assert_double_eq(pop(), 9.9);
        ck_assert_double_eq(pop(), 5.5);
        ck_assert_double_eq(pop(), 1.1);
        ck_assert_double_eq(pop(), 7.7);
        ck_assert_double_eq(pop(), 3.3);
        ck_assert_double_eq(pop(), -INFINITY);
    }
END_TEST


START_TEST (test_peek)
    {
        ck_assert_double_eq(pick(), -INFINITY);
        push(1.1);
        push(3.3);
        push(5.5);
        push(7.7);
        push(9.9);
        ck_assert_double_eq(pick(), 9.9);
        pop();
        ck_assert_double_eq(pick(), 7.7);
        pop();
        ck_assert_double_eq(pick(), 5.5);
        pop();
        ck_assert_double_eq(pick(), 3.3);
        pop();
        ck_assert_double_eq(pick(), 1.1);
        pop();
        ck_assert_double_eq(pick(), -INFINITY);
    }
END_TEST

START_TEST (test_push)
    {
        for (int i = 0; i < 50; i++) {
            push(i * 0.1);
        }

        ck_assert_double_eq(push(51.0), 1);

        for (int i = 49; i >= 0; i--) {
            ck_assert_double_eq(pick(), i * 0.1);
            pop();
        }
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
