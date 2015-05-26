#ifndef SAMPLEGRADIENT_H
#define SAMPLEGRADIENT_H

#include <QObject>
#include <gradient.h>

class SampleGradient : public QObject, public Gradient
{
    Q_OBJECT

public:
    SampleGradient();
    virtual ~SampleGradient();

protected:
    virtual double fx(std::vector<double> x);
    virtual void iterationInfo();

public slots:

signals:
    void showCoordinares(const std::vector<double>& x);
};

#endif // SAMPLEGRADIENT_H
