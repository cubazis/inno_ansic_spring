//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "vector_int.h"
#include <stdlib.h>
#include <stdio.h>

START_TEST(test_vector_create)
{
	Vector* vector = vector_create_int(5);
	ck_assert_int_eq(vector_get_size(vector), 0);
	ck_assert_int_eq(vector_get_capacity(vector), 5);
	ck_assert_int_eq(vector_get_item_size(vector), sizeof(int));
}
END_TEST

START_TEST(test_vector_push)
	{
		Vector* vector = vector_create_int(5);
		for (int i = 0; i < 100; ++i) {
			vector_push_back_int(vector, i);
		}
		for (int i = 0; i < 100; ++i) {
			ck_assert_int_eq(vector_get_element_int(vector, i), i);
		}
	}
END_TEST

START_TEST(test_vector_pop)
	{
		Vector* vector = vector_create_int(5);
		for (int i = 0; i < 100; ++i) {
			vector_push_back_int(vector, i);
		}
		for (int i = 0; i < 100; ++i) {
			ck_assert_int_eq(vector_pop_back_int(vector), 99 - i);
		}
	}
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("Lab Session 4");
	TCase *tcase = tcase_create("case");

	tcase_add_test(tcase, test_vector_create);
	tcase_add_test(tcase, test_vector_push);
	tcase_add_test(tcase, test_vector_pop);

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