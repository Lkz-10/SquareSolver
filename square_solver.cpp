#include <stdio.h>
#include <TXLib.h>
#include <math.h>

/**
* @brief                 Структура коэффициентов и корней
* @param a               Главный коэффициент уравнения
* @param b               Второй коэффициент уравнения
* @param c               Свободный член уравнения
* @param x1_expexted     Первый корень уравнения
* @param x2_expected     Второй корень уравнения
* @param nRoots_expected Количество корней уравнения
*/
struct coeffsStruct
{
    double a;
    double b;
    double c;
    double x1_expected;
    double x2_expected;
    int nRoots_expected;
};

const int SS_INF_ROOTS = -1;
const int SS_NO_ROOTS  =  0;
const int SS_ONE_ROOT  =  1;
const int SS_TWO_ROOTS =  2;

int SolveSquare (double a, double b, double c, double *x1, double *x2);
int SolveLine (double b, double c, double *x1);
int SolveAB (double a, double b, double* x1, double* x2);
int SolveAC (double a, double c, double* x1, double* x2);

bool CompareZero(double a);

int choose();

void input (double *a, double *b, double *c);
void output(int nRoots, double x1, double x2);
void BufferClear();

void swapDouble (double *a, double *b);

int Test(int nTest, struct coeffsStruct structData);

void CreateTests ();

void RunAllTests(coeffsStruct tests[]);

/**
*@brief Главная функция, вызывающая другие для решения поставленной задачи
*/
int main()
{
    if (choose() == 1) {

        double a = NAN, b = NAN, c = NAN;

        input(&a, &b, &c);

        assert(isfinite(a));
        assert(isfinite(b));
        assert(isfinite(c));

        int nRoots = 0;
        double x1 = NAN, x2 = NAN;

        nRoots = SolveSquare(a, b, c, &x1, &x2);

        output(nRoots, x1, x2);

    } else {

        CreateTests();
    }
}

/**
* @brief    Функция решения квадратного уравнения
* @param a  Главный коэффициент уравнения
* @param b  Второй коэффициент уравнения
* @param c  Свободный член уравнения
* @param x1 Первый полученный корень уравнения
* @param x2 Второй полученный корень уравнения
* @return   Количество корней квадратного уравнения
*/
int SolveSquare (double a, double b, double c, double* x1, double* x2)
{
    assert(x1);
    assert(x2);
    assert(x1 != x2);

    if (CompareZero(a)) {              // a == 0
        return SolveLine(b, c, x1);
    }
    if (CompareZero(b)) {              // b == 0
        return SolveAC(a, c, x1, x2);
    }
    if (CompareZero(c)) {              // c == 0
        return SolveAB(a, b, x1, x2);
    }
    double disc = b*b - 4*a*c;
    if (disc < 0) {
        return SS_NO_ROOTS;
    }
    if (CompareZero(disc)) {           // disc == 0
        *x1 = -b/(2*a);
        return SS_ONE_ROOT;
    }
    double sqrtd = sqrt(disc);

    *x1 = (-b + sqrtd)/(2*a);
    *x2 = (-b - sqrtd)/(2*a);

    return SS_TWO_ROOTS;
}

/**
* @brief    Решение линейного уравнения
* @param b  Коэффициент при x
* @param c  Свободный член уравнения
* @param x1 Полученный корень линейного уравнения
* @return   Количество корней линейного уравнения
*/
int SolveLine (double b, double c, double* x1)
{
    if (CompareZero(b)) {                                         // b == 0
            return (CompareZero(c))? SS_INF_ROOTS : SS_NO_ROOTS;  // c == 0
        }
        *x1 = -c/b;
        return SS_ONE_ROOT;
}

/**
* @brief    Функция для решения уравннения при нулевом втором коэффициенте
* @param a  Главный коэффициент
* @param c  Свободный член
* @param x1 Первый полученный корень
* @param x2 Второй полученный корень
* @return   Количество корней уравнения
*/
int SolveAC (double a, double c, double* x1, double* x2)   // if b == 0
{
    if (CompareZero(c)) {                                  //if c == 0 too
        *x1 = 0;
        return SS_ONE_ROOT;
    }
    if (-c/a < 0) {
        return SS_NO_ROOTS;
    }

    *x1 = sqrt(-c/a);
    *x2 = -*x1;

    return SS_TWO_ROOTS;
}

/**
* @brief    Функция решения уравнения при нулевом свободном члене
* @param a  Главный коэффициент
* @param b  Второй коэффициент
* @param x1 Первый полученный корень
* @param x2 Второй полученный корень
* @return   Количество корней уравнения
*/
int SolveAB (double a, double b, double* x1, double* x2)
{
    *x1 = 0;
    *x2 = -b/a;

    return SS_TWO_ROOTS;
}

