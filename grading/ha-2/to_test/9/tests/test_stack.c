//
// Created by Максим on 31.05.2018.
//

#include <check.h>
#include "stack.h"
#include <float.h>

START_TEST (stack) {
    ck_assert(push(1.0) == 0);
    ck_assert(push(2.0) == 0);
    ck_assert(pick() == 2.0);
    ck_assert(push(3.0) == 0);
    ck_assert(pop() == 3.0);
    ck_assert(pop() == 2.0);
    ck_assert(pop() == 1.0);
    ck_assert(pick() == -DBL_MAX);
    ck_assert(pop() == -DBL_MAX);
}
END_TEST

Suite *str_suite(void) {
    Suite *suite = suite_create("stack");
    TCase *tcase = tcase_create("case");
    tcase_add_test(tcase, stack);
    suite_add_tcase(suite, tcase);
    return suite;
}

int main() {
    int number_failed;
    Suite *suite = str_suite();
    SRunner *runner = srunner_create(suite);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return number_failed;
}