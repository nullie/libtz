#include <stdlib.h>
#include <check.h>
#include <time.h>
#include <stdio.h>
#include "../src/tz.h"

void abspath(char * const fullname, const char * path, size_t n) {
  getcwd(fullname, n);

  strcat(fullname, "/");

  strncat(fullname, path, n - strlen(fullname));
}

void fail_unless_time_equals(bt, sec, min, hour, mday, mon, year)
     struct tm * bt;
     int sec, min, hour, mday, mon, year;
{
  fail_unless(bt->tm_sec == sec && bt->tm_min == min && bt->tm_hour == hour &&
              bt->tm_mday == mday && bt->tm_mon == mon && bt->tm_year == year,
              "%02d:%02d:%02d %02d.%02d.%04d != %02d:%02d:%02d %02d.%02d.%04d",
              bt->tm_sec, bt->tm_min, bt->tm_hour, bt->tm_mday, bt->tm_mon + 1, bt->tm_year + 1900,
              sec, min, hour, mday, mon + 1, year + 1900);
}

START_TEST(test_tz_alloc_free)
{
  char fullname[FILENAME_MAX + 1];

  const struct state *sp;

  abspath(fullname, "ekaterinburg", FILENAME_MAX);

  sp = tz_alloc(fullname);

  fail_if(sp == NULL,
          "state not allocated");

  tz_free(sp);
}
END_TEST

START_TEST(test_tz_localtime) {
  char fullname[FILENAME_MAX + 1];
  const struct state *sp;

  abspath(fullname, "Yekaterinburg", FILENAME_MAX);

  sp = tz_alloc(fullname);

  struct tm st = {0, 0, 0, 1, 0, 112, 0, 0, 0};

  time_t t = timegm(&st);

  struct tm * bt = tz_localtime(sp, &t);

  fail_unless_time_equals(bt, 0, 0, 6, 1, 0, 112);

  struct tm st2 = {0, 0, 0, 1, 0, 111, 0, 0, 0};

  t = timegm(&st2);

  bt = tz_localtime(sp, &t);

  fail_unless_time_equals(bt, 0, 0, 5, 1, 0, 111);

  tz_free(sp);
}
END_TEST

START_TEST(test_tz_apia) {
  char fullname[FILENAME_MAX + 1];
  const struct state *sp;

  abspath(fullname, "Apia", FILENAME_MAX);

  sp = tz_alloc(fullname);

  struct tm st = {0, 0, 0, 1, 0, 112, 0, 0, 0};

  time_t t = timegm(&st);

  struct tm * bt = tz_localtime(sp, &t);

  fail_unless_time_equals(bt, 0, 0, 14, 1, 0, 112);

  struct tm st2 = {0, 0, 0, 30, 11, 111, 0, 0, 0};

  t = timegm(&st2);

  bt = tz_localtime(sp, &t);

  fail_unless_time_equals(bt, 0, 0, 14, 29, 11, 111);
}
END_TEST

START_TEST(test_tz_gmt) {
  const struct state *sp = tz_alloc("GMT-5");

  struct tm st = {0, 0, 0, 1, 0, 112, 0, 0, 0};

  time_t t = timegm(&st);

  struct tm * bt = tz_localtime(sp, &t);

  fail_unless_time_equals(bt, 0, 0, 5, 1, 0, 112);

  tz_free(sp);
}
END_TEST

START_TEST(test_tz_mktime) {
  char fullname[FILENAME_MAX + 1];
  const struct state *sp;

  abspath(fullname, "Yekaterinburg", FILENAME_MAX);

  sp = tz_alloc(fullname);

  struct tm st = {0, 30, 22, 15, 10, 111};

  time_t t = tz_mktime(sp, &st);

  struct tm * bt = gmtime(&t);

  fail_unless_time_equals(bt, 0, 30, 16, 15, 10, 111);

  struct tm st2 = {0, 30, 22, 15, 10, 110};

  t = tz_mktime(sp, &st2);

  bt = gmtime(&t);

  fail_unless_time_equals(bt, 0, 30, 17, 15, 10, 110);

  tz_free(sp);
}
END_TEST

Suite *
tz_suite(void)
{
  Suite *s = suite_create("tz");

  /* core test case */
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_tz_alloc_free);
  tcase_add_test(tc_core, test_tz_localtime);
  tcase_add_test(tc_core, test_tz_apia);
  tcase_add_test(tc_core, test_tz_gmt);
  tcase_add_test(tc_core, test_tz_mktime);
  suite_add_tcase(s, tc_core);

  return s;
}

int
main(void)
{
  int number_failed;
  Suite *s = tz_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
