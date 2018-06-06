//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "vector.h"
#include "stdio.h"

START_TEST(test_vector_create)
{
	size_t capacity = 50;
	Vector * v  = vector_create(capacity, sizeof (int));
	printf("%d\n", (int) vector_get_capacity(v));
	printf("%d\n", (int) vector_get_size(v));
	printf("%d\n", (int) vector_get_item_size(v));
	printf("%d\n", (int) vector_get_begin(v));
	printf("%d\n", (int) vector_get_end(v));
}
END_TEST

START_TEST(test_vector_insert)
{
	size_t capacity = 5;
	Vector *v;
	v = vector_create(capacity, sizeof (int));
	printf("%d\n", (int) vector_get_capacity(v));
	printf("%d\n", (int) vector_get_size(v));
	vector_push_back(v, (const void *) 3);
}
END_TEST


Suite* str_suite (void) {
	Suite *suite = suite_create("Lab Session 4");
	TCase *tcase = tcase_create("case");


	//tcase_add_test(tcase, test_vector_create);
	tcase_add_test(tcase, test_vector_insert);

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