//
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "pointers.h"
#include <stdlib.h>

START_TEST(test_double_free)
{
	int *pi = (int*) malloc(sizeof(int));
	*pi = 5;
	free(pi);

	int sum = 0;
	for (int i = 0; i < 14; ++i) {
		sum += i;
	}
	free(pi);
}
END_TEST

START_TEST(test_clearing_data)
{
	char name[32];
	int userID;
	char *securityQuestion;

	for (int i = 0; i < 32; ++i) {
		name[i] = (char)i;
	}
	userID = 42;
	securityQuestion = name;

	memset(name,0,sizeof(name));
	userID = 0;
	memset(securityQuestion,0,strlen(securityQuestion));
}
END_TEST

START_TEST(test_clearing_data_2)
{
	char *name = (char*)malloc(32* sizeof(char));
	for (int i = 0; i < 32; ++i) {
		name[i] = (char)i;
	}
	memset(name,0,sizeof(name));
	free(name);
}
END_TEST


Suite* str_suite (void) {
	Suite *suite = suite_create("Lab Session 4");
	TCase *tcase = tcase_create("case");


	tcase_add_test(tcase, test_double_free);
	tcase_add_test(tcase, test_clearing_data);
	tcase_add_test(tcase, test_clearing_data_2);


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