#ifndef SAMPLEGRADIENT_H
#define SAMPLEGRADIENT_H

#include <QObject>
#include <function.h>
#include <gradient_cjt.h>
#include <printer.h>

class SampleGradient : public QObject, public RnFunction, public IGradient, public IPrinter, public ConjugateGradient
{
    Q_OBJECT

public:
    SampleGradient();
    virtual ~SampleGradient();

protected:
    virtual double fx(const DoubleVector &x) const;
    virtual void gradient(const DoubleVector &x, DoubleVector &g);
    virtual void print(unsigned int iteration, const DoubleVector &x, const DoubleVector &g,
                       double f, GradientMethod::MethodResult result) const;


public slots:

signals:
    void showCoordinares(const DoubleVector &x) const;
};

#endif // SAMPLEGRADIENT_H
