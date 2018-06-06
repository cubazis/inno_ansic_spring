#include <check.h>
#include "../src/dll.h"



/** YOUT TEST CASES HERE
 *
 *  please use 'test_fname' format for naming tcases
 *  fname is function name
 *
 *  if function name is 'detab' then test case is 'test_detab'
 * */

START_TEST (test_construct)
    {
        ck_assert(1);
    }
END_TEST

START_TEST (test_destroy)
    {
        ck_assert(1);
    }
END_TEST

START_TEST (test_pushback)
    {
        ck_assert(1);
    }
END_TEST

START_TEST (test_pushfront)
    {
        ck_assert(1);
    }
END_TEST

START_TEST (test_popback)
    {
        ck_assert(1);
    }
END_TEST

START_TEST (test_popfront)
    {
        ck_assert(1);
    }
END_TEST


START_TEST (test_size)
    {
        ck_assert(1);
    }
END_TEST

Suite *str_suite(void) {
    Suite *suite = suite_create("Home assignment 1");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_construct);
    tcase_add_test(tcase, test_destroy);
    tcase_add_test(tcase, test_pushback);
    tcase_add_test(tcase, test_pushfront);
    tcase_add_test(tcase, test_popback);
    tcase_add_test(tcase, test_popfront);
    tcase_add_test(tcase, test_size);

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