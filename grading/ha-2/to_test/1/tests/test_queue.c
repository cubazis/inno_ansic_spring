#include <check.h>
#include "priority_queue.h"

START_TEST (test_insert)
    {
        //test with ordered elements
        for (int i = 0; i < 100; i++) {
            ck_assert_int_eq(insert(i * 0.1, i), 0);
        }

        // test for max number of elements
        ck_assert_int_eq(insert(101.0, 1), 1);

        for (int i = 0; i < 100; i++) {
            ck_assert_double_eq(extract_min(), i * 0.1);
        }

        // test with reversed ordered elements
        for (int i = 100; i > 0; i--) {
            ck_assert_int_eq(insert(i * 0.1, i), 0);
        }

        // test for max number of elements
        ck_assert_int_eq(insert(0.1, 1), 1);

        for (int i = 1; i <= 100; i++) {
            ck_assert_double_eq(extract_min(), i * 0.1);
        }

        // test for stability
        ck_assert_int_eq(insert(5.1, 5), 0);
        ck_assert_int_eq(insert(1.1, 1), 0);
        ck_assert_int_eq(insert(2.1, 2), 0);
        ck_assert_int_eq(insert(3.1, 3), 0);
        ck_assert_int_eq(insert(1.2, 1), 0);
        ck_assert_int_eq(insert(4.1, 4), 0);
        ck_assert_int_eq(insert(3.2, 3), 0);
        ck_assert_int_eq(insert(1.3, 1), 0);
        ck_assert_int_eq(insert(1.4, 1), 0);
        ck_assert_double_eq(extract_min(), 1.1);
        ck_assert_double_eq(extract_min(), 1.2);
        ck_assert_double_eq(extract_min(), 1.3);
        ck_assert_double_eq(extract_min(), 1.4);
        ck_assert_double_eq(extract_min(), 2.1);
        ck_assert_double_eq(extract_min(), 3.1);
        ck_assert_double_eq(extract_min(), 3.2);
        ck_assert_double_eq(extract_min(), 4.1);
        ck_assert_double_eq(extract_min(), 5.1);


    }
END_TEST

START_TEST (test_min)
    {
        ck_assert_double_eq(extract_min(), -INFINITY);
        insert(9.9, 4);
        insert(3.3, 2);
        insert(5.5, 3);
        insert(7.7, 1);
        insert(11.1, 6);
        insert(13.3, 7);
        insert(1.1, 5);
        ck_assert_double_eq(extract_min(), 7.7);
        ck_assert_double_eq(extract_min(), 3.3);
        ck_assert_double_eq(extract_min(), 5.5);
        ck_assert_double_eq(extract_min(), 9.9);
        ck_assert_double_eq(extract_min(), 1.1);
        ck_assert_double_eq(extract_min(), 11.1);
        ck_assert_double_eq(extract_min(), 13.3);
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
