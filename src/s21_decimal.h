#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

#define S21_INT_MAX 4294967295

int s21_decimal_add(s21_decimal num1, s21_decimal num2, s21_decimal *res_num);
int s21_decimal_sub(s21_decimal num1, s21_decimal num2, s21_decimal *res_num);
int s21_decimal_mul(s21_decimal num1, s21_decimal num2, s21_decimal *res_num);
int s21_decimal_div(s21_decimal num1, s21_decimal num2, s21_decimal *res_num);
int s21_decimal_mod(s21_decimal num1, s21_decimal num2, s21_decimal *res_num);

int s21_decimal_great(s21_decimal num1, s21_decimal num2);

s21_decimal new_decimal(unsigned int bit0, unsigned int bit1, unsigned int bit2,
                        int minus, int multiplier);
int get_bit_status(s21_decimal num, int index);
void set_bit(s21_decimal *num, int index);
void reset_bit(s21_decimal *num, int index);
int simple_add(s21_decimal num1, s21_decimal num2, s21_decimal *result);
int get_multiplier(s21_decimal number);
void set_multiplier(s21_decimal *number, int multipler);
int left_bit_shift(s21_decimal *number, int count);
int decimal_mul_10(s21_decimal *number, int count);
void set_minus(s21_decimal *number);
void reset_minus(s21_decimal *number);
int get_minus(s21_decimal number);
int decimal_div_10(s21_decimal *number, int count);

int decimal_great(s21_decimal num1, s21_decimal num2);
int decimal_equal(s21_decimal num1, s21_decimal num2);
int decimal_lite(s21_decimal num1, s21_decimal num2);

void reset_decimal(s21_decimal *number);
s21_decimal copy_decimal(s21_decimal number);
void inverse_decimal(s21_decimal *number);
int get_left_index(s21_decimal number);
int del_nulls(s21_decimal *number);

int decimal_simple_div(s21_decimal dividend, s21_decimal divider,
                       s21_decimal *result);

// for DEBUG; временно, удалить в конечной версии ------
void print_decimal(s21_decimal number);
void print_bits(s21_decimal num);

#endif  // SRC_S21_DECIMAL_H_
