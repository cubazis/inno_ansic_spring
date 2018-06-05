//
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "pointers.h"
#include <stdlib.h>


int global;

START_TEST (test_ipd_etext)
{
	int local;

	void func(){
		printf("pointer to local var valid? %d\n", valid_etext(&local));
		printf("pointer to static var valid? %d\n", valid_etext(&global));
		printf("pointer to function valid? %d\n", valid_etext((void *)func));


		int *p = (int *) malloc(sizeof(int));
		printf("pointer to heap valid? %d\n", valid_etext(p));
		printf("pointer to end of allocated heap valid? %d\n", valid_etext(++p));
		free(--p);
		printf("pointer to freed heap valid? %d\n", valid_etext(p));
		printf("null pointer valid? %d\n", valid_etext(NULL));
	}


	func();
}
END_TEST


START_TEST (test_ipd_incr_bad)
{
	int *p = (int *) malloc(sizeof(int));
	printf("%p\n",p);
	incr_bad(p);
	printf("%p\n",p);
}
END_TEST

START_TEST (test_ipd_incr)
{
	int *p = (int *) malloc(sizeof(int));
	printf("%p\n",p);
	incr(p);
	printf("%p\n",p);
}
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("Lab Session 4");
	TCase *tcase = tcase_create("case");

	tcase_add_test(tcase, test_ipd_etext);

	tcase_add_test(tcase, test_ipd_incr_bad);

	tcase_add_test(tcase, test_ipd_incr);
	/** YOUT TEST CASES HERE */

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