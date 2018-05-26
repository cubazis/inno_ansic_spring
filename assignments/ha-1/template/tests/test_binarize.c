//
// Created by cubazis on 24.05.18.
//
#include <check.h>
#include "binarize.h"

#ifndef COMPARATOR
#define COMPARATOR(res, c1, c2) do                    \
	{                                             \
		char i = 0;                           \
		for (;'\0' != (c1)[i];i++)            \
		{                                     \
			if((c1)[i] != (c2)[i])        \
				{                     \
                                        (res) = 0;    \
				}                     \
		}                                     \
	} while(0)
#endif

START_TEST (test_bin_u)
{
	unsigned long x = 1608637542;
	char* output = binarize_u(x);
	char* pattern = "01011111111000011101110001100110";
	int k = 1;
	COMPARATOR(k, output, pattern);
	ck_assert(1 == k);
	//printf("%s\n", output);
}
END_TEST

START_TEST (test_bin_s)
{
	signed long x = -1608637542;
	char* output = binarize_s(x);
	char* pattern = "10100000000111100010001110011010";
	int k = 1;
	COMPARATOR(k, output, pattern);
	ck_assert(1 == k);
	//printf("%s\n", output);
}
END_TEST

Suite* str_suite (void) {
	Suite *suite = suite_create("binarize");
	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test_bin_u);
	tcase_add_test(tcase, test_bin_s);
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