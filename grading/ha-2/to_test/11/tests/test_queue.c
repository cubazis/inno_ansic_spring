#include <check.h>
#include <math.h>
#include "priority_queue.h"

START_TEST (test_insert)
    {
        ck_assert(insert(10,1) == 0);
        ck_assert(insert(15,1) == 0);
        ck_assert(insert(20,1) == 0);
        ck_assert(extract_min() == 10);
    }
END_TEST

START_TEST(test_empty)
    {
        ck_assert(extract_min() == -INFINITY);
    }
END_TEST

START_TEST (test_extract1)
    {
        ck_assert(insert(20,1) == 0);
        ck_assert(insert(15,2) == 0);
        ck_assert(insert(10,3) == 0);
        ck_assert(extract_min() == 20);
    }
END_TEST

START_TEST (test_extract2)
    {
        ck_assert(insert(10,4) == 0);
        ck_assert(insert(15,3) == 0);
        ck_assert(insert(20,2) == 0);
        ck_assert(extract_min() == 20);
        ck_assert(extract_min() == 15);
        ck_assert(insert(30,1) == 0);
        ck_assert(extract_min() == 30);
    }
END_TEST

START_TEST(test_infinity_key)
    {
        ck_assert(insert(10.5,-INFINITY)==0);
        ck_assert(insert(11,-1000)==0);
        ck_assert(extract_min()==10.5);
    }
END_TEST

START_TEST(test_overflow)
    {
        for (int i=1;i<=100;++i){
            ck_assert(insert(i,-i)==0);
        }
        ck_assert(insert(0,0)==1);

    }
END_TEST

START_TEST(test_same_keys)
    {
        ck_assert(insert(4,5)==0);
        ck_assert(insert(6,5)==0);
        ck_assert(insert(1,5)==0);
        ck_assert(extract_min()==4);

    }
END_TEST

START_TEST(test_same_values)
    {
        ck_assert(insert(1.1,5)==0);
        ck_assert(insert(1.1,5)==0);
        ck_assert(insert(1.10,5)==0);
        ck_assert_double_eq_tol(extract_min(),1.1,0.01);
        ck_assert_double_eq_tol(extract_min(),1.1,0.01);
        ck_assert_double_eq_tol(extract_min(),1.1,0.01);
        ck_assert(extract_min()==-INFINITY);

    }
END_TEST

Suite *str_suite(void) {
    Suite *suite = suite_create("Home assignment 2");
    TCase *tcase = tcase_create("case");


    tcase_add_test(tcase, test_insert);
    tcase_add_test(tcase, test_empty);
    tcase_add_test(tcase, test_extract1);
    tcase_add_test(tcase, test_extract2);
    tcase_add_test(tcase, test_infinity_key);
    tcase_add_test(tcase, test_overflow);
    tcase_add_test(tcase, test_same_keys);
    tcase_add_test(tcase, test_same_values);


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