#include "functionconfig.h"
#include <math.h>

double f1(double x) { return x*x-x*x*x*x+0.5; }
double f2(double x) { return x*x; }
double f3(double x) { return -.5*x + 1; }
double f4(double x) { return sin(x)*cos(x); }
double f5(double x) { return 1/x; }

double LagrangePolynomial(double x0, double* x, double* y, int n)
{
    double L = 0.0;
    int i,j;
    for (i=0; i<n; i++)
    {
        double s = 1.0;
        double m = 1.0;
        for (j=0; j < n; j++)
        {
            if (i != j)
            {
                s = s * (x0   - x[j]);
                m = m * (x[i] - x[j]);
            }
        }
        L = L + y[i] * (s/m);
    }

    return L;
}

double lagrange(double x)
{
    const int n = 20;
    double x1[] = {-2.0,  -1.8,     -1.6,    -1.4,    -1.2,    -1.0, -0.8,   -0.6,   -0.4,   -0.2,   0.0, 0.2,    0.4,     0.6,    0.8,    1.0, 1.2,     1.4,     1.6,    1.8,      2.0};
    double y1[] = {-11.5, -6.7576 , -3.4936, -1.3816 , -0.1336, 0.5, 0.7304, 0.7304, 0.6344, 0.5384, 0.5, 0.5384, 0.6344,  0.7304, 0.7304, 0.5, -0.1336, -1.3816, -3.4936, -6.7576, 11.5};
    return LagrangePolynomial(x, x1, y1, n);
}
