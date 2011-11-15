#include <stdlib.h>
#include <check.h>
#include "../src/tz.h"

START_TEST(test_tz_alloc_free)
{
  const struct state *sp = tz_alloc("Asia/Yekaterinburg");

  fail_unless(sp != NULL,
              "state not allocated");
  tz_free(sp);
}
END_TEST

Suite *
tz_suite(void)
{
  Suite *s = suite_create("TZ");

  /* core test case */
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_tz_alloc_free);
  suite_add_tcase(s, tc_core);

  return s;
}

int
main(void)
{
  int number_failed;
  Suite *s = tz_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
