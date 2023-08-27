/**
 * @file s21_smartcalc.h
 * @author pintoter
 * @brief Файл содержит описание функций, используемых в проекте
 */

#ifndef SRC_S21_SMARTCALC_H
#define SRC_S21_SMARTCALC_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PRECISION 1E-7

/**
 * @brief Виды лексем в выражении
 */
typedef enum options {
    NOTHING, /**< Ничего */
    X, /**< Переменная */
    DIGIT, /**< Число */
    ACTION, /**< Математическое действие */
    FUNCTION, /**< Математическая функция */
    OPEN_BRACKET, /**< Открывающаяся скобка */
    CLOSE_BRACKET /**< Закрывающаяся скобка */
} options;

/**
 * @brief Объединение видов лексем в обработанной строке
 *
 * Необходимо для работы самого калькулятора (расставление приоритетов, рраспределние по стекам)
 */
typedef enum token {
    NUMBERS, /**< Число */
    OPERATIONS, /**< Операция */
    SEPARATORS /**< Разделитель */
} token;

/**
 * @brief Операции, поддерживаемые калькулятором
 */
typedef enum arithmetic {
    PLUS, /**< ++ */
    MINUS, /**< -- */
    MUL, /**< ** */
    DIV, /**< / */
    MOD, /**< mod */
    POW, /**< ^ */
    COS, /**< cos() */
    SIN, /**< sin() */
    TAN, /**< tan() */
    ACOS, /**< acos() */
    ASIN, /**< asin() */
    ATAN, /**< atan() */
    SQRT, /**< sqrt() */
    LN, /**< ln() */
    LOG /**< log() */
} arithmetic;

/**
 * @brief Объединение всех возможных значений
 *
 * @param d значение с точной
 * @param c значение символа
 * @param a значение операций
 */
typedef union value {
    double d;
    char c;
    arithmetic a;
} value;

/**
 * @brief Объединение всех возможных значений
 *
 * Используется в структуре лексемы
*/
typedef enum priority {
    low, /**< Низкий приоритет */
    medium, /**< Средний приоритет */
    high, /**< Высокий приоритет */
    max /**< Максимальный приоритет */
} priority;

/**
 * @brief Структура лексемы
 *
 * Используется как основной тип данных в калькуляторе
*/
typedef struct lexeme {
    token t; /**< Тип токена (перечисление) */
    value v; /**< Значение (объединение) */
    priority p; /**< Приоритет */
} lexeme;

/**
\brief Стек
Используется 2 стека (1 - для операций, 2 - для значений)
*/
typedef struct stack {
    lexeme l; /**< Лексема */
    struct stack *next; /**< Ссылка на следующий */
} stack;

