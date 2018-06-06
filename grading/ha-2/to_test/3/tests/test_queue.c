#include <check.h>
#include "priority_queue.h"

#define TOL_STRICT 1e-9

START_TEST (test_insert)
    {
        for (int i = MAX_QUEUE_SIZE - 1; i >= 0; --i) {
            ck_assert_int_eq(insert(i * 10, i), 0);
        }
        ck_assert_int_eq(insert(-10, -1), 1);
        ck_assert_double_eq_tol(extract_min(), 0, TOL_STRICT);
        ck_assert_int_eq(insert(0, 0), 0);
        ck_assert_int_eq(insert(-100, -100), 1);
        ck_assert_int_eq(insert(5000, 500), 1);
        ck_assert_int_eq(insert(7000, 700), 1);

        for (int i = 0; i < MAX_QUEUE_SIZE; ++i) {
            ck_assert_double_eq_tol(extract_min(), i * 10, TOL_STRICT);
        }
        ck_assert_double_eq(extract_min(), -INFINITY);

    }
END_TEST

START_TEST (test_min)
    {
        ck_assert_int_eq(insert(20, 2), 0);
        ck_assert_int_eq(insert(10, 1), 0);
        ck_assert_int_eq(insert(30, 3), 0);
        ck_assert_double_eq_tol(extract_min(), 10, TOL_STRICT);
        ck_assert_int_eq(insert(0, 0), 0);
        ck_assert_double_eq_tol(extract_min(), 0, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 20, TOL_STRICT);
        ck_assert_int_eq(insert(50, 5), 0);
        ck_assert_int_eq(insert(1000, 100), 0);
        ck_assert_int_eq(insert(500, 50), 0);
        ck_assert_double_eq_tol(extract_min(), 30, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 50, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 500, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 1000, TOL_STRICT);
        ck_assert_double_eq(extract_min(), -INFINITY);

        //Do this again
        ck_assert_int_eq(insert(2, 2), 0);
        ck_assert_int_eq(insert(1, 1), 0);
        ck_assert_int_eq(insert(3, 3), 0);
        ck_assert_double_eq_tol(extract_min(), 1, TOL_STRICT);
        ck_assert_int_eq(insert(0, 0), 0);
        ck_assert_double_eq_tol(extract_min(), 0, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 2, TOL_STRICT);
        ck_assert_int_eq(insert(5, 5), 0);
        ck_assert_int_eq(insert(100, 100), 0);
        ck_assert_int_eq(insert(50, 50), 0);
        ck_assert_double_eq_tol(extract_min(), 3, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 5, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 50, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 100, TOL_STRICT);

        ck_assert_int_eq(insert(100, 100), 0);
        ck_assert_int_eq(insert(80, 80), 0);
        ck_assert_int_eq(insert(90, 90), 0);
        ck_assert_int_eq(insert(50, 50), 0);
        ck_assert_int_eq(insert(40, 40), 0);
        ck_assert_int_eq(insert(20, 20), 0);
        ck_assert_int_eq(insert(60, 60), 0);
        ck_assert_int_eq(insert(45, 45), 0);
        ck_assert_int_eq(insert(10, 10), 0);


        ck_assert_double_eq_tol(extract_min(), 10, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 20, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 40, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 45, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 50, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 60, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 80, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 90, TOL_STRICT);
        ck_assert_double_eq_tol(extract_min(), 100, TOL_STRICT);

        for (int i = 0; i < 20; ++i) {
            ck_assert_int_eq(insert(i, 1), 0);
        }

        ck_assert_int_eq(insert(56, 2), 0);
        ck_assert_int_eq(insert(44, 0), 0);
        ck_assert_double_eq_tol(extract_min(), 44, TOL_STRICT);

        for (int i = 0; i < 20; ++i) {
            ck_assert_double_eq_tol(extract_min(), i, TOL_STRICT);
        }
        ck_assert_double_eq_tol(extract_min(), 56, TOL_STRICT);

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