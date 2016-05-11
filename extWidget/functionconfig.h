#ifndef FUNCTIONCONFIG_H
#define FUNCTIONCONFIG_H

#include <function.h>

typedef struct
{
    R1Function *f;
    double a;
    double b;
    unsigned int penColor;
} FunctionConfig;

double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);
double f5(double x);

double LagrangePolynomial(double x0, double* x, double* y, int n);
double lagrange(double x);
double lagrange1(double x);
double argmin(double alpha);

#endif // FUNCTIONCONFIG_H
