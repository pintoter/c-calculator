#include "s21_smartcalc.h"

double s21_smartcalc(const char *input, double x, int *err) {
  stack *operands = NULL;
  stack *operators = NULL;
  double res = 0;
  enum token previous_type = {0};
  while (*input != '\0' && !(*err)) {
    lexeme l = {0};
    if (*input == ' ') {
      input++;
    } else if (is_digit(*input)) {
      set_number(&input, &operands, &l, x, err);
      previous_type = NUMBERS;
    } else if (is_bracket(*input)) {
      set_separator(&input, &l, &operators, &operands, err);
      previous_type = SEPARATORS;
    } else {
      set_operation(&input, &l, &operators, &operands, previous_type, err);
      previous_type = OPERATIONS;
    }
  }
  while (!is_empty(operators) && !(*err))
    do_operation(pop(&operators), &operands, err);
  if (!(*err)) {
    res = pop(&operands).v.d;
  } else {
    while (!is_empty(operators)) {
      pop(&operators);
    }
    while (!is_empty(operands)) {
      pop(&operands);
    }
    res = 0;
  }
  return res;
}

void set_number(const char **input, stack **operands, lexeme *l, double x,
                int *err) {
  l->t = NUMBERS;
  if (**input == 'x') {
    l->v.d = x;
    (*input)++;
  } else if (is_double(*input)) {
    l->v.d = s21_atod(input, err);
  } else {
    l->v.d = (double)s21_atoi(input, err);
  }
  l->p = low;
  push(operands, *l);
}

void set_separator(const char **input, lexeme *l, stack **operators,
                   stack **operands, int *err) {
  l->t = SEPARATORS;
  if (**input == '(') {
    l->v.c = '(';
    l->p = max;
    push(operators, *l);
  } else {
    while (peek(*operators).v.c != '(') {
      do_operation(pop(operators), operands, err);
    }
    pop(operators);
  }
  (*input)++;
}

void set_operation(const char **input, lexeme *l, stack **operators,
                   stack **operands, int previous_type, int *err) {
  l->t = OPERATIONS;
  if (**input < 'a') {
    check_operator(input, l);
  } else {
    check_function(input, l);
  }
  if (((l->v.a == MINUS || l->v.a == PLUS) && previous_type == SEPARATORS &&
       peek(*operators).v.c == '(') ||
      ((l->v.a == MINUS || l->v.a == PLUS) && is_empty(*operators) &&
       is_empty(*operands))) {
    lexeme temp = {0};
    temp.t = NUMBERS;
    temp.v.d = 0;
    temp.p = low;
    push(operands, temp);
    push(operators, *l);
  } else if (is_empty(*operators) || l->p > check_priority(*operators) ||
             peek(*operators).t == SEPARATORS) {
    push(operators, *l);
  } else {
    while (!is_empty(*operators) && (l->p <= check_priority(*operators) &&
                                     peek(*operators).v.c != '(')) {
      do_operation(pop(operators), operands, err);
    }
    if (!(*err)) {
      push(operators, *l);
    } else {
      while (!is_empty(*operators)) {
        pop(operators);
      }
      while (!is_empty(*operands)) {
        pop(operands);
      }
    }
  }
}

void check_operator(const char **str, lexeme *l) {
  switch (**str) {
    case '+':
      l->v.a = PLUS;
      l->p = low;
      break;

    case '-':
      l->v.a = MINUS;
      l->p = low;
      break;

    case '*':
      l->v.a = MUL;
      l->p = medium;
      break;

    case '/':
      l->v.a = DIV;
      l->p = medium;
      break;

    case '^':
      l->v.a = POW;
      l->p = high;
      break;
  }
  (*str)++;
}

void check_function(const char **str, lexeme *l) {
  int skip_chars = 3;
  if (**str == 'c' && strncmp(*str, "cos", 3) == 0) {
    l->v.a = COS;
    l->p = high;
  } else if (**str == 's' && strncmp(*str, "sin", 3) == 0) {
    l->v.a = SIN;
    l->p = high;
  } else if (**str == 't' && strncmp(*str, "tan", 3) == 0) {
    l->v.a = TAN;
    l->p = high;
  } else if (**str == 'a' && strncmp(*str, "acos", 4) == 0) {
    l->v.a = ACOS;
    l->p = high;
    skip_chars = 4;
  } else if (**str == 'a' && strncmp(*str, "asin", 4) == 0) {
    l->v.a = ASIN;
    l->p = high;
    skip_chars = 4;
  } else if (**str == 'a' && strncmp(*str, "atan", 4) == 0) {
    l->v.a = ATAN;
    l->p = high;
    skip_chars = 4;
  } else if (**str == 's' && strncmp(*str, "sqrt", 4) == 0) {
    l->v.a = SQRT;
    l->p = high;
    skip_chars = 4;
  } else if (**str == 'l' && strncmp(*str, "ln", 2) == 0) {
    l->v.a = LN;
    l->p = high;
    skip_chars = 2;
  } else if (**str == 'l' && strncmp(*str, "log", 3) == 0) {
    l->v.a = LOG;
    l->p = high;
  } else if (**str == 'm' && strncmp(*str, "mod", 3) == 0) {
    l->v.a = MOD;
    l->p = medium;
  }
  *str += skip_chars;
}

