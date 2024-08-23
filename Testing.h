#ifndef __TESTING_H__
#define __TESTING_H__

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

/**
* @brief              Функция, проверяющая программу на заданном тесте
* @param nTest        Номер теста
* @param structData   Структура, содержащая данные для тестирования
* @return             0 при успешном прохождении теста, -1 при ошибке
*/
int Test(int nTest, struct coeffsStruct structData);

/**
* @brief        Функция, заполняющая массив заданными данными для тестирования
*/
void CreateTests ();

/**
* @brief        Функция, запускающая тесты
* @param tests  Массив с данными для тестов
*/
void RunAllTests(coeffsStruct tests[]);

#endif
