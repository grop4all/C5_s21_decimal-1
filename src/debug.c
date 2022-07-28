#include <stdio.h>

#include "s21_decimal.h"

// void print_decimal(s21_decimal number) {
//   for (int i = 0; i < 128; i++) {
//     printf("%d", get_bit_status(number, 127 - i));
//     if (i == 31 || i == 63 || i == 95) printf(" ");
//   }
//   printf("\n");
// }

// void print_bits(s21_decimal num) {
//   printf("%10u %10u %10u %10u", num.bits[3], num.bits[2], num.bits[1],
//          num.bits[0]);
//   printf(" mult=%2d", get_multiplier(num));
//   printf(" minus=%d\n", get_minus(num));
// }

int main() {
  // s21_decimal num1 = {
  //     0b10000000000000000000000000000001,
  //     0b01010000000000000000010000000101,
  //     0b00000000000000000000000000011111,
  //     0b00000000000000000000000000000000};

  // printf("%u %u %u %u\n", num1.bits[3], num1.bits[2], num1.bits[1],
  //        num1.bits[0]);

  // print_decimal(a);
  // print_decimal(b);
  // print_decimal(c);

  // print_bits(a);
  // print_bits(b);

  // print_decimal(c);
  //  print_bits(c);

  // printf("%d\n", get_left_index(a));

  // printf("ADD function result:%d\n", s21_decimal_add(a, b, &c));
  // print_decimal(c);
  // print_bits(c);

  // reset_bit(&c, 30);

  // inverse_decimal(&c);
  // print_decimal(c);

  // simple_add(a, b, &c);

  // set_bit(&c, 96 + 31);
  // print_decimal(c);

  // printf("%u %u %u %u\n", c.bits[3], c.bits[2], c.bits[1], c.bits[0]);

  // set_multiplier(&c, 25);
  // print_decimal(c);

  // printf("multiplier:%d\n", get_multiplier(c));
  // printf("minus status:%d\n", get_bit_status(c, 96 + 31));

  // print_decimal(a);
  // printf("%u %u %u %u\n", a.bits[3], a.bits[2], a.bits[1], a.bits[0]);
  // decimal_mul_10(&a, 25);
  // printf("%u %u %u %u\n", a.bits[3], a.bits[2], a.bits[1], a.bits[0]);

  // s21_decimal num1 = new_decimal(10500, 86445646, 5445545, 0, 5);
  // s21_decimal num2 = new_decimal(9999, 9999999, 9999999, 0, 10);
  s21_decimal result;
  // s21_decimal_add(num1, num2, &result);

  // print_bits(result);

  s21_decimal num1;
  s21_decimal num2;

  // num1 = new_decimal(10500, 0, 0, 1, 8);
  // num2 = new_decimal(75, 0, 0, 1, 10);

  // num1 = new_decimal(8, 0, 0, 0, 8);
  // num2 = new_decimal(3, 0, 0, 0, 3);

  // --- C# operation <DIV> testing result:
  // num1: 354546
  //       0000000000 0000000000 0000000000 0000354546
  // num2: 654
  //       0000000000 0000000000 0000000000 0000000654
  // res : 542.11926605504587155963302752 (3.26)
  //       0001703936 2938834430 0067171418 3464418144

  // int count = 4;
  //  s21_long_decimal c = {0};

  // print_bits_long(a);
  // for (int i = 0; i < 10; i++) {
  //   decimal_mul_10(&a, 1);
  //   print_bits_long(a);
  // }
  // for (int i = 0; i < 10; i++) {
  //   decimal_div_10(&a, 1);
  //   print_bits_long(a);
  // }
  // print_bits_long(a);
  // del_nulls(&a, &count);
  // printf("zeros in a:%d\n", count);
  // print_bits_long(a);

  // decimal_div_10(&b, 4);
  // print_bits_long(b);

  num1 = new_decimal(777, 444, 5555, 0, 10);
  num2 = new_decimal(3333, 88888, 11111, 0, 5);
  //       0001769472 0000000271 0112304069 1756309468
  print_bits(num1);
  print_bits(num2);

  s21_decimal_div(num1, num2, &result);
  print_bits(result);

  return 0;
}

// Decimal MAX = 79228162514264337593543950335