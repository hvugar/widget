#include "samplegradient.h"

SampleGradient::SampleGradient()
{
    setFunction(this);
    setGradient(this);
    setPrinter(this);
}

SampleGradient::~SampleGradient()
{}

double SampleGradient::fx(const DoubleVector &x)
{
    double x1 = x[0];
    double x2 = x[1];
    return ((1-x1)*(1-x1)) + 100*(x2-x1*x1)*(x2-x1*x1);
}

void SampleGradient::gradient(const DoubleVector &x, DoubleVector &g)
{
    IGradient::Gradient(this, 0.0001, x, g);
}

void SampleGradient::print(unsigned int iteration, const DoubleVector &x, const DoubleVector &gradient, double alpha, RnFunction *fn) const
{
    emit showCoordinares(x);
}
