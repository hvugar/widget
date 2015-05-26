#include "samplegradient.h"

SampleGradient::SampleGradient()
{
}

SampleGradient::~SampleGradient()
{}

double SampleGradient::fx(std::vector<double> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return ((1-x1)*(1-x1)) + 100*(x2-x1*x1)*(x2-x1*x1);
}

void SampleGradient::iterationInfo()
{
    emit showCoordinares(x());
}
