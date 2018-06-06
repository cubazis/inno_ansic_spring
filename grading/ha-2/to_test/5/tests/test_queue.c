//
// Created by yaskev on 31.05.2018
//

#include <check.h>
#include "../src/priority_queue.h"
#include "math.h"

#define EPS 1e-8

#ifndef COMPARATOR
#define COMPARATOR(res, c1, c2) do                    \
    {                                             \
        int i = 0;                           \
        for (;'\0' != (c1)[i];i++)            \
        {                                     \
            if((c1)[i] != (c2)[i])        \
                {                     \
                                        (res) = 0;    \
                }                     \
        }                                     \
    } while(0)
#endif


START_TEST(test_queue)
    {
        insert(1.0, 5);
        insert(2, 4);
        insert(3, 3);
        insert(4, 2);
        insert(5, 1);

        double x = extract_min();
        ck_assert(fabs(x - 5) < EPS);
        x = extract_min();
        ck_assert(fabs(x - 4) < EPS);
        x = extract_min();
        ck_assert(fabs(x - 3) < EPS);
        x = extract_min();
        ck_assert(fabs(x - 2) < EPS);
        x = extract_min();
        ck_assert(fabs(x - 1) < EPS);
    }
END_TEST

START_TEST(test_overflow)
    {
        for (int i = 0; i < 100; ++i)

            insert(i, 100 - i);

        ck_assert(insert(1, 1) == 1);
    }
END_TEST

START_TEST(test_underflow)
    {
        ck_assert(extract_min() < -1e100);
    }
END_TEST

START_TEST(test_same_keys)
    {
        insert(1, 1);
        insert(2, 1);
        insert(3, 1);
        insert(4, 1);
        insert(5, 1);

        double x = extract_min();
        ck_assert(fabs(x - 1) < EPS);
        x = extract_min();
        ck_assert(fabs(x - 2) < EPS);
        x = extract_min();
        ck_assert(fabs(x - 3) < EPS);
        x = extract_min();
        ck_assert(fabs(x - 4) < EPS);
        x = extract_min();
        ck_assert(fabs(x - 5) < EPS);
    }
END_TEST


/** YOUR TEST CASES HERE */


Suite *str_suite(void) {
    Suite *suite = suite_create("Home assignment 2");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_queue);
    tcase_add_test(tcase, test_overflow);
    tcase_add_test(tcase, test_underflow);
    tcase_add_test(tcase, test_same_keys);

    /** YOUT TEST CASES HERE */

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

