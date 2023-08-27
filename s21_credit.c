#include "s21_smartcalc.h"

credit_res s21_credit(type_payment type, int S, double P, int N) {
  credit_res res = {0};
  res.err = s21_validator_credit(S, P, N);
  char *str = NULL;

  double monthly_all = 0;

  if (!(res.err)) {
    if (type == annuitive) {
      asprintf(&str, MP_ANNUITIVE, S, P, P, N, P, N);
      monthly_all = s21_smartcalc(str, 0, &(res.err));
      free(str);

      /* костыль. */
      asprintf(&str, "%.2lf", monthly_all);
      strcpy(res.monthly_payment, (const char *)str);
      free(str);

      asprintf(&str, SUM, monthly_all, N);
      res.summary = s21_smartcalc(str, 0, &(res.err));
      free(str);

      asprintf(&str, OVERPAYMENT, res.summary, S);
      res.interest_charges = s21_smartcalc(str, 0, &(res.err));
      free(str);

    } else if (type == differentiated) {
      double loan_balance = 0, main_debt = 0, monthly_debt = 0,
             start_payment = 0, end_payment = 0;
      struct tm *u;
      int day_m, day_y;
      char s1[40] = {0};

      const time_t now = time(NULL);
      u = localtime(&now);

      /* Находим постоянную часть платежа, которая уходит на основной долг */
      asprintf(&str, "%d/%d", S, N);
      main_debt = s21_smartcalc(str, 0, &(res.err));
      free(str);

      asprintf(&str, "%lf", main_debt);
      main_debt = atof(str);
      free(str);

      // Нашли постоянную

      asprintf(&str, "%lf/100", P);
      P = s21_smartcalc(str, 0, &(res.err));
      free(str);

      /* Остаток задолженности */
      for (int i = 0; i < N && !(res.err); i++) {
        int current_month = (u->tm_mon) % 12 + 1;
        day_m = check_month(current_month);
        if (i == 0 || current_month == 1) {
          day_y = check_year(u->tm_year);
        }

        if (day_y == 366 && current_month == 2) day_m += 1;

        /* Рассчет остатка основного долга */
        asprintf(&str, "%d-%d*%lf", S, i, main_debt);
        loan_balance = s21_smartcalc(str, 0, &(res.err));
        free(str);

        /* Расчет ежемесячной составляющей */
        asprintf(&str, "%lf * %lf / 12", loan_balance, P);
        monthly_debt = s21_smartcalc(str, 0, &(res.err));
        free(str);
        asprintf(&str, "%lf+%lf", monthly_debt, res.interest_charges);
        res.interest_charges = s21_smartcalc(str, 0, &(res.err));
        ;
        free(str);

        /* Рассчет суммы за текущий месяц */
        asprintf(&str, "%lf+%lf", main_debt, monthly_debt);
        monthly_all = s21_smartcalc(str, 0, &(res.err));
        free(str);
        asprintf(&str, "%lf+%lf", monthly_all, res.summary);
        res.summary = s21_smartcalc(str, 0, &(res.err));
        ;
        free(str);

        if (i == 0) {
          start_payment = monthly_all;
        } else if (i == N - 1) {
          end_payment = monthly_all;
        }

        strftime(s1, 80, "%d.%m.%Y", u);

        u->tm_mday += day_m;
        time_t next = mktime(u);
        u = localtime(&next);
      }

      sprintf(res.monthly_payment, "%.2lf…%.2lf", start_payment, end_payment);
    }
  }
  return res;
}

int s21_validator_credit(double S, double P, int N) {
  return (S > 0 && P > 0 && P < 100 && N <= 360) ? 0 : 1;
}

int check_year(int current_year) {
  return (current_year % 4 == 0 || current_year % 100 == 0 ||
          current_year % 400 == 0)
             ? 366
             : 365;
}

int check_month(int current_month) {
  int res = 31;
  if (current_month == 4 || current_month == 6 || current_month == 9 ||
      current_month == 11) {
    res = 30;
  } else if (current_month == 2) {
    res = 28;
  }
  return res;
}
