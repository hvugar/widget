#include "cartesianwidget.h"

#define scale_min 80
#define scale_max 150
#define scale_stp 10

CartesianWidget::CartesianWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Base);
    leftButtonPressed = false;

    reset();
}

CartesianWidget::~CartesianWidget() { }

void CartesianWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    calcBounds();

    update();
}

int CartesianWidget::scaleX() const
{
    return m_scaleX;
}

void CartesianWidget::setScaleX(int scaleX)
{
    setScale(scaleX, m_scaleY);
}

int CartesianWidget::scaleY() const
{
    return m_scaleY;
}

void CartesianWidget::setScaleY(int scaleY)
{
    setScale(m_scaleX, scaleY);
}

void CartesianWidget::setScale(int scaleX, int scaleY)
{
    m_scaleX = scaleX;
    m_scaleY = scaleY;

    calcBounds();

    emit scaleChanged(m_scaleX, m_scaleY);
}

int CartesianWidget::offsetX() const
{
    return m_offsetX;
}

void CartesianWidget::setOffsetX(int offsetX)
{
    setOffset(offsetX, m_offsetY);
}

int CartesianWidget::offsetY() const
{
    return m_offsetY;
}

void CartesianWidget::setOffsetY(int offsetY)
{
    setOffset(m_offsetX, offsetY);
}

void CartesianWidget::setOffset(int offsetX, int offsetY)
{
    m_offsetX = offsetX;
    m_offsetY = offsetY;

    emit offsetChanged(m_offsetX, m_offsetY);
}

double CartesianWidget::centerX() const
{
    return mcenterX;
}

void CartesianWidget::setCenterX(double centerX)
{
    setCenter(centerX, mcenterY);
}

double CartesianWidget::centerY() const
{
    return mcenterY;
}

void CartesianWidget::setCenterY(double centerY)
{
    setCenter(mcenterX, centerY);
}

void CartesianWidget::setCenter(double centerX, double centerY)
{
    mcenterX = centerX;
    mcenterY = centerY;

    calcBounds();

    emit centerChanged(mcenterX, mcenterY);
}

double CartesianWidget::xmin() const
{
    return mxmin;
}

double CartesianWidget::xmax() const
{
    return mxmax;
}

double CartesianWidget::ymin() const
{
    return mymin;
}

double CartesianWidget::ymax() const
{
    return mymax;
}

double CartesianWidget::zoom() const
{
    return mzoom;
}

void CartesianWidget::setZoom(double zoom)
{
    mzoom = zoom;

    calcBounds();

    emit zoomChanged(mzoom);
}

void CartesianWidget::reset()
{
    setOffset(0, 0);
    setCenter(0.0, 0.0);
    setScale(100, 100);
    setZoom(1.0);

    level = Level1;

    update();
}

void CartesianWidget::zoomIn()
{
    int min = scale_min;
    int max = scale_max;
    int stp = scale_stp;

    if (zoom() > 0.00000001)
    {
        setScale(scaleX() + stp, scaleY() + stp);
        if (scaleX() > max)
        {
            setScale(min, min);
            switch (level)
            {
            case Level1: { setZoom(zoom()/2.0); level = Level2; } break;
            case Level2: { setZoom(zoom()/2.5); level = Level3; } break;
            case Level3: { setZoom(zoom()/2.0); level = Level1; } break;
            default: break;
            }
        }
    }
    update();
}

void CartesianWidget::zoomOut()
{
    int min = scale_min;
    int max = scale_max;
    int stp = scale_stp;

    setScale(scaleX() - stp, scaleY() - stp);
    if (scaleX() < min)
    {
        setScale(max, max);
        switch (level)
        {
        case Level1: { setZoom(zoom()*2.0); level = Level3; } break;
        case Level3: { setZoom(zoom()*2.5); level = Level2; } break;
        case Level2: { setZoom(zoom()*2.0); level = Level1; } break;
        default: break;
        }
    }
    update();
}

void CartesianWidget::calcBounds()
{
    int w = width();
    int h = height();

    mxmin = centerX() - (double)(w/2.0) / ((double)scaleX()/zoom());
    mxmax = centerX() + (double)(w/2.0) / ((double)scaleX()/zoom());
    mymin = centerY() - (double)(h/2.0) / ((double)scaleY()/zoom());
    mymax = centerY() + (double)(h/2.0) / ((double)scaleY()/zoom());

    emit boundsChanged(mxmin, mymin, mxmax, mymax);
}

void CartesianWidget::addFunctionConfig(FunctionConfig fc)
{
    fcs.append(fc);
}

QString CartesianWidget::axisNumber(double number) const
{
    int precition = 12;
    QString s = QString::number(number, 'f', precition);
    while(s.endsWith('0') )
    {
        s.chop(1);
        if (s.endsWith('.'))
        {
            s.chop(1);
            break;
        }
    }
    return s;
}
