#include "s21_smartcalc.h"

int is_digit(char c) { return ((c >= '0' && c <= '9') || c == 'x'); }

int is_bracket(char c) { return (c == '(' || c == ')'); }

int is_double(const char *str) {
  while (is_digit(*str)) str++;
  int res = (*str == '.') ? 1 : 0;
  return res;
}

int s21_atoi(const char **str, int *err) {
  int rate = 10;
  int res = 0;
  while (**str && is_digit(**str)) {
    res = res * rate + **str - '0';
    (*str)++;
    if (res < 0) {
      *err = 1;
    }
  }
  return res;
}

double s21_atod(const char **str, int *err) {
  double res = 0;
  res = (double)s21_atoi(str, err);
  if (**str == '.') {
    (*str)++;
    int n = 1;
    while (**str && is_digit(**str)) {
      res = res + (double)(**str - '0') / (double)pow(10, n);
      n++;
      (*str)++;
    }
  }
  return res;
}

priority check_priority(stack *operators) {
  lexeme temp = peek(operators);
  return temp.p;
}

int enough_values(stack **operands, int count) {
  int res = 0;
  if (count == 1) {
    res = is_empty(*operands);
  } else if (count == 2 && !is_empty(*operands)) {
    res = is_next_empty(*operands);
  }
  return (res == 0);
}
