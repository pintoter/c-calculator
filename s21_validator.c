#include "s21_smartcalc.h"

int s21_validator(const char *str) {
  int err = (str == NULL || strlen(str) > 255) ? 1 : 0;
  options prev_token = NOTHING, current_token = NOTHING;
  int count_brackets = 0;
  while (!err && str && *str) {
    if (*str == ' ') {
      str++;
    } else {
      current_token = check_current(&str, &err);

      if (current_token == OPEN_BRACKET) {
        count_brackets++;
      } else if (current_token == CLOSE_BRACKET) {
        count_brackets--;
      }

      if ((count_brackets < 0) ||
          (prev_token == OPEN_BRACKET && current_token == CLOSE_BRACKET) ||
          (prev_token == FUNCTION && current_token == ACTION) ||
          (prev_token == ACTION && current_token == ACTION) ||
          (current_token == FUNCTION &&
           (prev_token != ACTION && prev_token != OPEN_BRACKET &&
            prev_token != NOTHING)) ||
          ((prev_token == X && current_token == DIGIT) ||
           (prev_token == DIGIT && current_token == X)) ||
          ((current_token == X || current_token == DIGIT) &&
           (prev_token != ACTION && prev_token != NOTHING &&
            prev_token != OPEN_BRACKET)) ||
          (current_token == ACTION &&
           (prev_token != DIGIT && prev_token != X &&
            prev_token != CLOSE_BRACKET && prev_token != OPEN_BRACKET &&
            prev_token != NOTHING)) ||
          (current_token == OPEN_BRACKET && prev_token != ACTION &&
           prev_token != FUNCTION && prev_token != NOTHING)) {
        err = 1;
      }

      prev_token = current_token;
    }
  }
  if (!err && ((prev_token != DIGIT && prev_token != CLOSE_BRACKET &&
                prev_token != X) ||
               (count_brackets != 0)))
    err = 1;
  return err;
}

options check_current(const char **str, int *err) {
  options temp = 0;
  if (**str == 'x') {
    temp = X;
    (*str)++;
  } else if (is_digit(**str) || **str == '.') {
    while (is_digit(**str) || **str == '.') (*str)++;
    temp = DIGIT;
  } else if (is_bracket(**str) && **str == '(') {
    temp = OPEN_BRACKET;
    (*str)++;
  } else if (is_bracket(**str) && **str == ')') {
    temp = CLOSE_BRACKET;
    (*str)++;
  } else if (is_function(str)) {
    temp = FUNCTION;
  } else if (is_action(**str) ||
             (**str == 'm' && strncmp(*str, "mod", 3) == 0)) {
    temp = ACTION;
    if (**str != 'm')
      (*str)++;
    else
      (*str) += 3;
  } else {
    *err = 1;
  }
  return temp;
}

int is_action(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') ? 1 : 0;
}

int is_function(const char **str) {
  int skip_chars = 0;
  if (**str == 'c' && strncmp(*str, "cos", 3) == 0) {
    skip_chars = 3;
  } else if (**str == 's' && strncmp(*str, "sin", 3) == 0) {
    skip_chars = 3;
  } else if (**str == 't' && strncmp(*str, "tan", 3) == 0) {
    skip_chars = 3;
  } else if (**str == 'a' && strncmp(*str, "acos", 4) == 0) {
    skip_chars = 4;
  } else if (**str == 'a' && strncmp(*str, "asin", 4) == 0) {
    skip_chars = 4;
  } else if (**str == 'a' && strncmp(*str, "atan", 4) == 0) {
    skip_chars = 4;
  } else if (**str == 's' && strncmp(*str, "sqrt", 4) == 0) {
    skip_chars = 4;
  } else if (**str == 'l' && strncmp(*str, "ln", 2) == 0) {
    skip_chars = 2;
  } else if (**str == 'l' && strncmp(*str, "log", 3) == 0) {
    skip_chars = 3;
  }
  if (skip_chars) (*str) += skip_chars;
  return skip_chars;
}
