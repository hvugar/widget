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
        double fj = (x1[j]-t[j]*t[j]*t[j])*(x1[j]-t[j]*t[j]*t[j]) + (x2[j] - t[j])*(x2[j] - t[j]) + (2*u[j] - t[j])*(2*u[j] - t[j]);
        double fi = (x1[i]-t[i]*t[i]*t[i])*(x1[i]-t[i]*t[i]*t[i]) + (x2[i] - t[i])*(x2[i] - t[i]) + (2*u[i] - t[i])*(2*u[i] - t[i]);
        sum = sum + 0.5 * (fj+fi) * (t[j]-t[i]);
    }
    sum = sum + (x2[N-1] - 1.0) * (x2[N-1] - 1.0);
    return sum;
}

double argmin(double alpha)
{
    double t[] =   { +0.00000000,  +0.10000000,  +0.20000000,  +0.30000000,  +0.40000000,  +0.50000000,  +0.60000000,  +0.70000000,  +0.80000000,  +0.90000000,  +1.00000000};

    double u[] =    { +0.01670172,  +0.06586119,  +0.11308640,  +0.15951677,  +0.20586228,  +0.25251534,  +0.29968098,  +0.34750206,  +0.39618774,  +0.44617800,  +0.49840072};
    double x1[] =   { +0.00000000,  +0.00093703,  +0.00749392,  +0.02531436,  +0.06009471,  +0.11756743,  +0.20345073,  +0.32337257,  +0.48276456,  +0.68670509,  +0.93966667};
    double x2[] =   { +0.00000000,  +0.09678421,  +0.19359793,  +0.29067230,  +0.38803196,  +0.48555848,  +0.58303076,  +0.68013604,  +0.77644632,  +0.87134907,  +0.96390715};
    double p1[] =   { +0.29993526,  +0.24607083,  +0.19869133,  +0.15798963,  +0.12365195,  +0.09501053,  +0.07116116,  +0.05103725,  +0.03343377,  +0.01697352,  +0.00000000};
    double p2[] =   { +0.56881471,  +0.50706418,  +0.43980277,  +0.37223406,  +0.30800796,  +0.24947514,  +0.19798556,  +0.15420402,  +0.11842776,  +0.09090692,  +0.07218570};
    double gr[] =   { -1.27124319,  -1.14101785,  -0.98429669,  -0.82060227,  -0.66291415,  -0.51907298,  -0.39341895,  -0.28842454,  -0.20635741,  -0.15123782,  -0.13157715};
    double s1[] =   { +0.09443288,  +0.09683570,  +0.07415462,  +0.03990695,  +0.00288871,  -0.03168210,  -0.06068845,  -0.08167524,  -0.09141876,  -0.08415708,  -0.04883938};

    int N = 11;
    int n = 2;
    int i;
    double u1[N];
    for (i=0; i<N; i++) u1[i] = u[i] - alpha * s1[i];
    return smp1_JSum_5(t, x1, x2, n, u1, N);
}
