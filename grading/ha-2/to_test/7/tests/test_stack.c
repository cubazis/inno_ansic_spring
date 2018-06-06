#include <check.h>
#include "stack.h"

START_TEST (test_stub)
    {

        for (int i = 1; i <= 50; i++)
            ck_assert_int_eq(push(i), 0);


        ck_assert_int_eq(push(1337), 1);

        for (int j = 50; j >= 1; --j) {
            ck_assert_double_eq(peek(), (double) j);
            ck_assert_double_eq(pop(), (double) j);
        }

    }
END_TEST

Suite *str_suite(void) {
    Suite *suite = suite_create("Stack");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_stub);

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