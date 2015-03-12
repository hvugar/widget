#include "cartesianwidget.h"

CartesianWidget::CartesianWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Base);
    leftButtonPressed = false;

    reset();
}

CartesianWidget::~CartesianWidget() { }

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
    update();
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
    update();
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
    update();
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
    emit zoomChanged(mzoom);
    update();
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

void CartesianWidget::calcBounds()
{
    int w = width();
    int h = height();

    mxmin = centerX() - (double)(w/2.0) / (double)scaleX();
    mxmax = centerX() + (double)(w/2.0) / (double)scaleX();
    mymin = centerY() - (double)(h/2.0) / (double)scaleY();
    mymax = centerY() + (double)(h/2.0) / (double)scaleY();
}

void CartesianWidget::addFunctionConfig(FunctionConfig fc)
{
    fcs.append(fc);
}

QString CartesianWidget::axisNumber(double number) const
{
    int precition = 15;
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
