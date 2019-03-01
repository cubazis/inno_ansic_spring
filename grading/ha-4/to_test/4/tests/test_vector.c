//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "vector.h"
#include <stdlib.h>

START_TEST(test_vector_create)
	{
		Vector* vector = vector_create(5, sizeof(int));
		ck_assert_int_eq(vector_get_size(vector), 0);
		ck_assert_int_eq(vector_get_capacity(vector), 5);
		ck_assert_int_eq(vector_get_item_size(vector), sizeof(int));

		Vector* vector1 = vector_create(10, sizeof(char));
		ck_assert_int_eq(vector_get_size(vector1), 0);
		ck_assert_int_eq(vector_get_capacity(vector1), 10);
		ck_assert_int_eq(vector_get_item_size(vector1), sizeof(char));
	}
END_TEST

START_TEST(test_vector_push)
	{
		Vector* vector = vector_create(5, sizeof(int));
		for (int i = 0; i < 100; ++i) {
			vector_push_back(vector, &i);
		}
		for (int i = 0; i < 100; ++i) {
			ck_assert_int_eq(*(int*)vector_get_element(vector, i), i);
		}

		Vector* vector1 = vector_create(10, sizeof(char));
		for (int i = 0; i < 26; ++i) {
			char ch = (char) ('a' + i);
			vector_push_back(vector1, &ch);
		}
		for (int i = 0; i < 26; ++i) {
			char ch = (char) ('a' + i);
			ck_assert(*(char*)vector_get_element(vector1, i) == ch);
		}
	}
END_TEST

START_TEST(test_vector_pop)
	{
		Vector* vector = vector_create(5, sizeof(int));
		for (int i = 0; i < 100; ++i) {
			vector_push_back(vector, &i);
		}
		for (int i = 0; i < 100; ++i) {
			int j = 0;
			vector_pop_back(vector, &j);
			ck_assert_int_eq(j, 99 - i);
		}

		Vector* vector1 = vector_create(10, sizeof(char));
		for (int i = 0; i < 26; ++i) {
			char ch = (char) ('a' + i);
			vector_push_back(vector1, &ch);
		}
		for (int i = 0; i < 26; ++i) {
			char j = 'a';
			vector_pop_back(vector1, &j);
			ck_assert(j == ('a' + 25 - i));
		}
	}
END_TEST

START_TEST(test_vector_get_elements)
	{
		Vector* vector = vector_create(5, sizeof(int));
		for (int i = 0; i < 100; ++i) {
			vector_push_back(vector, &i);
		}
		ck_assert_int_eq(*(int*)vector_get_begin(vector),0);
		ck_assert_int_eq(*(int*)vector_get_end(vector),99);


		Vector* vector1 = vector_create(10, sizeof(char));
		for (int i = 0; i < 26; ++i) {
			char ch = (char) ('a' + i);
			vector_push_back(vector1, &ch);
		}
		ck_assert(*(char*)vector_get_begin(vector1) == 'a');
		ck_assert(*(char*)vector_get_end(vector1) == 'z');
	}
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("Lab Session 4");
	TCase *tcase = tcase_create("case");


	tcase_add_test(tcase, test_vector_create);
	tcase_add_test(tcase, test_vector_push);
	tcase_add_test(tcase, test_vector_pop);
	tcase_add_test(tcase, test_vector_get_elements);

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