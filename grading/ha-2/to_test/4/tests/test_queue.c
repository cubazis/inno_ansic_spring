#include <check.h>
#include "priority_queue.h"

START_TEST (test_insert)
    {
        for (int i = 0; i < 100; i++) {
            ck_assert_int_eq(insert(i * 1.0, i), 0);
        }

        ck_assert_int_eq(insert(0, 1), 1);

        for (int i = 0; i < 100; i++) {
            ck_assert_double_eq(extract_min(), i * 1.0);
        }
    }
END_TEST

START_TEST (test_min)
    {
        ck_assert_double_eq(extract_min(), -INFINITY);
        insert(1.0, 2);
        insert(2.0, 3);
        insert(3.0, 1);
        ck_assert_double_eq(extract_min(), 3.0);
        ck_assert_double_eq(extract_min(), 1.0);
        ck_assert_double_eq(extract_min(), 2.0);
        ck_assert_double_eq(extract_min(), -INFINITY);
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