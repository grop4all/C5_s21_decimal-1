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

void print_bits(const s21_decimal num) {
  printf("%10u %10u %10u %10u", num.bits[3], num.bits[2], num.bits[1],
         num.bits[0]);
  printf(" mult=%2d", get_multiplier(num));
  printf(" minus=%d\n", get_minus(num));
}

void print_bits_long(s21_long_decimal num) {
  printf("%10u %10u %10u %10u %10u %10u\n", num.bits[5], num.bits[4],
         num.bits[3], num.bits[2], num.bits[1], num.bits[0]);
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

void reset_decimal_long(s21_long_decimal *number) {
  for (int i = 0; i < 6; i++) number->bits[i] = 0;
}

s21_decimal copy_decimal(s21_decimal number) {
  s21_decimal result;
  for (int i = 0; i < 4; i++) result.bits[i] = number.bits[i];
  return result;
}

s21_long_decimal copy_decimal_long(s21_long_decimal number) {
  s21_long_decimal result;
  for (int i = 0; i < 6; i++) result.bits[i] = number.bits[i];
  return result;
}

s21_long_decimal convert_decimal_to_long(s21_decimal number) {
  s21_long_decimal result;
  reset_decimal_long(&result);
  for (int i = 0; i < 3; i++) result.bits[i] = number.bits[i];
  return result;
}

void inc_decimal_long(s21_long_decimal *number) {
  s21_long_decimal one = {{1, 0, 0, 0, 0, 0}};
  simple_add(*number, one, number);
}

s21_decimal convert_long_to_decimal(s21_long_decimal number, int operation,
                                    int *multiplier, int *func_status) {
  // operation = 0 for add, sub, mul
  // opertaion = 1 for div
  // operation = 2 for mod

  s21_decimal result = {{0, 0, 0, 0}};
  reset_decimal(&result);

  // printf("0-mult=%d\n", *multiplier);

  int rang_long = get_rang(number);

  // printf("0-rang_long=%d\n", rang_long);

  int temp = 0;
  int big_multiplier = 0;
  if (*multiplier > 28) big_multiplier = 1;

  int num_free = 29 - rang_long + *multiplier;

  // printf("free=%d\n", num_free);

  if (*multiplier > num_free && num_free >= 0) {
    for (int i = 0; i < *multiplier - num_free; i++) {
      temp = decimal_div_10(&number, 1);
      // print_bits_long(number);
    }
    *multiplier = num_free;
  }

  while (*multiplier > 28) {
    temp = decimal_div_10(&number, 1);
    *multiplier = *multiplier - 1;
  }

  if (temp == 1) inc_decimal_long(&number);

  // print_bits_long(number);
  //   printf("mult=%d\n", *multiplier);

  if (operation == 1) del_nulls(&number, multiplier);

  // printf("modiff_mult=%d\n", *multiplier);

  for (int i = 0; i < 3; i++) result.bits[i] = number.bits[i];

  if (operation == 1 && big_multiplier && is_null(result)) *func_status = 2;
  if (operation == 0 && (number.bits[3] || number.bits[4] || number.bits[5]))
    *func_status = 2;

  return result;
}

void inverse_decimal(s21_long_decimal *number) {
  for (int i = 0; i < 6; i++) number->bits[i] = ~number->bits[i];
  s21_long_decimal one = {{1, 0, 0, 0, 0, 0}};
  simple_add(*number, one, number);
}

int get_bit_status_long(s21_long_decimal num, int index) {
  int func_res = 0;
  unsigned int mask = 1;
  mask = mask << index % 32;
  unsigned int result = 0;
  int bit_index = round(index / 32);
  result = num.bits[bit_index] & mask;
  if (result > 0) func_res = 1;
  return func_res;
}

int get_bit_status(s21_decimal num, int index) {
  unsigned int mask = 1;
  mask = mask << index % 32;
  unsigned int result = num.bits[index / 32] & mask;
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

void set_bit_long(s21_long_decimal *num, int index) {
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

void reset_bit_long(s21_long_decimal *num, int index) {
  unsigned int mask = 1;
  mask = mask << index % 32;
  mask = ~mask;
  num->bits[index / 32] = num->bits[index / 32] & mask;
}

void reset_minus(s21_decimal *number) { reset_bit(number, 31 + 3 * 32); }

int simple_add(s21_long_decimal num1, s21_long_decimal num2,
               s21_long_decimal *result) {
  int perenos = 0;

  reset_decimal_long(result);

  for (int i = 0; i < 192; i++) {
    int temp_summ = 0;
    temp_summ = get_bit_status_long(num1, i) + get_bit_status_long(num2, i);
    if (temp_summ == 2 && perenos) set_bit_long(result, i);
    if (temp_summ == 1 && !perenos) set_bit_long(result, i);
    if (temp_summ == 0 && perenos) {
      set_bit_long(result, i);
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
  for (int i = 16; i < 24; i++) {
    int bit = 0;
    bit = get_bit_status(number, i + 3 * 32);
    result = result + _pow(2, i - 16) * bit;
  }
  return result;
}

void set_multiplier(s21_decimal *number, int multipler) {
  int minus = get_bit_status(*number, 96 + 31);
  number->bits[3] = multipler << 16;
  if (minus) set_minus(number);
}

int left_bit_shift(s21_long_decimal *number, int count) {
  for (int j = 0; j < count; j++) {
    for (int i = 0; i < 6; i++) {
      number->bits[5 - i] = number->bits[5 - i] << 1;
      if (i < 5)
        if (get_bit_status_long(*number, 31 + (4 - i) * 32))
          set_bit_long(number, 0 + 32 * (5 - i));
    }
  }
  return 0;
}

int right_bit_shift(s21_long_decimal *number, int count) {
  for (int j = 0; j < count; j++) {
    for (int i = 0; i < 6; i++) {
      number->bits[i] = number->bits[i] >> 1;
      if (i < 5)
        if (get_bit_status_long(*number, 32 + i * 32))
          set_bit_long(number, 31 + 32 * i);
    }
  }
  return 0;
}

int decimal_mul_10(s21_long_decimal *number, int count) {
  // int minus_bit = get_minus(*number);
  for (int i = 0; i < count; i++) {
    s21_long_decimal temp = copy_decimal_long(*number);
    s21_long_decimal temp2 = copy_decimal_long(*number);
    left_bit_shift(&temp, 1);
    left_bit_shift(&temp2, 3);
    simple_add(temp, temp2, number);
  }
  // if (minus_bit) set_minus(number);
  return 0;
}

int decimal_simple_div(s21_long_decimal dividend, s21_long_decimal divider,
                       s21_long_decimal *result, s21_long_decimal *ostatok) {
  s21_long_decimal temp_dividend = copy_decimal_long(dividend);
  s21_long_decimal temp_divider = copy_decimal_long(divider);

  reset_decimal_long(result);

  int count = get_left_index(temp_dividend) - get_left_index(temp_divider);

  left_bit_shift(&temp_divider, count);
  s21_long_decimal temp_divider_inv;

  for (int i = 0; i < count + 1; i++) {
    if (i != 0) right_bit_shift(&temp_divider, 1);

    left_bit_shift(result, 1);

    if (decimal_great(temp_dividend, temp_divider) ||
        decimal_equal(temp_dividend, temp_divider)) {
      temp_divider_inv = copy_decimal_long(temp_divider);
      inverse_decimal(&temp_divider_inv);
      simple_add(temp_dividend, temp_divider_inv, &temp_dividend);
      set_bit_long(result, 0);
    }
  }
  *ostatok = copy_decimal_long(temp_dividend);
  return 0;
}

int decimal_div_10(s21_long_decimal *number, int count) {
  s21_long_decimal temp = copy_decimal_long(*number);
  s21_long_decimal ten = {{10, 0, 0, 0, 0, 0}};
  s21_long_decimal result = copy_decimal_long(*number);
  s21_long_decimal ost = {{0, 0, 0, 0}};
  for (int i = 0; i < count; i++) {
    decimal_simple_div(temp, ten, &result, &ost);
    temp = copy_decimal_long(result);
  }
  *number = copy_decimal_long(result);
  if (ost.bits[0] == 0)
    return 0;
  else if (ost.bits[0] >= 5)
    return 1;
  else
    return 2;
}

int max_num(int num1, int num2) {
  if (num1 > num2)
    return num1;
  else
    return num2;
}

int decimal_normalize(s21_decimal num1, s21_decimal num2,
                      s21_long_decimal *n1_out, s21_long_decimal *n2_out,
                      int *multipler) {
  int mult1 = get_multiplier(num1);
  int mult2 = get_multiplier(num2);

  if (mult1 > mult2)
    *multipler = mult1;
  else
    *multipler = mult2;

  *n1_out = convert_decimal_to_long(num1);
  *n2_out = convert_decimal_to_long(num2);

  // printf("mult1=%d, mult2=%d, mult=%d\n", mult1, mult2, *multipler);

  if (*multipler > mult1) decimal_mul_10(n1_out, *multipler - mult1);
  if (*multipler > mult2) decimal_mul_10(n2_out, *multipler - mult2);

  return 0;
}

int decimal_great(s21_long_decimal num1, s21_long_decimal num2) {
  int result = 0, bit1 = 0, bit2 = 0;
  for (int i = 0; i < 192 && bit1 == bit2; i++) {
    bit1 = get_bit_status_long(num1, 191 - i);
    bit2 = get_bit_status_long(num2, 191 - i);
    if (bit1 != bit2) {
      if (bit1 > bit2) result = 1;
    }
  }
  return result;
}

int decimal_equal(s21_long_decimal num1, s21_long_decimal num2) {
  int result = 1, bit1 = 0, bit2 = 0;
  for (int i = 0; i < 192 && bit1 == bit2; i++) {
    bit1 = get_bit_status_long(num1, 191 - i);
    bit2 = get_bit_status_long(num2, 191 - i);
    if (bit1 != bit2) result = 0;
  }
  return result;
}

int decimal_lite(s21_long_decimal num1, s21_long_decimal num2) {
  int result = 0, bit1 = 0, bit2 = 0;
  for (int i = 0; i < 192 && bit1 == bit2; i++) {
    bit1 = get_bit_status_long(num1, 191 - i);
    bit2 = get_bit_status_long(num2, 191 - i);
    if (bit1 != bit2) {
      if (bit1 < bit2) result = 1;
    }
  }
  return result;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal n1, n2;
  int mult = 0;
  decimal_normalize(value_1, value_2, &n1, &n2, &mult);

  int minus1 = get_minus(value_1);
  int minus2 = get_minus(value_2);
  int result = decimal_great(n1, n2);

  if (minus2 && !minus1) result = 1;
  if (minus1 && !minus2) result = 0;
  if (minus1 && minus2)
    if (result)
      result = 0;
    else
      result = 1;
  return result;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal n1, n2;
  int mult = 0;
  decimal_normalize(value_1, value_2, &n1, &n2, &mult);

  int minus1 = get_minus(value_1);
  int minus2 = get_minus(value_2);
  int result = decimal_lite(n1, n2);

  if (minus2 && !minus1) result = 0;
  if (minus1 && !minus2) result = 1;
  if (minus1 && minus2)
    if (decimal_great(n1, n2))
      result = 1;
    else
      result = 0;
  return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal n1, n2;
  int mult = 0;
  decimal_normalize(value_1, value_2, &n1, &n2, &mult);

  int minus1 = get_minus(value_1);
  int minus2 = get_minus(value_2);
  int result = decimal_equal(n1, n2);
  if (result && !(is_null(value_1) && is_null(value_2)) && (minus1 != minus2))
    result = 0;
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) == 1 ||
         s21_is_equal(value_1, value_2) == 1;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) == 1 ||
         s21_is_equal(value_1, value_2) == 1;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_long_decimal n1, n2, res_long;
  reset_decimal_long(&res_long);

  int mult = 0;
  int func_result = 0;
  decimal_normalize(value_1, value_2, &n1, &n2, &mult);

  // print_bits_long(n1);
  // print_bits_long(n2);

  int minus_flag1 = get_minus(value_1);
  int minus_flag2 = get_minus(value_2);
  int minus_flag = 0;

  // print_bits(n1);
  // print_bits(n2);

  int n1_great = decimal_great(n1, n2);

  if (!minus_flag1 && !minus_flag2) {  // n1>0 & n2>0
    func_result = simple_add(n1, n2, &res_long);
  }

  if (minus_flag1 && minus_flag2) {  // n1<0 & n2<0
    func_result = simple_add(n1, n2, &res_long);
    minus_flag = 1;
    if (func_result == 1) func_result = 2;
  }

  if (!minus_flag1 && minus_flag2 && n1_great) {  // n1>0 & n2<0 & |n1|>|n2|
    inverse_decimal(&n2);
    simple_add(n1, n2, &res_long);
  }

  if (!minus_flag1 && minus_flag2 && !n1_great) {  // n1>0 & n2<0 & |n1|<|n2|
    inverse_decimal(&n1);
    simple_add(n1, n2, &res_long);
    minus_flag = 1;
  }

  if (minus_flag1 && !minus_flag2 && !n1_great) {  // n1<0 & n2>0 & |n1|<|n2|
    inverse_decimal(&n1);
    simple_add(n1, n2, &res_long);
  }

  if (minus_flag1 && !minus_flag2 && n1_great) {  // n1<0 & n2>0 & |n1|>|n2|
    inverse_decimal(&n2);
    simple_add(n1, n2, &res_long);
    minus_flag = 1;
  }

  *result = convert_long_to_decimal(res_long, 0, &mult, &func_result);
  set_multiplier(result, mult);
  if (minus_flag) set_minus(result);

  if (is_null(*result) && (minus_flag1)) set_minus(result);
  if (is_null(*result) && (!minus_flag1)) reset_minus(result);

  if (func_result == 2 && minus_flag) func_result = 3;

  return func_result;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal n1 = copy_decimal(value_1);
  s21_decimal n2 = copy_decimal(value_2);

  int minus_flag1 = get_minus(value_1);
  int minus_flag2 = get_minus(value_2);
  if (!minus_flag2) set_minus(&n2);
  if (minus_flag2) reset_minus(&n2);
  int func_result = s21_add(n1, n2, result);

  if (is_null(*result) && (!minus_flag1 || minus_flag2)) reset_minus(result);
  if (is_null(*result) && (minus_flag1 && minus_flag2)) set_minus(result);

  return func_result;
}

int get_left_index(s21_long_decimal number) {
  int i = 191;
  while (get_bit_status_long(number, i) == 0 && i != 0) {
    i--;
  }
  return i;
}

int get_rang(s21_long_decimal number) {
  int rang = 0;
  s21_long_decimal temp = {{1, 0, 0, 0, 0, 0}};
  while (!decimal_great(temp, number)) {
    rang++;
    decimal_mul_10(&temp, 1);
  }
  return rang;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_long_decimal res_long;
  reset_decimal_long(&res_long);
  int func_result = 0;

  reset_decimal(result);

  if (is_null(value_1) || is_null(value_2)) return func_result;

  s21_long_decimal n1 = convert_decimal_to_long(value_1);
  s21_long_decimal n2 = convert_decimal_to_long(value_2);

  int left_index = get_left_index(n2);
  s21_long_decimal temp = copy_decimal_long(n1);

  for (int i = 0; i < left_index + 1; i++) {
    if (i != 0) left_bit_shift(&temp, 1);
    if (get_bit_status_long(n2, i)) {
      simple_add(res_long, temp, &res_long);
    }
  }

  int minus_flag1 = get_minus(value_1);
  int minus_flag2 = get_minus(value_2);
  int mult1 = get_multiplier(value_1);
  int mult2 = get_multiplier(value_2);
  int mult = mult1 + mult2;
  // print_bits_long(res_long);

  // reset_decimal(result);
  *result = convert_long_to_decimal(res_long, 0, &mult, &func_result);

  reset_minus(result);
  if ((minus_flag1 && !minus_flag2) || (!minus_flag1 && minus_flag2))
    set_minus(result);

  set_multiplier(result, mult);

  return func_result;
}

int del_nulls(s21_long_decimal *number, int *mult) {
  s21_long_decimal temp = copy_decimal_long(*number);

  while (*mult != 0 && decimal_div_10(&temp, 1) == 0) {
    decimal_div_10(number, 1);
    *mult = *mult - 1;
  }
  return 0;
}

int is_null(s21_decimal num) {
  if (!num.bits[0] && !num.bits[1] && !num.bits[2])
    return 1;
  else
    return 0;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_decimal(result);
  int func_result = 0;

  if (is_null(value_2)) {
    func_result = 3;
    return func_result;
  }

  s21_long_decimal n1 = convert_decimal_to_long(value_1);
  s21_long_decimal n2 = convert_decimal_to_long(value_2);

  s21_long_decimal res_long;
  s21_long_decimal ost_long;

  int mult1 = get_multiplier(value_1);
  int mult2 = get_multiplier(value_2);
  int mult = 0;
  int rang1 = get_rang(n1);
  int rang2 = get_rang(n2);
  int shift = 30 - rang1 + rang2;

  decimal_mul_10(&n1, shift);
  // print_bits(n1);

  // decimal_normalize(value_1, value_2, &n1, &n2, &mult);

  mult = mult1 + shift - mult2;

  decimal_simple_div(n1, n2, &res_long, &ost_long);

  // inc_decimal_long(&res_long);

  del_nulls(&res_long, &mult);

  *result = convert_long_to_decimal(res_long, 1, &mult, &func_result);
  set_multiplier(result, mult);
  reset_minus(result);

  int minus_flag1 = get_minus(value_1);
  int minus_flag2 = get_minus(value_2);

  if ((minus_flag1 && !minus_flag2) || (!minus_flag1 && minus_flag2))
    set_minus(result);

  return func_result;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int func_result = 0;

  if (is_null(value_2)) {
    func_result = 3;
    return func_result;
  }

  s21_long_decimal n1;
  s21_long_decimal n2;
  s21_long_decimal div_result;
  s21_long_decimal div_mod;
  int mult = 0;

  int minus_flag1 = get_minus(value_1);
  int minus_flag2 = get_minus(value_2);

  decimal_normalize(value_1, value_2, &n1, &n2, &mult);
  decimal_simple_div(n1, n2, &div_result, &div_mod);

  *result = convert_long_to_decimal(div_mod, 2, &mult, &func_result);

  set_multiplier(result, mult);
  if ((minus_flag1 && !minus_flag2) || (minus_flag1 && minus_flag2))
    set_minus(result);

  return func_result;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  reset_decimal(dst);
  dst->bits[0] = abs(src);
  if (src < 0) set_minus(dst);
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;
  int mult = get_multiplier(src);
  s21_long_decimal num = convert_decimal_to_long(src);
  if (mult) decimal_div_10(&num, mult);
  if (num.bits[1]) result = 1;
  if (!num.bits[1]) {
    *dst = num.bits[0];
    if (get_minus(src)) *dst = *dst * (-1);
  }
  return result;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = 0;
  int mult = get_multiplier(value);
  int minus = get_minus(value);
  s21_long_decimal num = convert_decimal_to_long(value);
  int res_div = decimal_div_10(&num, mult);
  if (minus && (res_div || !is_null(value))) inc_decimal_long(&num);

  *result = convert_long_to_decimal(num, 0, &mult, &res);
  if (minus) set_minus(result);
  return res;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int res = 0;
  int mult = get_multiplier(value);
  int minus = get_minus(value);
  s21_long_decimal num = convert_decimal_to_long(value);
  int res_div = decimal_div_10(&num, mult);
  if (res_div == 1) inc_decimal_long(&num);

  *result = convert_long_to_decimal(num, 0, &mult, &res);
  if (minus) set_minus(result);
  return res;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  int mult = get_multiplier(value);
  int minus = get_minus(value);
  s21_long_decimal num = convert_decimal_to_long(value);
  decimal_div_10(&num, mult);

  *result = convert_long_to_decimal(num, 0, &mult, &res);
  if (minus) set_minus(result);
  return res;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  int minus = get_minus(value);
  *result = copy_decimal(value);
  if (minus) reset_minus(result);
  if (!minus) set_minus(result);
  return res;
}
