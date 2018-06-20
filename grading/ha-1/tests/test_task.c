/**
 * cubazis stuff
 */


#include <check.h>
#include "math.h"
#include "task.h"
#include "limits.h"

#ifndef TOL
#define TOL 1e-8
#endif

#ifndef ck_assert_double_eq
#define ck_assert_double_eq(val, ref) \
  ck_assert(fabs(((val))-((ref))) < TOL);
#endif

char *replace(const char *s, char ch, const char *repl) {
	int count = 0;
	const char *t;
	for(t=s; *t; t++)
		count += (*t == ch);

	//printf("count %d\n", count);

	size_t rlen = strlen(repl);

	char *res = malloc(strlen(s) + (rlen-1)*count + 1);
	char *ptr = res;
	for(t=s; *t; t++) {
		if(*t == ch) {
			memcpy(ptr, repl, rlen);
			ptr += rlen;
		} else {
			*ptr++ = *t;
		}
	}
	*ptr = 0;
	return res;
}

START_TEST (test_detab)
{
	ck_assert_str_eq(detab(""), "");
	ck_assert_str_eq(detab(" "), " ");
	ck_assert_str_eq(detab("\t"), "    ");
	ck_assert_str_eq(detab("xx\tx"), "xx    x");
	ck_assert_str_eq(detab("xx\t\tx"), "xx        x");
	ck_assert_str_eq(detab("\t\t\t"), "            ");
	ck_assert_str_eq(detab("xx\txx\nxx\t\n"), "xx    xx\nxx    \n");
}
END_TEST

START_TEST (test_entab)
{
	ck_assert_str_eq(entab(""), "");
	ck_assert_str_eq(entab("  "), "");
	ck_assert_str_eq(entab("    "), "");
	ck_assert_str_eq(entab("     "), "");
	ck_assert_str_eq(entab("a b "), "a b");
	ck_assert_str_eq(entab("a b \n"), "a b \n");
	ck_assert_str_eq(entab("abc    a\n"), "abc\ta\n");
	ck_assert_str_eq(entab("abc     a\n"), "abc\t a\n");
	ck_assert_str_eq(entab("a    b     c     a\n"), "a\t  b\t\tc\t  a\n");
}
END_TEST

START_TEST (test_enter)
{
	char * pattern = "asdf\n"
		"ghjk\n"
		"zxcv\n"
		"bn";
	ck_assert_str_eq(enter(4, "asdfghjkzxcvbn"), pattern);
}
END_TEST

START_TEST (test_flush)
{
	char *code = "/** Данный блок кода необходим для проверки */\n"
		"void main(void){\n"
		"    /* комментарий 1 */\n"
		"    int c;\n"
		"    /** комментарий 2 **/\n"
		"    c = 42;\n"
		"    /** комментарий 3 */\n"
		"    printf(\"\\' \\\\\"); // комментарий 4\n"
		"    // комментарий 5\n"
		"    printf(\"%d\", c);\n"
		"}";

	char* pattern = "\n"
		"void main(void){\n"
		"    \n"
		"    int c;\n"
		"    \n"
		"    printf(\"\\' \\\\\"); \n"
		"    \n"
		"    printf(\"%d\", c);\n"
		"}";

	ck_assert_str_eq(flush(code), pattern);

}
END_TEST

START_TEST (test_htoi)
{
	ck_assert_int_eq(htoi("0x1f"), 31);
}
END_TEST

START_TEST (test_squeeze)
{
	ck_assert_str_eq(squeeze("asdfgahajak", "ghjk"), "asdfaaa");
}
END_TEST

START_TEST (test_any)
{
	ck_assert_int_eq(any("&^$#*&%#", "*"), 4);
	ck_assert_int_eq(any("&^$#*&%#", "%*&"), 6);
}
END_TEST

START_TEST (test_setbits)
{
	ck_assert_int_eq(65535, setbits(255, 15, 8, 255));
}
END_TEST

START_TEST (test_binsearch)
{
	int v[] = {2, 2, 8, 1, 3, 3, 7};
	ck_assert_int_eq(5, binsearch(3, v, 7));
}
END_TEST

START_TEST (test_escape)
{
	ck_assert_str_eq(escape("abc\t\n\b\v\r\a\f\?\\\'\""), "abc\\t\\n\\b\\v\\r\\a\\f\\?\\\\\\'\\\"");
}
END_TEST

START_TEST (test_expand)
{
	ck_assert_str_eq(expand("a-d-e"), "abcde");
	ck_assert_str_eq(expand("-a-d-e"), "-abcde");
	ck_assert_str_eq(expand("a-d-e-"), "abcde-");
	ck_assert_str_eq(expand("a-z0-c"), "abcdefghijklmnopqrstuvwxyz0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc");
}
END_TEST

START_TEST (test_itoa)
{
	ck_assert_str_eq(itoa(INT_MIN), "-2147483648");

}
END_TEST

START_TEST (test_itob)
{
	ck_assert_str_eq(itob(10,2), "1010");
	ck_assert_str_eq(itob(1337,2), "10100111001");
	ck_assert_str_eq(itob(-1337,2), "-10100111001");
	ck_assert_str_eq(itob(1337,3), "1211112");
	ck_assert_str_eq(itob(-1337,3), "-1211112");

}
END_TEST

START_TEST (test_strrindex)
{
	ck_assert_int_eq(strrindex("1337t 1l3e3e7t", "7t"), 12);
	ck_assert_int_eq(strrindex("onetwoone", "one"), 6);
}
END_TEST

START_TEST (test_atofe)
{
	ck_assert_double_eq(atofe("3.14e2"), 314);
	ck_assert_double_eq(atofe("314e-2"), 3.14);
	ck_assert_double_eq(atofe("3.14e-2"), 0.0314);
	ck_assert_double_eq(atofe("-3.14e2"), -314);
	ck_assert_double_eq(atofe("-314e-2"), -3.14);
	ck_assert_double_eq(atofe("-3.14e-2"), -0.0314);
}
END_TEST



Suite* str_suite (void) {
	Suite *suite = suite_create("Home assignment 1");
	TCase *tcase = tcase_create("case");


	//tcase_add_test(tcase, test_detab);
	//tcase_add_test(tcase, test_entab);
	tcase_add_test(tcase, test_enter);

	//tcase_add_test(tcase, test_flush);

	//tcase_add_test(tcase, test_htoi);
	//tcase_add_test(tcase, test_squeeze);
	//tcase_add_test(tcase, test_any);
	//tcase_add_test(tcase, test_setbits);
	//tcase_add_test(tcase, test_binsearch);
	//tcase_add_test(tcase, test_escape);
	//tcase_add_test(tcase, test_expand);
	//tcase_add_test(tcase, test_itoa);
	//tcase_add_test(tcase, test_itob);
	//tcase_add_test(tcase, test_strrindex);
	//tcase_add_test(tcase, test_atofe);
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