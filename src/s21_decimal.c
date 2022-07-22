#include "s21_decimal.h"

#include <stdio.h>  //временно!! удалить после дебага

// ---- ************************************************************
void print_decimal(s21_decimal number) {
  for (int i = 0; i < 128; i++) {
    printf("%d", get_bit_status(number, 127 - i));
    if (i == 31 || i == 63 || i == 95) printf(" ");
  }
  printf("\n");
}

void print_bits(s21_decimal num) {
  printf("%10u %10u %10u %10u", num.bits[3], num.bits[2], num.bits[1],
         num.bits[0]);
  printf(" mult=%2d", get_multiplier(num));
  printf(" minus=%d\n", get_minus(num));
}
// ---------------- ^^^^^^^^^^ убрать после дебага !!!!!! ^^^^^^^^^^

s21_decimal new_decimal(unsigned int bit0, unsigned int bit1, unsigned int bit2,
                        int minus, int multiplier) {
  s21_decimal number;
  reset_decimal(&number);
  number.bits[0] = bit0;
  number.bits[1] = bit1;
  number.bits[2] = bit2;
  if (minus) set_minus(&number);
  if (multiplier) set_multiplier(&number, multiplier);
  return number;
}

void set_minus(s21_decimal *number) { set_bit(number, 31 + 3 * 32); }

int get_minus(s21_decimal number) {
  return get_bit_status(number, 31 + 3 * 32);
}

void reset_decimal(s21_decimal *number) {
  for (int i = 0; i < 4; i++) number->bits[i] = 0;
}

s21_decimal copy_decimal(s21_decimal number) {
  s21_decimal result;
  for (int i = 0; i < 4; i++) result.bits[i] = number.bits[i];
  return result;
}

void inverse_decimal(s21_decimal *number) {
  for (int i = 0; i < 3; i++) number->bits[i] = ~number->bits[i];
  s21_decimal one = {{1, 0, 0, 0}};
  simple_add(*number, one, number);
}

int get_bit_status(s21_decimal num, int index) {
  unsigned int mask = 1;
  mask = mask << index % 32;
  unsigned result = num.bits[index / 32] & mask;
  if (result > 0)
    return 1;
  else
    return 0;
}

void set_bit(s21_decimal *num, int index) {
  unsigned int mask = 1;
  mask = mask << index % 32;
  num->bits[index / 32] = num->bits[index / 32] | mask;
}

void reset_bit(s21_decimal *num, int index) {
  unsigned int mask = 1;
  mask = mask << index % 32;
  mask = ~mask;
  num->bits[index / 32] = num->bits[index / 32] & mask;
}

void reset_minus(s21_decimal *number) { reset_bit(number, 31 + 3 * 32); }

int simple_add(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  int perenos = 0;
  int temp_summ = 0;

  reset_decimal(result);

  for (int i = 0; i < 96; i++) {
    temp_summ = get_bit_status(num1, i) + get_bit_status(num2, i);
    if (temp_summ == 2 && perenos) set_bit(result, i);
    if (temp_summ == 1 && !perenos) set_bit(result, i);
    if (temp_summ == 0 && perenos) {
      set_bit(result, i);
      perenos = 0;
    }
    if (temp_summ == 2) perenos = 1;
  }
  if (perenos == 1) return 1;
  return 0;
}

int _pow(int x, int y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  return x * _pow(x, y - 1);
}

int get_multiplier(s21_decimal number) {
  int result = 0;
  int bit = 0;
  for (int i = 16; i < 24; i++) {
    bit = get_bit_status(number, i + 3 * 32);
    result = result + _pow(2, i - 16) * bit;
  }
  return result;
}

void set_multiplier(s21_decimal *number, int multipler) {
  int minus = get_bit_status(*number, 96 + 31);
  number->bits[3] = multipler << 16;
  if (minus) set_bit(number, 96 + 31);
}

