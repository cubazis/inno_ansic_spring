#include <check.h>
#include "../headers/stack.h"

START_TEST (stack_test)
{
    STACK* s = create_stack();

    stack_put(s, 1);
    stack_put(s, 2);
    stack_put(s, 3);

    ck_assert(stack_pull(s) == 3);
    ck_assert(stack_peek(s) == 2);
    ck_assert(stack_size(s) == 2);

    delete_stack(s);
}
END_TEST

Suite* str_suite (void)
{
    Suite *suite = suite_create("Home Assignment 2: Stack");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, stack_test);

    suite_add_tcase(suite, tcase);
    return suite;
}

int main (int argc, char *argv[])
{
    int number_failed;
    Suite *suite = str_suite();

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);

    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return number_failed;
}