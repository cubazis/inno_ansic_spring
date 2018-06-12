#include <check.h>
#include <math.h>
#include "../src/priority_queue.h"
/** YOUT TEST CASES HERE
 *
 *  please use 'test_fname' format for naming tcases
 *  fname is function name
 *
 *  if function name is 'detab' then test case is 'test_detab'
 * */

START_TEST (test_insert)
    {
        for (int i=1;i<=100;i++){
            ck_assert(insert(i,i)==0);
        }
        for (int i=-5;i<=0;i++){
            ck_assert(insert(i,i)==1);
        }
    }
END_TEST


START_TEST (test_extract)
    {
        for (int i=1;i<=100;i++){
            ck_assert(extract_min()==i);
        }
        ck_assert(extract_min()==-INFINITY);
    }
END_TEST


Suite *str_suite(void) {
    Suite *suite = suite_create("HA 2. Proprity Queue Test Suite");
    TCase *tcase = tcase_create("case");
    tcase_add_test(tcase,test_insert);
    tcase_add_test(tcase,test_extract);
    /** YOUT TEST CASES HERE */

    suite_add_tcase(suite, tcase);
    return suite;
}

int main(int argc, char *argv[]) {
    int number_failed;
    Suite *suite = str_suite();
    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return number_failed;

}