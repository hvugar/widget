#ifndef FUNCTIONCONFIG_H
#define FUNCTIONCONFIG_H

typedef double(*R1Function)(double x);
typedef double(*RnFunction)(double* x, int size);

typedef struct
{
    R1Function f;
    int a;
    int b;
    QPen pen;
} FunctionConfig;

#endif // FUNCTIONCONFIG_H
