//
// Created by George Watson.
//

#include <check.h>
#include "stack.h"

START_TEST (test_stack)
        {
            // basic insert
            for (int i = 0; i < 50; i++)
                push(i);
            // check on fullness
            ck_assert_int_eq(1, push(50));
            // check top element
            ck_assert_int_eq(49, (int)pick());
            // clear
            for (int i = 0; i < 50; i++)
                pop();
            // check on emptiness
            ck_assert(isinf(pop()));
            // check on structure of stack
            push(1);
            for (int i = 0; i < 50; i++)
                push(i);
            ck_assert_int_eq(48, (int)pick());
        }
END_TEST

Suite* str_suite (void) {
    Suite *suite = suite_create("Home assignment 2");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_stack);

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