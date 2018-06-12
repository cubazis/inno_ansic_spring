//
// Created by George Watson.
//


#include <check.h>
#include "priority_queue.h"

START_TEST (test_queue)
    {
        // basic checks
        insert(12, 1);
        insert(13, 2);
        insert(14, 1);
        ck_assert_int_eq(12, (int)extract_min());
        ck_assert_int_eq(14, (int)extract_min());
        ck_assert_int_eq(13, (int)extract_min());
        // normal insertion
        for (int i = 0; i < 100; ++i)
            insert(MAXFLOAT, i);
        // free storage
        for (int i = 0; i < 100; ++i)
            ck_assert_float_eq(MAXFLOAT, extract_min());
        // inverse insertion
        for (int i = 0; i < 100; ++i)
            insert(i, 100 - i);
        // check on full queue
        ck_assert_int_eq(1, insert(1,1));
        // free storage
        for (int i = 99; i > -1; --i)
            ck_assert_int_eq(i, (int)extract_min());
        // check on emptiness
        ck_assert(isinf(extract_min()));
    }
END_TEST

Suite* str_suite (void) {
    Suite *suite = suite_create("Home assignment 2");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_queue);

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