//
// Created by yaskev on 31.05.2018
//

#include <check.h>
#include "stdlib.h"
#include "../src/stack.h"

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


START_TEST(test_stack)
    {
        push(4);
        ck_assert(pick() == 4);

        push(5);
        ck_assert(pick() == 5);

        pop();
        ck_assert(pick() == 4);

    }
END_TEST

START_TEST(test_underflow)
    {
        ck_assert(pop() < -1e100);
    }
END_TEST

START_TEST(test_overflow)
    {
        for (int i = 0; i < 50; ++i)
            push(i);

        ck_assert(push(567) == 1);
    }
END_TEST

/** YOUR TEST CASES HERE */


Suite *str_suite(void) {
    Suite *suite = suite_create("Home assignment 2");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_stack);
    tcase_add_test(tcase, test_overflow);
    tcase_add_test(tcase, test_underflow);


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