void do_operation(lexeme sign, stack **operands, int *err) {
  switch (sign.v.a) {
    case PLUS:
      calculate_plus(operands);
      break;
    case MINUS:
      calculate_minus(operands);
      break;
    case MUL:
      calculate_multiply(operands);
      break;
    case DIV:
      calculate_divide(operands, err);
      break;
    case MOD:
      calculate_mod(operands);
      break;
    case POW:
      calculate_pow(operands);
      break;
    case COS:
      calculate_cos(operands);
      break;
    case SIN:
      calculate_sin(operands);
      break;
    case TAN:
      calculate_tan(operands, err);
      break;
    case ACOS:
      calculate_acos(operands, err);
      break;
    case ASIN:
      calculate_asin(operands, err);
      break;
    case ATAN:
      calculate_atan(operands);
      break;
    case SQRT:
      calculate_sqrt(operands, err);
      break;
    case LN:
      calculate_ln(operands, err);
      break;
    case LOG:
      calculate_log(operands, err);
      break;
  }
}

void calculate_plus(stack **operands) {
  if (enough_values(operands, 2)) {
    lexeme temp1 = pop(operands);
    lexeme temp2 = pop(operands);
    lexeme res = temp1;
    res.v.d = temp1.v.d + temp2.v.d;
    push(operands, res);
  }
}

void calculate_minus(stack **operands) {
  if (enough_values(operands, 2)) {
    lexeme temp1 = pop(operands);
    lexeme temp2 = pop(operands);
    lexeme res = temp1;
    res.v.d = temp2.v.d - temp1.v.d;
    push(operands, res);
  }
}

void calculate_multiply(stack **operands) {
  if (enough_values(operands, 2)) {
    lexeme temp1 = pop(operands);
    lexeme temp2 = pop(operands);
    lexeme res = temp1;
    res.v.d = temp2.v.d * temp1.v.d;
    push(operands, res);
  }
}

void calculate_divide(stack **operands, int *err) {
  if (enough_values(operands, 2) && fabs(peek(*operands).v.d) > PRECISION) {
    lexeme temp1 = pop(operands);
    lexeme temp2 = pop(operands);
    lexeme res = temp1;
    res.v.d = temp2.v.d / temp1.v.d;
    push(operands, res);
  } else {
    *err = 1;
  }
}

void calculate_mod(stack **operands) {
  if (enough_values(operands, 2)) {
    lexeme temp1 = pop(operands);
    lexeme temp2 = pop(operands);
    lexeme res = temp1;
    res.v.d = fmod(temp2.v.d, temp1.v.d);
    push(operands, res);
  }
}

void calculate_pow(stack **operands) {
  if (enough_values(operands, 2)) {
    lexeme temp1 = pop(operands);
    lexeme temp2 = pop(operands);
    lexeme res = temp1;
    res.v.d = pow(temp2.v.d, temp1.v.d);
    push(operands, res);
  }
}

void calculate_cos(stack **operands) {
  if (enough_values(operands, 1)) {
    lexeme res = pop(operands);
    res.v.d = cos(res.v.d);
    push(operands, res);
  }
}

void calculate_sin(stack **operands) {
  if (enough_values(operands, 1)) {
    lexeme res = pop(operands);
    res.v.d = sin(res.v.d);
    push(operands, res);
  }
}

void calculate_tan(stack **operands, int *err) {
  if (enough_values(operands, 1) && peek(*operands).v.d != M_PI_2) {
    lexeme res = pop(operands);
    res.v.d = tan(res.v.d);
    push(operands, res);
  } else {
    *err = 1;
  }
}

void calculate_acos(stack **operands, int *err) {
  if (enough_values(operands, 1) && fabs(peek(*operands).v.d) <= 1) {
    lexeme res = pop(operands);
    res.v.d = acos(res.v.d);
    push(operands, res);
  } else {
    *err = 1;
  }
}

void calculate_asin(stack **operands, int *err) {
  if (enough_values(operands, 1) && fabs(peek(*operands).v.d) <= 1) {
    lexeme res = pop(operands);
    res.v.d = asin(res.v.d);
    push(operands, res);
  } else {
    *err = 1;
  }
}

void calculate_atan(stack **operands) {
  if (enough_values(operands, 1)) {
    lexeme res = pop(operands);
    res.v.d = atan(res.v.d);
    push(operands, res);
  }
}

void calculate_sqrt(stack **operands, int *err) {
  if (enough_values(operands, 1) && peek(*operands).v.d >= 0) {
    lexeme res = pop(operands);
    res.v.d = sqrt(res.v.d);
    push(operands, res);
  } else {
    *err = 1;
  }
}

void calculate_ln(stack **operands, int *err) {
  if (enough_values(operands, 1) && peek(*operands).v.d > PRECISION) {
    lexeme res = pop(operands);
    res.v.d = log(res.v.d);
    push(operands, res);
  } else {
    *err = 1;
  }
}

void calculate_log(stack **operands, int *err) {
  if (enough_values(operands, 1) && peek(*operands).v.d > PRECISION) {
    lexeme res = pop(operands);
    res.v.d = log10(res.v.d);
    push(operands, res);
  } else {
    *err = 1;
  }
}
