#include <check.h>
#include <stdio.h>
#include "../headers/priority_queue.h"

// TODO

START_TEST (queue_test)
{
    PQ* q = create_pq();

    pq_insert(q, 1, 3);
	pq_insert(q, 2, 2);
	pq_insert(q, 3, 4);
	pq_insert(q, 4, 1);

	ck_assert(pq_extract_head(q) == 3);
	ck_assert(pq_extract_head(q) == 1);
	ck_assert(pq_extract_head(q) == 2);
	ck_assert(pq_extract_head(q) == 4);

	delete_pq(q);
}
END_TEST

Suite* str_suite (void)
{
    Suite *suite = suite_create("Home Assignment 2: Queue");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, queue_test);

    suite_add_tcase(suite, tcase);
    return suite;
}

int main (int argc, char *argv[]) {
    int number_failed;
    Suite *suite = str_suite();

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);

    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return number_failed;
}