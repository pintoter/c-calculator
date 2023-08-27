#include "../s21_smartcalc.h"

#include <check.h>

START_TEST(test_1) {
  char str[255] = "";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_2) {
  char str[255] = "1";
  double answer = 1;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_3) {
  char str[255] = "1)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_4) {
  char str[255] = "1+2";
  double answer = 3;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_5) {
  char str[255] = "2*5";
  double answer = 10;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_6) {
  char str[255] = "4/5";
  double answer = 0.8;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_7) {
  char str[255] = "3^3";
  double answer = 27;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_8) {
  char str[255] = "3*";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_9) {
  char str[255] = "2.5*3/8";
  double answer = 0.9375;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_10) {
  char str[255] = "***";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_11) {
  char str[255] = "25/0";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_12) {
  char str[255] = "sin";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_13) {
  char str[255] = "sin(1)";
  double answer = 0.841471;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_14) {
  char str[255] = "cos(1)";
  double answer = 0.540302;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_15) {
  char str[255] = "log(5)";
  double answer = 0.69897;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_16) {
  char str[255] = "ln(5)";
  double answer = 1.609438;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_17) {
  char str[255] = "asin(0.2)";
  double answer = 0.201358;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_18) {
  char str[255] = "acos(0.2)";
  double answer = 1.369438;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_19) {
  char str[255] = "tan(0.8)";
  double answer = 1.029639;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_20) {
  char str[255] = "atan(0.8)";
  double answer = 0.674741;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_21) {
  char str[255] = "2+7";
  double answer = 9;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_22) {
  char str[255] = "4.5*3";
  double answer = 13.5;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_23) {
  char str[255] = "1**24-1/0*sin()-1^^2";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_24) {
  char str[255] = "sin(cos(sin(cos(";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_25) {
  char str[255] = "7(7";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_26) {
  char str[255] = "sqrt(9)";
  double answer = 3;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_27) {
  char str[255] = "2.6-1.11";
  double answer = 1.49;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_28) {
  char str[255] = "7mod3";
  double answer = 1;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_29) {
  char str[255] = "x*2";
  double answer = 10;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 5, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_30) {
  char str[255] = "-1";
  double answer = -1;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_31) {
  char str[255] = "+1";
  double answer = 1;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_32) {
  char str[255] = "2**2";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_33) {
  char str[255] = "cos";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_36) {
  char str[255] = "sqrt(-1)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_37) {
  char str[255] = "asin(5)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_38) {
  char str[255] = "acos(-5)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_39) {
  char str[255] = "x+5";
  double answer = 10;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 5, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_40) {
  char str[255] = "x*3";
  double answer = 15;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 5, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_41) {
  char str[255] = "x/2";
  double answer = 2.5;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 5, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_42) {
  char str[255] = "xmod1.5";
  double answer = 0.5;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 5, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_43) {
  char str[255] = "sin(cos(2))";
  double answer = -0.404239;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_44) {
  char str[255] = "ln(2)+ln(3)-4+(5*6)^3.2+sin(10)";
  double answer = 53304.710856;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_45) {
  char str[255] = "5-3*2^4+5*(2.2*4.3)^2.1*5";
  double answer = 2757.988947;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_46) {
  char str[255] = "asin(0.1)^(2+0.5)*3-1";
  double answer = -0.990473;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_47) {
  char str[255] = "acos(2)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_50) {
  char str[255] = "2acos(2)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_51) {
  char str[255] = "(*1 + 2 * acos(2))";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_52) {
  char str[255] = "(1 + 2 + z * acos(2))";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_53) {
  char str[255] = "tan(1.57079632679489661923)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_54) {
  char str[255] =
      "(atan(1)+acos(1)+asin(1)+sqrt(1)+log(1)+ln(1))^1+sin(0)+cos(0)+tan(0)";
  double answer = 4.35619449019;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_55) {
  char str[255] = "(/)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_56) {
  char str[255] =
      "213671237621736512351263721536215361723576125367125376125321563751237125"
      "3";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_57) {
  char str[255] = "ln()";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_58) {
  char str[255] = "-(-5+6*8+10/(-1+6)+cos(0+5-5*2/2))";
  double answer = -46;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_59) {
  char str[255] = "-(.)";
  double answer = 0;
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_int_eq(answer, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_60) {
  char str[255] = "sqrt(-49)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_61) {
  char str[255] = "ln(-49)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_62) {
  char str[255] = "log(-49)";
  int error = s21_validator(str);
  double result = 0;
  if (!error) result = s21_smartcalc(str, 0, &error);
  ck_assert_double_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_1_credit) {
  char* str;
  credit_res result = s21_credit(1, 100000, 9.5, 36);
  ck_assert_str_eq("3569.44…2799.77", result.monthly_payment);
  asprintf(&str, "%.2f", result.interest_charges);
  ck_assert_str_eq("14645.83", str);
  free(str);
  asprintf(&str, "%.2f", result.summary);
  ck_assert_str_eq("114645.83", str);
  free(str);
}
END_TEST

START_TEST(test_2_credit) {
  char* str;
  credit_res result = s21_credit(0, 100000, 9.5, 36);
  ck_assert_str_eq("3203.29", result.monthly_payment);
  asprintf(&str, "%.2f", result.interest_charges);
  ck_assert_str_eq("15318.44", str);
  free(str);
  asprintf(&str, "%.2f", result.summary);
  ck_assert_str_eq("115318.44", str);
  free(str);
}
END_TEST

START_TEST(test_3_credit) {
  credit_res result = s21_credit(0, -100000, 9.5, 36);
  ck_assert_int_eq(1, result.err);
}
END_TEST

int main(void) {
  Suite* s = suite_create("suite_tests");
  TCase* tc = tcase_create("tests");
  SRunner* sr = srunner_create(s);
  int res = 0;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);
  tcase_add_test(tc, test_21);
  tcase_add_test(tc, test_22);
  tcase_add_test(tc, test_23);
  tcase_add_test(tc, test_24);
  tcase_add_test(tc, test_25);
  tcase_add_test(tc, test_26);
  tcase_add_test(tc, test_27);
  tcase_add_test(tc, test_28);
  tcase_add_test(tc, test_29);
  tcase_add_test(tc, test_30);
  tcase_add_test(tc, test_31);
  tcase_add_test(tc, test_32);
  tcase_add_test(tc, test_33);
  tcase_add_test(tc, test_36);
  tcase_add_test(tc, test_37);
  tcase_add_test(tc, test_38);
  tcase_add_test(tc, test_39);
  tcase_add_test(tc, test_40);
  tcase_add_test(tc, test_41);
  tcase_add_test(tc, test_42);
  tcase_add_test(tc, test_43);
  tcase_add_test(tc, test_44);
  tcase_add_test(tc, test_45);
  tcase_add_test(tc, test_46);
  tcase_add_test(tc, test_47);
  tcase_add_test(tc, test_50);
  tcase_add_test(tc, test_51);
  tcase_add_test(tc, test_52);
  tcase_add_test(tc, test_53);
  tcase_add_test(tc, test_54);
  tcase_add_test(tc, test_55);
  tcase_add_test(tc, test_56);
  tcase_add_test(tc, test_57);
  tcase_add_test(tc, test_58);
  tcase_add_test(tc, test_59);
  tcase_add_test(tc, test_60);
  tcase_add_test(tc, test_61);
  tcase_add_test(tc, test_62);
  tcase_add_test(tc, test_1_credit);
  tcase_add_test(tc, test_2_credit);
  tcase_add_test(tc, test_3_credit);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  res = srunner_ntests_failed(sr);
  srunner_free(sr);
  return res == 0 ? 0 : 1;
}
