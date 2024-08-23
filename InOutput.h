#ifndef __INOUTPUT_H__
#define __INOUTPUT_H__

/**
* @brief   Функция для ввода коэффициентов
* @param a Главный коэффициент
* @param b Второй коэффициент
* @param c Свободный член
*/
void input (double *a, double *b, double *c);

/**
* @brief        Функция вывода корней уравнения
* @param nRoots Количество корней
* @param x1     Первый корень
* @param x2     Второй корень
*/
void output (int nRoots, double x1, double x2);

#endif
