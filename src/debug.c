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

  // s21_decimal a = new_decimal(1, 255, 4294967295, 1, 0);
  // s21_decimal b = new_decimal(108991, 2, 5, 0, 0);
  // s21_decimal c = {0};

  // // print_decimal(a);
  // // print_decimal(b);
  // // print_decimal(c);

  // print_bits(a);
  // print_bits(b);

  // s21_decimal_add(a, b, &c);
  // print_decimal(c);
  // print_bits(c);

  // printf("%d\n", get_left_index(a));

  // printf("ADD function result:%d\n", s21_decimal_add(a, b, &c));
  // print_decimal(c);
  // print_bits(c);

  // reset_bit(&c, 30);

  // inverse_decimal(&c);
  // print_decimal(c);

  // simple_add(a, b, &c);

  // printf("%u %u %u %u\n", a.bits[3], a.bits[2], a.bits[1], a.bits[0]);
  // printf("%u %u %u %u\n", b.bits[3], b.bits[2], b.bits[1], b.bits[0]);
  // printf("%u %u %u %u\n", c.bits[3], c.bits[2], c.bits[1], c.bits[0]);

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

  num1 = new_decimal(1680, 0, 0, 0, 2);
  num2 = new_decimal(410, 0, 0, 0, 2);
  // print_decimal(num2);
  // inverse_decimal(&num2);
  // print_decimal(num2);

  // printf("{num1 > num2} %d\n", decimal_great(num1, num2));

  // decimal_div_10(&num1, 4);
  print_bits(num1);

  // decimal_simple_div(num1, num2, &result);
  // print_bits(result);

  // print_bits(num2);

  // s21_decimal result;

  s21_decimal_div(num1, num2, &result);
  print_bits(result);

  s21_decimal_mod(num1, num2, &result);

  // del_nulls(&num1);
  // print_bits(num1);

  print_bits(result);

  return 0;
}
