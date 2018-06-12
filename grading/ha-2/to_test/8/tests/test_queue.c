//
// Created by bogdan on 6/1/18.
//

#include <check.h>
#include "priority_queue.h"

START_TEST (test_insert)
    {
        for (int i = 0; i < 100; ++i) {
            ck_assert(insert(i, i) == 0);
        }

        ck_assert(insert(14, 88) == 1);
        extract_min();
        ck_assert(insert(3, 9) == 0);
    }
END_TEST

START_TEST (test_min)
    {
        ck_assert(insert(10.1, 3) == 0);
        ck_assert(insert(20.2, 7) == 0);
        ck_assert(insert(30.3, 10) == 0);
        ck_assert(insert(40.4, 13) == 0);
        ck_assert(insert(50.5, 9) == 0);
        ck_assert(insert(530.5, -11) == 0);
        ck_assert(insert(250.5, 4) == 0);

        ck_assert(extract_min() == 530.5);
        ck_assert(extract_min() == 10.1);
        ck_assert(extract_min() == 250.5);
        ck_assert(extract_min() == 20.2);
        ck_assert(extract_min() == 50.5);
        ck_assert(extract_min() == 30.3);
        ck_assert(extract_min() == 40.4);
        ck_assert(extract_min() == -INFINITY);
    }
END_TEST

Suite *str_suite(void) {
    Suite *suite = suite_create("priority queue");
    TCase *tcase = tcase_create("case");
    tcase_add_test(tcase, test_insert);
    tcase_add_test(tcase, test_min);
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