/**
\brief Валидатор строки
\param str Входная строка
\return Возвращает true или false (правильная или нет)
*/
int s21_validator(const char *str);
/**
\brief Вычисление значения
\param input Входная строка
\param paste Значение переменной X
\param err Указатель на наличие ошибок
\return Результат выражения
*/
double s21_smartcalc(const char *input, double paste, int *err);
/**
\brief Определение текущего элемента (его принадлежности) строки в валидаторе
\param str Входная строка
\param err Указатель на наличие ошибок
\return Тип лексемы
*/
options check_current(const char **str, int *err);
/**
\brief Обработка значений
\param input Входная строка
\param operands Указатель на стек чисел
\param l Значения параметров лексемы
\param x Значение переменной X
\param err Указатель на наличие ошибок
*/
void set_number(const char **input, stack **operands, lexeme *l, double x, int *err);
/**
\brief Обработка разделителей
\param input Входная строка
\param l Значения параметров лексемы
\param operators Указатель на стек операций
\param operands Указатель на стек чисел
\param err Указатель на наличие ошибок
*/
void set_separator(const char **input, lexeme *l, stack **operators, stack **operands, int *err);
/**
\brief Обработка операций
\param input Входная строка
\param l Значения параметров лексемы
\param operators Указатель на стек операций
\param operands Указатель на стек чисел
\param previous_type Предыдущий тип лексемы
\param err Указатель на наличие ошибок
*/
void set_operation(const char **input, lexeme *l, stack **operators, stack **operands, int previous_type, int *err);
/**
\brief Проверка на математическую функцию
\param str Входная строка
\return Возвращает true или false
*/
int is_function(const char **str);
/**
\brief Проверка на действие
\param c Входной символ
\return Возвращает true или false
*/
int is_action(char c);
/**
\brief Проверка на число
\param c Входной символ
\return Возвращает true или false
*/
int is_digit(char c);
/**
\brief Проверка на разделитель
\param c Входной символ
\return Возвращает true или false
*/
int is_bracket(char c);
/**
\brief Проверка на десятичное число
\param str Входная строка
\return Возвращает true или false
*/
int is_double(const char *str);
/**
\brief Перевод из строки в целочисленное значение
\param str Входная строка
\param err Указатель на наличие ошибок
\return Возвращает число (int)
*/
int s21_atoi(const char **str, int *err);
/**
\brief Перевод из строки в десятичное число
\param str Входная строка
\param err Указатель на наличие ошибок
\return Возвращает число (double)
*/
double s21_atod(const char **str, int *err);
/**
\brief Положить значение в стек
\param head Головной элемент стека
\param l Значения параметров лексемы
\return Возвращает число (double)
*/
void push(stack **head, lexeme l);
/**
\brief Проверка на пустоту стека
\param head Головной элемент стека
\return Возвращает true или false (пустой или нет)
*/
int is_empty(stack *head);
int is_next_empty(stack *head);
/**
\brief Посмотреть элемент стека
\param head Головной элемент стека
\return Возвращает значение параметров лексемы
*/
lexeme peek(stack *head);
/**
\brief Достать значение из стека
\param head Головной элемент стека
\return Возвращает значение параметров лексемы
*/
lexeme pop(stack **head);
/**
\brief Устанавливает значение оператора в лексеме
*/
void check_operator(const char **str, lexeme *l);
/**
\brief Устанавливает значение функции в лексеме
*/
void check_function(const char **str, lexeme *l);
/**
\brief Проверка приоритета верхнего элемента стека
\return Возвращает приоритет операции
*/
priority check_priority(stack *operators);
/**
\brief Выполнить операцию
*/
void do_operation(lexeme sign, stack **operands, int *err);
/**
\brief Проверка на достаточное количество элементов в стеке для выполнения операции
*/
int enough_values(stack **operands, int count);
/**
\brief +
 Вычисление операции сложение
*/
void calculate_plus(stack **operands);
/**
\brief -
 Вычисление операции вычитание
*/
void calculate_minus(stack **operands);
/**
\brief *
 Вычисление операции умножение
*/
void calculate_multiply(stack **operands);
/**
\brief /
 Вычисление операции деление
*/
void calculate_divide(stack **operands, int *err);
/**
\brief mod
  Вычисление операции остаток
*/
void calculate_mod(stack **operands);
/**
\brief ^
 Вычисление операции возведение в степень
*/
void calculate_pow(stack **operands);
/**
\brief cos()
 Вычисление операции косинус
*/
void calculate_cos(stack **operands);
/**
\brief sin()
 Вычисление операции синус
*/
void calculate_sin(stack **operands);
/**
\brief tan()
 Вычисление операции тангенс
*/
void calculate_tan(stack **operands, int *err);
/**
\brief acos()
 Вычисление операции арккосинус
*/
void calculate_acos(stack **operands, int *err);
/**
\brief asin()
 Вычисление операции арксинус
*/
void calculate_asin(stack **operands, int *err);
/**
\brief atan()
 Вычисление операции арктангенс
*/
void calculate_atan(stack **operands);
/**
\brief sqrt
 Вычисление операции квадратный корень
*/
void calculate_sqrt(stack **operands, int *err);
/**
\brief ln
 Вычисление операции натуральный логарифм
*/
void calculate_ln(stack **operands, int *err);
/**
\brief log
 Вычисление операции десятичный логарифм
*/
void calculate_log(stack **operands, int *err);

#define MP_ANNUITIVE "%d*%.2lf/12/100*(1+%.2lf/12/100)^%d/((1+%.2lf/12/100)^%d-1)" /**< Строка для расчета ежемесячного платежа*/
#define SUM "%.2lf*%d" /**< Общая сумма кредита */
#define OVERPAYMENT "%.2lf-%d" /**< Переплата по процентам */

/**
\brief Режимы видов платежей
*/
typedef enum type_payment {
    annuitive = 0, /**< Аннуитетный тип платежа */
    differentiated /**< Дифференцированный тип платежа*/
} type_payment;

/**
\brief Структура результата кредитного калькулятора
*/
typedef struct credit_res {
    char monthly_payment[40]; /**< Ежемесячный платеж */
    double interest_charges; /**< Переплата по процентам */
    double summary; /**< Общая сумма */
    int err; /**< Ошибка при расчете */
} credit_res;


/**
 * @brief Расчет параметров кредите
 *
 * @param type значение с точной
 * @param S сумма кредита
 * @param P годовая ставка
 * @param N количество месяцев
 * @return Возвращает ежемесячный платеж, переплату по процентам и общую переплату
 */
credit_res s21_credit(type_payment type,int S, double P, int N);
/**
\brief Кредитный валидатор
*/
int s21_validator_credit(double S, double P, int N);
/**
\brief Проверка является ли год високосным
 \param current_year
 \return Возвращает количество дней в году
*/
int check_year(int current_year);
/**
\brief Проверить количество дней в текущем месяце
\param current_month
 \return Возвращает количество дней в месяце
*/
int check_month(int current_month);

#endif // SRC_S21_SMARTCALC_H