int left_bit_shift(s21_decimal *number, int count) {
  for (int j = 0; j < count; j++)
    for (int i = 0; i < 3; i++) {
      number->bits[2 - i] = number->bits[2 - i] << 1;
      if (get_bit_status(*number, 31 + (1 - i) * 32) && i != 2)
        set_bit(number, 0 + 32 * (2 - i));
    }
  return 0;
}

int right_bit_shift(s21_decimal *number, int count) {
  for (int j = 0; j < count; j++)
    for (int i = 0; i < 3; i++) {
      number->bits[i] = number->bits[i] >> 1;
      if (get_bit_status(*number, 32 + i * 32) && i != 2)
        set_bit(number, 31 + 32 * i);
    }
  return 0;
}

int decimal_mul_10(s21_decimal *number, int count) {
  int minus_bit = get_minus(*number);
  for (int i = 0; i < count; i++) {
    s21_decimal temp = copy_decimal(*number);
    s21_decimal temp2 = copy_decimal(*number);
    left_bit_shift(&temp, 1);
    left_bit_shift(&temp2, 3);
    simple_add(temp, temp2, number);
  }
  if (minus_bit) set_minus(number);
  return 0;
}

int decimal_simple_div(s21_decimal dividend, s21_decimal divider,
                       s21_decimal *result) {
  s21_decimal temp_dividend = copy_decimal(dividend);
  s21_decimal temp_divider = copy_decimal(divider);

  reset_decimal(result);

  int count = get_left_index(temp_dividend) - get_left_index(temp_divider);

  left_bit_shift(&temp_divider, count);
  s21_decimal temp_divider_inv;

  for (int i = 0; i < count + 1; i++) {
    if (i != 0) right_bit_shift(&temp_divider, 1);

    left_bit_shift(result, 1);

    if (decimal_great(temp_dividend, temp_divider) ||
        decimal_equal(temp_dividend, temp_divider)) {
      temp_divider_inv = copy_decimal(temp_divider);
      inverse_decimal(&temp_divider_inv);
      simple_add(temp_dividend, temp_divider_inv, &temp_dividend);
      set_bit(result, 0);
    }
  }
  return 0;
}

int decimal_div_10(s21_decimal *number, int count) {
  s21_decimal temp = copy_decimal(*number);
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal result;
  for (int i = 0; i < count; i++) {
    decimal_simple_div(temp, ten, &result);
    temp = copy_decimal(result);
  }
  *number = copy_decimal(result);
  return 0;
}

int max_num(int num1, int num2) {
  if (num1 > num2)
    return num1;
  else
    return num2;
}

int decimal_normalize(s21_decimal num1, s21_decimal num2, s21_decimal *n1_out,
                      s21_decimal *n2_out, int *multipler) {
  int mult1 = get_multiplier(num1);
  int mult2 = get_multiplier(num2);
  int free_index1 = 30 - get_left_index(num1) / 3;
  int free_index2 = 30 - get_left_index(num2) / 3;

  int max_mult;

  if (free_index1 + mult1 < free_index2 + mult2)
    max_mult = free_index1 + mult1;
  else
    max_mult = free_index2 + mult2;

  // printf("free1=%d, free2=%d, max=%d\n", free_index1, free_index2,
  // max_mult);

  if (mult1 > mult2 && mult1 < max_mult) *multipler = mult1;
  if (mult1 > mult2 && mult1 >= max_mult) *multipler = max_mult;

  if (mult2 > mult1 && mult2 < max_mult) *multipler = mult2;
  if (mult2 > mult1 && mult2 >= max_mult) *multipler = max_mult;

  *n1_out = copy_decimal(num1);
  *n2_out = copy_decimal(num2);

  // printf("mult1=%d, mult2=%d, mult=%d\n", mult1, mult2, *multipler);

  if (*multipler > mult1) decimal_mul_10(n1_out, *multipler - mult1);
  if (*multipler > mult2) decimal_mul_10(n2_out, *multipler - mult2);

  if (*multipler < mult1) decimal_div_10(n1_out, mult1 - *multipler);
  if (*multipler < mult2) decimal_div_10(n2_out, mult2 - *multipler);

  set_multiplier(n1_out, *multipler);
  set_multiplier(n2_out, *multipler);
  return 0;
}

