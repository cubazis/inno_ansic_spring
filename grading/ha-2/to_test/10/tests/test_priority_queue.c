#include "priority_queue.h"
#include <stdio.h>
#include <check.h>
#include <math.h>


double abs_d(double a) {
    return a > 0 ? a : -a;
}


void assert_double_eq(double a, double b) {
    double eps = 1e-9;
    ck_assert(abs_d(a - b) <= eps);
}


START_TEST(test_pq_1)

    {
        ck_assert_int_eq(0, insert(3, 1));
        ck_assert_int_eq(0, insert(4, 2));
        ck_assert_int_eq(0, insert(5.4, 7));

        assert_double_eq(3, extract_min());
        ck_assert_int_eq(0, insert(10.3, 1));
        assert_double_eq(10.3, extract_min());

        assert_double_eq(4, extract_min());
        assert_double_eq(5.4, extract_min());
    }

END_TEST


START_TEST(test_pq_2)

    {
        int code = 0, i = 0;
        do {
            code = insert(-1 * i / 100, i);
            i++;
        } while (code == 0);

        ck_assert_int_eq(i, 101);
        ck_assert_int_eq(1, insert(2.77, 5));
    }
END_TEST


START_TEST(test_pq_3)
    {
        int code = 0, i = 0;
        while (code == 0) {
            code = insert(-1 * i / 100, i);
            i++;
        }
        ck_assert_int_eq(1, insert(1, 1));

        while (!isinf(extract_min()));
        ck_assert_int_eq(0, insert(2, 4));
        assert_double_eq(2, extract_min());


        ck_assert(isinf(extract_min()));


    }

END_TEST


START_TEST(test_pq_4)

    {
        ck_assert_int_eq(0, insert(14, 3));
        ck_assert_int_eq(0, insert(15, 5));
        assert_double_eq(14, extract_min());
        assert_double_eq(15, extract_min());
        ck_assert(isinf(extract_min()));
    }

END_TEST


START_TEST(test_pq_5)

    {
        int code, i = 0;
        do {
            double ins = (double)i*(-1)/100;
            code = insert(ins, 100 - i);
            i++;
        } while (code == 0);

        ck_assert_int_eq(i, 101);
        ck_assert_int_eq(1, insert(2.77, 5));

        double extract = -5;
        do{
            ck_assert(extract < extract_min());
            extract = extract_min();
        } while(!isinf(extract));
    }
END_TEST

START_TEST(test_pq_6)

    {
        int i = 0;

        do {
            ck_assert(isinf(extract_min()));
            i++;
        } while (i < 10);
        ck_assert_int_eq(0, insert(12.5, 6));
        assert_double_eq(12.5, extract_min());
        i =  0;
        do {
            ck_assert(isinf(extract_min()));
            i++;
        } while (i < 10);
    }
END_TEST

START_TEST(test_pq_7)
    {
        ck_assert_int_eq(0, insert(14, 6));
        ck_assert_int_eq(0, insert(2, 3));
        assert_double_eq(2, extract_min());
        assert_double_eq(14, extract_min());
        ck_assert(isinf(extract_min()));
        ck_assert_int_eq(0, insert(2, 1));
        assert_double_eq(2, extract_min());
    }
END_TEST

Suite *test_suite(void) {

    Suite *suite = suite_create("PQ test suite");
    TCase *tCase = tcase_create("PQ test case");

    tcase_add_test(tCase, test_pq_1);
    tcase_add_test(tCase, test_pq_2);
    tcase_add_test(tCase, test_pq_3);
    tcase_add_test(tCase, test_pq_4);
    tcase_add_test(tCase, test_pq_5);
    tcase_add_test(tCase, test_pq_6);
    tcase_add_test(tCase, test_pq_7);

    suite_add_tcase(suite, tCase);
    return suite;

}




int main() {

    int number_failed;
    Suite *suite = test_suite();
    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return number_failed;
}