/**
* @brief              Функция, проверяющая программу на заданном тесте
* @param nTest        Номер теста
* @param structData   Структура, содержащая данные для тестирования
* @return             0 при успешном прохождении теста, -1 при ошибке
*/
int Test(int nTest, struct coeffsStruct structData)
{
    double x1 = NAN, x2 = NAN;

    int nRoots = SolveSquare(structData.a, structData.b, structData.c, &x1, &x2);

    if (isfinite(structData.x2_expected) && structData.x1_expected < structData.x2_expected) {
        swapDouble(&structData.x1_expected, &structData.x2_expected);
    }

    bool x1_nan = false, x2_nan = false;

    if (!isfinite(x1) && !isfinite(structData.x1_expected)) x1_nan = true;
    if (!isfinite(x2) && !isfinite(structData.x2_expected)) x2_nan = true;

    if (nRoots != structData.nRoots_expected || (!x1_nan && !CompareZero(x1-structData.x1_expected)) ||
        (!x2_nan && !CompareZero(x2-structData.x2_expected))) {

        printf("Error Test %d: a = %lg, b = %lg, c = %lg, nRoots = %d, x1 = %lg, x2 = %lg\n"
               "Expected: nRoots = %d, x1 = %lg, x2 = %lg\n", nTest, structData.a, structData.b, structData.c,
               nRoots, x1, x2, structData.nRoots_expected, structData.x1_expected, structData.x2_expected);

        return -1;
    }
    return 0;
}

/**
* @brief        Функция, заполняющая массив заданными данными для тестирования
*/
void CreateTests ()
{
    coeffsStruct tests[] = {

    {.a = 1,      .b = -3,       .c = 2,      .x1_expected = 1,          .x2_expected = 2,          //два корня
     .nRoots_expected = 2},


    {.a = 0,      .b = 0,        .c = 0,      .x1_expected = NAN,        .x2_expected = NAN,        //бесконечно корней
     .nRoots_expected = SS_INF_ROOTS},


    {.a = 2,      .b = 4,        .c = 2,      .x1_expected = -1,         .x2_expected = NAN,        //1 корень, D = 0
     .nRoots_expected = 1},

    {.a = 18,     .b = 4,        .c = 41,     .x1_expected = NAN,        .x2_expected = NAN,        //0 корней, D < 0
     .nRoots_expected = 0},

    {.a = 0,      .b = 16,       .c = 21,     .x1_expected = -1.3125,    .x2_expected = NAN,        //линейное
     .nRoots_expected = 1},

    {.a = 2.1,    .b = 3.85,     .c = -16.84, .x1_expected = 2.059795,   .x2_expected = -3.893129,  //дробные
     .nRoots_expected = 2},

    {.a = 0.0008, .b = 0.000016, .c = -0.032, .x1_expected = 6.31456322, .x2_expected = -6.3345632, //маленькие значения
     .nRoots_expected = 2},

    {.a = 4,      .b = 0,        .c = 60,     .x1_expected = NAN,        .x2_expected = NAN,        //b=0, 0 корней
     .nRoots_expected=0},

    {.a = 125,    .b = 0,        .c = -64,    .x1_expected = 0.7155418,  .x2_expected = -0.7155418, //b=0, 2 корня
     .nRoots_expected=2},

    {.a = 45,     .b = 12,       .c = 0,      .x1_expected = 0,          .x2_expected = -0.266667,  //c=0, 2 корня
     .nRoots_expected = 2}
    };

    RunAllTests(tests);
}

/**
* @brief        Функция, запускающая тесты
* @param tests  Массив с данными для тестов
*/
 void RunAllTests(coeffsStruct tests[])
 {
       const int nTests = 10;

       for (int i = 0; i < nTests; ++i) {
            if (Test(i+1, tests[i]) == 0) {
                printf("Test %2d completed successfully\n", i+1);
            }
       }
 }

/**
* @brief  Функция, позволяющая пользователю выбрать, хочет он решить уравнение или запустить тесты
* @return Выбор пользователя
*/
 int choose()
 {
    printf("If you want to solve a square equation enter 1,\n"
           "If you want to run tests enter 0:\n");

    int choice = 0;
    scanf("%d", &choice);

    return choice;
 }

/**
* @brief   Функция для ввода коэффициентов
* @param a Главный коэффициент
* @param b Второй коэффициент
* @param c Свободный член
*/
void input (double *a, double *b, double *c)
{
    assert(a);
    assert(b);
    assert(c);
    assert(a != b && a != c && b != c);

    printf("Enter the coefficients:\n");

    while (scanf("%lg %lg %lg", a, b, c) != 3) {
        BufferClear();
        printf("Error, Enter three coefficients:\n");
    }

}

/**
* @brief        Функция вывода корней уравнения
* @param nRoots Количество корней
* @param x1     Первый корень
* @param x2     Второй корень
*/
void output (int nRoots, double x1, double x2)
{
    switch (nRoots)
    {
        case SS_NO_ROOTS:
            printf("No roots\n");
            break;

        case SS_ONE_ROOT:
            printf("One root, x = %lg\n", x1);
            break;

        case SS_TWO_ROOTS:
            printf("Two roots, x1 = %lg, x2 = %lg\n", x1, x2);
            break;

        case SS_INF_ROOTS:
            printf("Infinite amount of roots\n");
            break;

        default:
            printf("ERROR\n");
    }
}

/**
* @brief   Функция для сравнения чисел типа double с нулем
* @param a Число типа double
* @return  true, если число близко к нулю, false в противном случае
*/
bool CompareZero(double a)
{
    const double EPS = 0.000001;
    return fabs(a) < EPS;
}

/**
* @brief   Функция, меняющая значения двух переменных между собой
* @param a Первая переменная
* @param b Вторая переменная
*/
 void swapDouble (double *a, double *b)
 {
    double temp = 0;

    temp = *a;
    *a = *b;
    *b = temp;
 }

/**
* @brief Функция очистки буфера ввода
*/
void BufferClear()
{
    while (getchar() != '\n' && getchar() != EOF) {}
}

