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

  // --- C# operation <ADD> testing result:
  // num1: 1004525753281499027063.54436
  // num1 bits: 0000327680 0005445545 0086445646 0000010500
  // num2: 18446742233330111.1115491087
  // num2 bits: 0000655360 0009999999 0009999999 0000009999
  // result: 1004544200023732357174.6559091
  // result bits: 0000458752 0544564502 0050345040 3020412019

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

  num1 = new_decimal(10500, 0, 0, 1, 8);
  num2 = new_decimal(75, 0, 0, 1, 10);
  s21_decimal_sub(num1, num2, &result);

  //   --- C# operation <SUB> testing result:
  // num1: -0.00010500
  // num1 bits: 2148007936 0000000000 0000000000 0000010500
  // num2: -0.0000000075
  // num2 bits: 2148139008 0000000000 0000000000 0000000075
  // result: -0.0001049925
  // result bits: 2148139008 0000000000 0000000000 0001049925

  ck_assert_uint_eq(result.bits[0], 1049925);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 10);
  ck_assert_uint_eq(get_minus(result), 1);

  num1 = new_decimal(10500, 86445646, 5445549, 0, 6);
  num2 = new_decimal(9999, 9999999, 9999999, 0, 10);
  s21_decimal_sub(num1, num2, &result);

  // --- C# operation <SUB> testing result:
  // num1: 100452649115126197544.560900
  // num1 bits: 0000393216 0005445549 0086445646 0000010500
  // num2: 18446742233330111.1115491087
  // num2 bits: 0000655360 0009999999 0009999999 0000009999
  // result: 100434202372892867433.44935089
  // result bits: 0000524288 0544454902 0097479680 4167168177

  ck_assert_uint_eq(result.bits[0], 4167168177);
  ck_assert_uint_eq(result.bits[1], 97479680);
  ck_assert_uint_eq(result.bits[2], 544454902);
  ck_assert_uint_eq(get_multiplier(result), 8);
  ck_assert_uint_eq(get_minus(result), 0);
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
  ck_assert_uint_eq(get_multiplier(result), 5);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(10500, 0, 0, 1, 3);
  num2 = new_decimal(75, 0, 0, 0, 1);
  s21_decimal_mul(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 787500);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 4);
  ck_assert_uint_eq(get_minus(result), 1);

  num1 = new_decimal(10500, 0, 0, 1, 5);
  num2 = new_decimal(175, 0, 0, 1, 3);
  s21_decimal_mul(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 1837500);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 8);
  ck_assert_uint_eq(get_minus(result), 0);

  num1 = new_decimal(111111, 55555, 666666, 0, 10);
  num2 = new_decimal(2222, 44444, 33333, 0, 20);
  s21_decimal_mul(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 1228745288);
  ck_assert_uint_eq(result.bits[1], 757513025);
  ck_assert_uint_eq(result.bits[2], 4099231370);
  ck_assert_uint_eq(get_multiplier(result), 10);
  ck_assert_uint_eq(get_minus(result), 0);

  //   --- C# operation <MUL> testing result:
  // num1: 1229781708488225.8845872647
  // num1 bits: 0000655360 0000666666 0000055555 0000111111
  // num2: 6148.85320399846010521774
  // num2 bits: 0001310720 0000033333 0000044444 0000002222
  // result: 7561747198456527992.2839169608
  // result bits: 0000655360 4099231370 0757513025 1228745288
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

  num1 = new_decimal(10500, 0, 0, 1, 8);
  num2 = new_decimal(75, 0, 0, 1, 10);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 14000);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(get_multiplier(result), 0);
  ck_assert_uint_eq(get_minus(result), 0);

  //   --- C# operation <DIV> testing result:
  // num1: -0.00010500
  // num1 bits: 2148007936 0000000000 0000000000 0000010500
  // num2: -0.0000000075
  // num2 bits: 2148139008 0000000000 0000000000 0000000075
  // result: 14000
  // result bits: 0000000000 0000000000 0000000000 0000014000

  num1 = new_decimal(8024, 0, 0, 0, 2);
  num2 = new_decimal(35, 0, 0, 0, 1);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 2377571182);
  ck_assert_uint_eq(result.bits[1], 3082367693);
  ck_assert_uint_eq(result.bits[2], 1242805461);
  ck_assert_uint_eq(get_multiplier(result), 27);
  ck_assert_uint_eq(get_minus(result), 0);

  //   --- C# operation <DIV> testing result:
  // num1: 80.24
  // num1 bits: 0000131072 0000000000 0000000000 0000008024
  // num2: 3.5
  // num2 bits: 0000065536 0000000000 0000000000 0000000035
  // result: 22.925714285714285714285714286
  // result bits: 0001769472 1242805461 3082367693 2377571182

  num1 = new_decimal(7, 0, 0, 0, 2);
  num2 = new_decimal(3, 0, 0, 0, 3);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 626349397);
  ck_assert_uint_eq(result.bits[1], 2432763277);
  ck_assert_uint_eq(result.bits[2], 1264902534);
  ck_assert_uint_eq(get_multiplier(result), 27);
  ck_assert_uint_eq(get_minus(result), 0);

  //   --- C# operation <DIV> testing result:
  // num1: 0.07
  // num1 bits: 0000131072 0000000000 0000000000 0000000007
  // num2: 0.003
  // num2 bits: 0000196608 0000000000 0000000000 0000000003
  // result: 23.333333333333333333333333333
  // result bits: 0001769472 1264902534 2432763277 0626349397

  num1 = new_decimal(8, 0, 0, 0, 0);
  num2 = new_decimal(3, 0, 0, 0, 0);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 715827883);
  ck_assert_uint_eq(result.bits[1], 2780300888);
  ck_assert_uint_eq(result.bits[2], 1445602896);
  ck_assert_uint_eq(get_multiplier(result), 28);
  ck_assert_uint_eq(get_minus(result), 0);

  //   --- C# operation <DIV> testing result:
  // num1: 8
  // num1 bits: 0000000000 0000000000 0000000000 0000000008
  // num2: 3
  // num2 bits: 0000000000 0000000000 0000000000 0000000003
  // result: 2.6666666666666666666666666667
  // result bits: 0001835008 1445602896 2780300888 0715827883

  num1 = new_decimal(8, 0, 0, 0, 1);
  num2 = new_decimal(3, 0, 0, 0, 0);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 1789569707);
  ck_assert_uint_eq(result.bits[1], 2855010466);
  ck_assert_uint_eq(result.bits[2], 144560289);
  ck_assert_uint_eq(get_multiplier(result), 28);
  ck_assert_uint_eq(get_minus(result), 0);

  //   --- C# operation <DIV> testing result:
  // num1: 0.8
  // num1 bits: 0000065536 0000000000 0000000000 0000000008
  // num2: 3
  // num2 bits: 0000000000 0000000000 0000000000 0000000003
  // result: 0.2666666666666666666666666667
  // result bits: 0001835008 0144560289 2855010466 1789569707

  num1 = new_decimal(354546, 0, 0, 0, 0);
  num2 = new_decimal(654, 0, 0, 0, 0);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 3464418144);
  ck_assert_uint_eq(result.bits[1], 67171418);
  ck_assert_uint_eq(result.bits[2], 2938834430);
  ck_assert_uint_eq(result.bits[3], 1703936);

  // --- C# operation <DIV> testing result:
  // num1: 354546
  //       0000000000 0000000000 0000000000 0000354546
  // num2: 654
  //       0000000000 0000000000 0000000000 0000000654
  // res : 542.11926605504587155963302752
  //       0001703936 2938834430 0067171418 3464418144

  num1 = new_decimal(10, 1, 55, 0, 0);
  num2 = new_decimal(7, 56, 0, 0, 0);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 1603828433);
  ck_assert_uint_eq(result.bits[1], 1538858751);
  ck_assert_uint_eq(result.bits[2], 22867295);
  ck_assert_uint_eq(result.bits[3], 1114112);

  // --- C# operation <DIV> testing result:
  // num1: 1014570924058320306186
  //       0000000000 0000000055 0000000001 0000000010
  // num2: 240518168583
  //       0000000000 0000000000 0000000056 0000000007
  // res : 4218271451.32366071433034449
  //       0001114112 0022867295 1538858751 1603828433

  num1 = new_decimal(8, 0, 0, 0, 8);
  num2 = new_decimal(3, 0, 0, 0, 3);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 3869944491);
  ck_assert_uint_eq(result.bits[1], 124410055);
  ck_assert_uint_eq(result.bits[2], 14456);
  ck_assert_uint_eq(get_multiplier(result), 28);
  ck_assert_uint_eq(get_minus(result), 0);

  //   --- C# operation <DIV> testing result:
  // num1: 0.00000008
  // num1 bits: 0000524288 0000000000 0000000000 0000000008
  // num2: 0.003
  // num2 bits: 0000196608 0000000000 0000000000 0000000003
  // result: 0.0000266666666666666666666667
  // result bits: 0001835008 0000014456 0124410055 3869944491

  num1 = new_decimal(10, 1, 55, 0, 0);
  num2 = new_decimal(7, 0, 0, 0, 0);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 756423899);
  ck_assert_uint_eq(result.bits[1], 3082119497);
  ck_assert_uint_eq(result.bits[2], 785714285);
  ck_assert_uint_eq(result.bits[3], 524288);

  // --- C# operation <DIV> testing result:
  // num1: 1014570924058320306186
  //       0000000000 0000000055 0000000001 0000000010
  // num2: 7
  //       0000000000 0000000000 0000000000 0000000007
  // res : 144938703436902900883.71428571
  //       0000524288 0785714285 3082119497 0756423899

  num1 = new_decimal(1, 2, 3, 0, 0);
  num2 = new_decimal(4, 5, 6, 0, 0);
  s21_decimal_div(num1, num2, &result);
  ck_assert_uint_eq(result.bits[0], 4289596349);
  ck_assert_uint_eq(result.bits[1], 476131325);
  ck_assert_uint_eq(result.bits[2], 271050543);
  ck_assert_uint_eq(result.bits[3], 1835008);

  // --- C# operation <DIV> testing result:
  // num1: 55340232229718589441
  //       0000000000 0000000003 0000000002 0000000001
  // num2: 110680464463732146180
  //       0000000000 0000000006 0000000005 0000000004
  // res : 0.4999999999805974463569071037
  //       0001835008 0271050543 0476131325 4289596349

  num1 = new_decimal(777, 444, 5555, 0, 10);
  num2 = new_decimal(3333, 88888, 111, 0, 5);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 2054553333);
  ck_assert_uint_eq(result.bits[1], 2930122307);
  ck_assert_uint_eq(result.bits[2], 271294);
  ck_assert_uint_eq(result.bits[3], 1835008);

  // --- C# operation <DIV> testing result:
  // num1: 10247166333136.3524707081
  //       0000655360 0000005555 0000000444 0000000777
  // num2: 20475889739528132.39557
  //       0000327680 0000000111 0000088888 0000003333
  // res : 0.0005004503571512442995736309
  //       0001835008 0000271294 2930122307 2054553333

  num1 = new_decimal(777, 444, 5555, 0, 10);
  num2 = new_decimal(3333, 88888, 11111, 0, 5);
  s21_decimal_div(num1, num2, &result);

  ck_assert_uint_eq(result.bits[0], 1756309468);
  ck_assert_uint_eq(result.bits[1], 112304069);
  ck_assert_uint_eq(result.bits[2], 271);
  ck_assert_uint_eq(result.bits[3], 1769472);

  // --- C# operation <DIV> testing result:
  // num1: 10247166333136.3524707081
  //       0000655360 0000005555 0000000444 0000000777
  // num2: 2049617737847578810.15557
  //       0000327680 0000011111 0000088888 0000003333
  // res : 0.000004999549986280607524828
  //       0001769472 0000000271 0112304069 1756309468
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