int decimal_great(s21_decimal num1, s21_decimal num2) {
  // s21_decimal n1, n2;
  int result = 0, bit1 = 0, bit2 = 0;
  // decimal_normalize(num1, num2, &n1, &n2, &mult);

  for (int i = 0; i < 32 * 3 && bit1 == bit2; i++) {
    bit1 = get_bit_status(num1, 95 - i);
    bit2 = get_bit_status(num2, 95 - i);
    if (bit1 != bit2) {
      if (bit1 > bit2) result = 1;
    }
  }
  return result;
}

int s21_decimal_great(s21_decimal num1, s21_decimal num2) {
  int minus1 = get_minus(num1);
  int minus2 = get_minus(num2);
  int result = decimal_great(num1, num2);

  if (minus2 && !minus1) result = 1;
  if (minus1 && !minus2) result = 0;
  if (minus1 && minus2) result = ~result & 0x0000000F;
  return result;
}

int decimal_equal(s21_decimal num1, s21_decimal num2) {
  // s21_decimal n1, n2;
  int result = 1, bit1 = 0, bit2 = 0;
  // decimal_normalize(num1, num2, &n1, &n2, &mult);
  for (int i = 0; i < 32 * 3 && bit1 == bit2; i++) {
    bit1 = get_bit_status(num1, 95 - i);
    bit2 = get_bit_status(num2, 95 - i);
    if (bit1 != bit2) result = 0;
  }
  return result;
}

int decimal_lite(s21_decimal num1, s21_decimal num2) {
  // s21_decimal n1, n2;
  int result = 0, bit1 = 0, bit2 = 0;
  // decimal_normalize(num1, num2, &n1, &n2, &mult);
  for (int i = 0; i < 32 * 3 && bit1 == bit2; i++) {
    bit1 = get_bit_status(num1, 95 - i);
    bit2 = get_bit_status(num2, 95 - i);
    if (bit1 != bit2) {
      if (bit1 < bit2) result = 1;
    }
  }
  return result;
}

int s21_decimal_add(s21_decimal num1, s21_decimal num2, s21_decimal *res_num) {
  s21_decimal n1, n2;
  int mult = 0;
  int func_result = 0;
  decimal_normalize(num1, num2, &n1, &n2, &mult);

  int minus_flag1 = get_minus(n1);
  int minus_flag2 = get_minus(n2);

  // print_bits(n1);
  // print_bits(n2);

  int n1_great = decimal_great(n1, n2);

  if (!minus_flag1 && !minus_flag2) {  // n1>0 & n2>0
    func_result = simple_add(n1, n2, res_num);
    set_multiplier(res_num, mult);
  }

  if (minus_flag1 && minus_flag2) {  // n1<0 & n2<0
    func_result = simple_add(n1, n2, res_num);
    set_multiplier(res_num, mult);
    set_minus(res_num);
    if (func_result == 1) func_result = 2;
  }

  if (!minus_flag1 && minus_flag2 && n1_great) {  // n1>0 & n2<0 & n1>n2
    inverse_decimal(&n2);
    simple_add(n1, n2, res_num);
    set_multiplier(res_num, mult);
  }

  if (!minus_flag1 && minus_flag2 && !n1_great) {  // n1>0 & n2<0 & n1<n2
    inverse_decimal(&n1);
    simple_add(n1, n2, res_num);
    set_multiplier(res_num, mult);
    set_minus(res_num);
  }

  if (minus_flag1 && !minus_flag2 && !n1_great) {  // n1<0 & n2>0 & n1<n2
    inverse_decimal(&n1);
    simple_add(n1, n2, res_num);
    set_multiplier(res_num, mult);
  }

  if (minus_flag1 && !minus_flag2 && n1_great) {  // n1<0 & n2>0 & n1>n2
    inverse_decimal(&n2);
    simple_add(n1, n2, res_num);
    set_multiplier(res_num, mult);
    set_minus(res_num);
  }

  return func_result;
}

