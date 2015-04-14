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

double lagrange1(double x)
{
    const int n = 11;
    double x1[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    double y1[] = {-0.4737532590,
                   -0.3174120924,
                   -0.1785954885,
                   -0.0563262682,
                   +0.0501161120,
                   +0.1411845656,
                   +0.2170430411,
                   +0.2775385249,
                   +0.3221627883,
                   +0.3500033738,
                   +0.3596788553};
    return LagrangePolynomial(x, x1, y1, n);
}


double smp1_JSum_5(double *t, double *x1, double *x2, double n, double *u, int N)
{
    double sum = 0.0;
    int i=0;
    for (i=0; i<(N-1); i++)
    {
        int j=i+1;
        double fj = (x1[j]-t[j]*t[j]*t[j])*(x1[j]-t[j]*t[j]*t[j]) + x2[j]*x2[j] - t[j]*t[j] + (2*u[j] - 1.0)*(2*u[j] - 1.0);
        double fi = (x1[i]-t[i]*t[i]*t[i])*(x1[i]-t[i]*t[i]*t[i]) + x2[i]*x2[i] - t[i]*t[i] + (2*u[i] - 1.0)*(2*u[i] - 1.0);
        sum = sum + 0.5 * (fj+fi) * (t[j]-t[i]);
    }
    sum = sum + (x2[N-1]-1.0) * (x2[N-1]-1.0);
    return sum;
}

double argmin(double alpha)
{
    double t[]  = {0.00000000,   0.10000000,   0.20000000,   0.30000000,   0.40000000,   0.50000000,   0.60000000,   0.70000000,   0.80000000,   0.90000000,   1.00000000};
    double u[] =    {  0.29321431,   0.35108648,   0.40752216,   0.46520950,   0.52577606,   0.59004902,   0.65828904,   0.73036954,   0.80590279,   0.88433436,   0.96506883};
    double x1[] =   {  0.00000000,   0.00018439,   0.00133280,   0.00389660,   0.00771570,   0.01200537,   0.01551683,   0.01713669,   0.01732823,   0.02098720,   0.04239520};
    double x2[] =   {  0.00000000,   0.04347435,   0.07904796,   0.10538096,   0.11981166,   0.11837604,   0.09577907,   0.04535031,  -0.04093992,  -0.17227040,  -0.35835376};
    double gr[] =   { 17.98432619,  15.75828998,  13.60607955,  11.57810922,   9.70599756,   8.00553353,   6.47790229,   5.11063108,   3.87990478,   2.75593386,   1.71286445};

    int N = 11;
    int n = 2;
    int i;
    double u1[N];
    for (i=0; i<N; i++) u1[i] = u[i] - alpha * gr[i];
    return smp1_JSum_5(t, x1, x2, n, u1, N);
}
