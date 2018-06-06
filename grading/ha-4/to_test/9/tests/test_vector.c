//vector_create
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "vector.h"
#include <stdlib.h>

START_TEST(test_vector_create)
{

}
END_TEST


Suite* str_suite (void) {
	Suite *suite = suite_create("Lab Session 4");
	TCase *tcase = tcase_create("case");


	tcase_add_test(tcase, test_vector_create);

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