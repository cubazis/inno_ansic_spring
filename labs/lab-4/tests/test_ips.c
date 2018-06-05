//
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "pointers.h"
#include <stdlib.h>



START_TEST(test_structers)
{
	Employee employee;
	// Initialize eployee
	char *ptr = employee.name;
	printf("%p\n", ptr);
	ptr += sizeof(employee.name);
	printf("%p\n", ptr);
}
END_TEST

START_TEST(test_structers_2)
{
	// Not guaranteed to work
	Item part = {12345, 35, 107};
	int *pi = &part.partNumber;
	printf("Part number: %d\n",*pi);
	pi++;
	printf("Quantity: %d\n",*pi);
	pi++;
	printf("Bin number: %d\n",*pi);
}
END_TEST

START_TEST(test_structers_2_better)
{
	Item part = {12345, 35, 107};
	int *pi = &part.partNumber;
	printf("Part number: %d\n",*pi);
	pi = &part.quantity;
	printf("Quantity: %d\n",*pi);
	pi = &part.binNumber;
	printf("Bin number: %d\n",*pi);
}
END_TEST

START_TEST(test_structers_2_much_more_better)
{
	Item part = {12345, 35, 107};
	printf("Part number: %d\n",part.partNumber);
	printf("Quantity: %d\n",part.quantity);
	printf("Bin number: %d\n",part.binNumber);
}
END_TEST

START_TEST(test_functions)
{
	if(getSystemStatus() == 0) {
		printf("Status is 0\n");
	} else {
		printf("Status is not 0\n");
	}
}
END_TEST

START_TEST(test_functions_2)
{
	if(getSystemStatus == 0) {
		printf("Status is 0\n");
	} else {
		printf("Status is not 0\n");
	}
}
END_TEST

START_TEST(test_functions_signatures)
{
	int (*fptrCompute)(int,int);
	int add(int n1, int n2, int n3) {
		return n1+n2+n3;
	}
	fptrCompute = add;
	printf("%d\n", fptrCompute(2,5));
}
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("Lab Session 4");
	TCase *tcase = tcase_create("case");

	tcase_add_test(tcase, test_structers);
	tcase_add_test(tcase, test_structers_2);
	tcase_add_test(tcase, test_structers_2_better);
	tcase_add_test(tcase, test_structers_2_much_more_better);
	tcase_add_test(tcase, test_functions);
	tcase_add_test(tcase, test_functions_2);
	tcase_add_test(tcase, test_functions_signatures);


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