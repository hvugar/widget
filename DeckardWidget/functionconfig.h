#ifndef FUNCTIONCONFIG_H
#define FUNCTIONCONFIG_H

typedef double(*R1Function)(double x);
typedef double(*RnFunction)(double* x, int size);

typedef struct
{
    R1Function f;
    double a;
    double b;
    unsigned int penColor;
} FunctionConfig;

double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);

double LagrangePolynomial(double x0, double* x, double* y, int n);
double lagrange(double x);

#endif // FUNCTIONCONFIG_H
