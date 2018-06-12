//
// Created by Максим on 31.05.2018.
//

#include <check.h>
#include "priority_queue.h"
#include <float.h>

START_TEST (pq) {
    ck_assert(insert(12, 1) == 0);
    ck_assert(insert(13, 0) == 0);
    ck_assert(extract_min() == 13);
    ck_assert(insert(14, 3) == 0);
    ck_assert(insert(15, 2) == 0);
    ck_assert(extract_min() == 12);
    ck_assert(extract_min() == 15);
    ck_assert(extract_min() == 14);
    ck_assert(extract_min() == -DBL_MAX);
}
END_TEST

Suite* str_suite (void) {
    Suite *suite = suite_create("pq");
    TCase *tcase = tcase_create("case");
    tcase_add_test(tcase, pq);
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
