#include <check.h>
#include "priority_queue.h"

START_TEST (test_queue)
    {

        for (int i = 1, j = 100; i <= 100, j >= 1; ++i, --j)
            ck_assert_int_eq(insert(i, j), 0);


        ck_assert_int_eq(insert(1337, 1337), 1);

        for (int k = 100; k >= 1; --k)
            ck_assert_double_eq(extract_min(), (double) k);

    }
END_TEST

Suite *str_suite(void) {
    Suite *suite = suite_create("Priority Queue");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_queue);

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