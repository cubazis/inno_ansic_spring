//
// Created by cubazis on 05.06.18.
//

#include <check.h>
#include "pointers.h"
#include <stdlib.h>

START_TEST (test_ipd_1)
{
	int* ptr1, ptr2;

	ck_assert(valid(ptr1));
	ck_assert(valid(ptr2));
}
END_TEST

START_TEST (test_ipd_2)
{
	int* ptr1, *ptr2;

	ck_assert(valid(ptr1));
	ck_assert(valid(ptr2));
}
END_TEST

START_TEST(test_wild_ptr)
{
	int *pi;
	//int ia[4] = {1, 3, 3, 7};
	printf("%d\n",*pi);
}
END_TEST

START_TEST(test_wild_ptr_char)
{
	char *ptr;
	//int ia[4] = {1, 3, 3, 7};
	printf("%d\n",*ptr);
}
END_TEST

START_TEST(test_uninitialized_ptrs)
{
	int *pi = NULL;
	if(pi == NULL) {
		printf("pointer is NULL\n");
	} else {
		printf("pointer is not NULL\n");
	}
}
END_TEST

START_TEST(test_dangling)
{
	char firstName[8] = "_______";
	char middleName[8] = "_______";
	char lastName[8] = "_______";

	middleName[-11] = 'X';
	middleName[0] = 'X';
	middleName[18] = 'X';

	printf("%p %s\n", firstName,firstName);
	printf("%p %s\n", middleName,middleName);
	printf("%p %s\n", lastName,lastName);
}
END_TEST

START_TEST(test_array_size)
{
	char name[8];
	strcpy(name,"Alexander");
	replace(name,'+',sizeof(name));
	printf("%s\n", name);
}
END_TEST

START_TEST(test_sizeof)
{
	int buffer[20];
	int *pbuffer = buffer;
	for(int i=0; i<sizeof(buffer); i++) {
		*(pbuffer++) = 0;
	}
}
END_TEST

START_TEST(test_ptr_match)
{
	int num = 2147483647;
	int *pi = &num;
	short *ps = (short*)pi;
	short *pss = pi;
	printf("pi: %p Value(16): %x Value(10): %d\n", pi, *pi, *pi);
	printf("ps: %p Value(16): %hx Value(10): %hd\n",
	       ps, (unsigned short)*ps, (unsigned short)*ps);

	//printf("pi: %p Value(16): %x Value(10): %d\n", pss, *pss, *pss);
}
END_TEST



Suite* str_suite (void) {
	Suite *suite = suite_create("Lab Session 4");
	TCase *tcase = tcase_create("case");

	tcase_add_test(tcase, test_ipd_1);
	tcase_add_test(tcase, test_ipd_2);
	tcase_add_test(tcase, test_wild_ptr);
	tcase_add_test(tcase, test_wild_ptr_char);
	tcase_add_test(tcase, test_uninitialized_ptrs);
	tcase_add_test(tcase, test_dangling);
	tcase_add_test(tcase, test_array_size);
	tcase_add_test(tcase, test_sizeof);
	tcase_add_test(tcase, test_ptr_match);

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