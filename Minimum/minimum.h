#ifndef MINIMUM_H
#define MINIMUM_H

#include "minimum_global.h"

typedef double (*R1Function)(double);
typedef double (*RnFunction)(double*, int);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Градиент функции
 * @param f         Целевая функция
 * @param x         Независимые переменные
 * @param n         Число переменных
 * @param dx        Длина шагов для нахождение градиента
 * @param gradients Вектор градиента функции
 */
void gradient(RnFunction f, double *x, int n, double dx, double *gradients);

/**
 * @brief Градиент функции по формуле f(x+dx)-f(x) / dx
 * @param f         Целевая функция
 * @param x         Независимые переменные
 * @param n         Число переменных
 * @param dx        Длина шагов для нахождение градиента
 * @param gradients Вектор градиента функции
 */
void gradient1(RnFunction f, double *x, int n, double dx, double *gradients);

/**
 * @brief Градиент функции по формуле f(x+dx)-f(x-dx) / 2dx
 * @param f         Целевая функция
 * @param x         Независимые переменные
 * @param n         Число переменных
 * @param dx        Длина шагов для нахождение градиента
 * @param gradients Вектор градиента функции
 */
void gradient2(RnFunction f, double *x, int n, double dx, double *gradients);

/**
 * @brief Норма вектора
 * @param vctr Вектор
 * @param n    Число елементов вектора
 * @return
 */
double vertor_norm(double *vctr, int n);

#ifdef __cplusplus
}
#endif

#endif // MINIMUM_H
