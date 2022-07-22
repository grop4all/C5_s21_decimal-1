#include <check.h>
#include <stdlib.h>

#include "s21_decimal.h"

#define S21_EPS_TEST 1E-6

START_TEST(ADDTest) {
  s21_decimal num1 = new_decimal(10500, 0, 0, 0, 0);
  s21_decimal num2 = new_decimal(75, 0, 0, 0, 0);
  s21_decimal result;

  s21_decimal_add(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 10575);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 0);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(10500, 0, 0, 0, 2);
  num2 = new_decimal(75, 0, 0, 0, 4);
  s21_decimal_add(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 1050075);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 4);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(10500, 0, 0, 1, 3);
  num2 = new_decimal(75, 0, 0, 0, 1);
  s21_decimal_add(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 3000);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 3);
  ck_assert_uint_eq(get_minus(result), 1);

  num1 = new_decimal(10500, 0, 0, 0, 3);
  num2 = new_decimal(75, 0, 0, 1, 1);
  s21_decimal_add(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 3000);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 3);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(10500, 0, 0, 0, 4);
  num2 = new_decimal(75, 0, 0, 1, 1);
  s21_decimal_add(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 64500);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 4);
  ck_assert_uint_eq(get_minus(result), 1);

  num1 = new_decimal(10500, 0, 0, 1, 5);
  num2 = new_decimal(75, 0, 0, 1, 15);
  s21_decimal_add(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 934514763);
  ck_assert_uint_eq(result.bits[1], 24447);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 15);
  ck_assert_uint_eq(get_minus(result), 1);

  num1 = new_decimal(11111, 88888888, 5555555, 0, 5);
  num2 = new_decimal(9999, 9999999, 9999999, 0, 7);
  s21_decimal_add(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 1121099);
  ck_assert_uint_eq(result.bits[1], 308954207);
  ck_assert_uint_eq(result.bits[2], 565555501);
  ck_assert_uint_eq(get_multiplier(result), 7);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(10500, 86445646, 5445545, 0, 5);
  num2 = new_decimal(9999, 9999999, 9999999, 0, 10);
  s21_decimal_add(num1, num2, &result);

  //   C# testing result:
  // decimal_num1: 1004525753281499027063.54436
  // decimal_num2: 18446742233330111.1115482087
  // decimals_sum: 1004544200023732357174.6559082
  // result bits: 0000458752 0544564502 0050345040 3020412010

  ck_assert_uint_eq(result.bits[0], 3020412019);
  ck_assert_uint_eq(result.bits[1], 50345040);
  ck_assert_uint_eq(result.bits[2], 544564502);
  ck_assert_uint_eq(get_multiplier(result), 7);
  ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(SUBTest) {
  s21_decimal num1 = new_decimal(10500, 0, 0, 0, 0);
  s21_decimal num2 = new_decimal(75, 0, 0, 0, 0);
  s21_decimal result;

  s21_decimal_sub(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 10425);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 0);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(10500, 0, 0, 0, 2);
  num2 = new_decimal(75, 0, 0, 0, 3);
  s21_decimal_sub(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 104925);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 3);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(10500, 0, 0, 1, 3);
  num2 = new_decimal(75, 0, 0, 0, 1);
  s21_decimal_sub(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 18000);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 3);
  ck_assert_uint_eq(get_minus(result), 1);

  num1 = new_decimal(10500, 0, 0, 1, 5);
  num2 = new_decimal(75, 0, 0, 1, 15);
  s21_decimal_sub(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 934514613);
  ck_assert_uint_eq(result.bits[1], 24447);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 15);
  ck_assert_uint_eq(get_minus(result), 1);
}
END_TEST

START_TEST(MULTest) {
  s21_decimal num1 = new_decimal(10500, 0, 0, 0, 0);
  s21_decimal num2 = new_decimal(75, 0, 0, 0, 0);
  s21_decimal result;

  s21_decimal_mul(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 787500);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 0);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(10500, 0, 0, 0, 2);
  num2 = new_decimal(75, 0, 0, 0, 3);
  s21_decimal_mul(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 787500);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 6);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(10500, 0, 0, 1, 3);
  num2 = new_decimal(75, 0, 0, 0, 1);
  s21_decimal_mul(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 787500);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 3);
  ck_assert_uint_eq(get_minus(result), 1);

  num1 = new_decimal(10500, 0, 0, 1, 5);
  num2 = new_decimal(175, 0, 0, 1, 3);
  s21_decimal_mul(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 1837500);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 15);
  ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

START_TEST(DIVTest) {
  s21_decimal num1 = new_decimal(10500, 0, 0, 0, 0);
  s21_decimal num2 = new_decimal(75, 0, 0, 0, 0);
  s21_decimal result;

  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 140);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 0);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(10500, 0, 0, 1, 3);
  num2 = new_decimal(75, 0, 0, 1, 1);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 14);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 1);
  ck_assert_uint_eq(get_minus(result), 0);
}
END_TEST

Suite *my_suite_create() {
  Suite *my_suite = suite_create("Test_decimal");
  TCase *DecimalTest = tcase_create("DECIMAL");

  suite_add_tcase(my_suite, DecimalTest);
  tcase_add_test(DecimalTest, ADDTest);
  tcase_add_test(DecimalTest, SUBTest);
  tcase_add_test(DecimalTest, MULTest);
  tcase_add_test(DecimalTest, DIVTest);

  return my_suite;
}

int main() {
  int number_failed;
  Suite *my_suite;
  SRunner *sr;
  my_suite = my_suite_create();
  sr = srunner_create(my_suite);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