int s21_decimal_sub(s21_decimal num1, s21_decimal num2, s21_decimal *res_num) {
  s21_decimal n1 = copy_decimal(num1);
  s21_decimal n2 = copy_decimal(num2);

  int minus_flag2 = get_minus(num2);
  if (!minus_flag2) set_minus(&n2);
  if (minus_flag2) reset_minus(&n2);
  int func_result = s21_decimal_add(n1, n2, res_num);
  return func_result;
}

int get_left_index(s21_decimal number) {
  int i = 95;
  while (get_bit_status(number, i) == 0 && i != 0) {
    i--;
  }
  return i;
}

int s21_decimal_mul(s21_decimal num1, s21_decimal num2, s21_decimal *res_num) {
  reset_decimal(res_num);
  s21_decimal n1 = copy_decimal(num1);
  s21_decimal n2 = copy_decimal(num2);

  int left_index = get_left_index(n2);
  s21_decimal temp = copy_decimal(n1);

  for (int i = 0; i < left_index + 1; i++) {
    if (i != 0) left_bit_shift(&temp, 1);
    if (get_bit_status(n2, i)) {
      simple_add(*res_num, temp, res_num);
    }
  }
  int mult1 = get_multiplier(num1);
  int mult2 = get_multiplier(num2);

  int minus_flag1 = get_minus(num1);
  int minus_flag2 = get_minus(num2);

  int mult;
  if (mult1 * mult2 == 0) mult = 0;
  if (mult1 == 0 && mult2 != 0) mult = mult2;
  if (mult2 == 0 && mult1 != 0) mult = mult1;
  if (mult1 != 0 && mult2 != 0) mult = mult1 + mult2;
  set_multiplier(res_num, mult);

  if ((minus_flag1 && !minus_flag2) || (!minus_flag1 && minus_flag2))
    set_minus(res_num);

  return 0;
}

int del_nulls(s21_decimal *number) {
  int mult = get_multiplier(*number);
  while (mult != 0 && number->bits[0] % 10 == 0) {
    decimal_div_10(number, 1);
    mult--;
  }
  set_multiplier(number, mult);
  return 0;
}

int s21_decimal_div(s21_decimal num1, s21_decimal num2, s21_decimal *res_num) {
  reset_decimal(res_num);
  s21_decimal n1 = copy_decimal(num1);
  s21_decimal n2 = copy_decimal(num2);

  int mult1 = get_multiplier(num1);
  int mult2 = get_multiplier(num2);
  int mult;

  decimal_mul_10(&n1, mult2);
  // print_bits(n1);

  // decimal_normalize(num1, num2, &n1, &n2, &mult);
  // if (mult1 * mult2 == 0) mult = 0;
  // if (mult1 == 0 && mult2 != 0) mult = mult2;
  // if (mult2 == 0 && mult1 != 0) mult = mult1;
  // if (mult1 != 0 && mult2 != 0) mult = mult1 * mult2;
  // set_multiplier(res_num, mult);

  decimal_simple_div(n1, n2, res_num);
  set_multiplier(res_num, mult1);
  // print_bits(*res_num);

  int minus_flag1 = get_minus(num1);
  int minus_flag2 = get_minus(num2);

  if ((minus_flag1 && !minus_flag2) || (!minus_flag1 && minus_flag2))
    set_minus(res_num);

  del_nulls(res_num);

  return 0;
}
// decimal_num1: 80.24
// decimal_num2: 3.5
// decimals_sum: 22.925714285714285714285714286
//  22.925714285714285714285714286  0001769472 1242805461 3082367693 2377571182

int s21_decimal_mod(s21_decimal num1, s21_decimal num2, s21_decimal *res_num) {
  s21_decimal n1 = copy_decimal(num1);
  s21_decimal n2 = copy_decimal(num2);
  s21_decimal div_result;
  s21_decimal temp;
  s21_decimal_div(n1, n2, &div_result);
  s21_decimal_mul(n2, div_result, &temp);
  s21_decimal_sub(n1, temp, res_num);
  return 0;
}
