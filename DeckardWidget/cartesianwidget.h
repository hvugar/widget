#ifndef CARTESIANWIDGET_H
#define CARTESIANWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QFontMetrics>
#include <QFontMetricsF>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QMouseEvent>

#include <math.h>
#include "functionconfig.h"

class CartesianWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CartesianWidget(QWidget *parent = 0);
    virtual ~CartesianWidget();

    // scale
    int scaleX() const;
    int scaleY() const;
    void setScaleX(int scaleX);
    void setScaleY(int scaleY);
    virtual void setScale(int scaleX, int scaleY);

    // offset
    int offsetX() const;
    int offsetY() const;
    void setOffsetX(int offsetX);
    void setOffsetY(int offsetY);
    virtual void setOffset(int offsetX, int offsetY);

    // center
    double centerX() const;
    double centerY() const;
    void setCenterX(double x);
    void setCenterY(double y);
    virtual void setCenter(double x, double y);

    double xmin() const;
    double xmax() const;
    double ymin() const;
    double ymax() const;

    // functions
    void setFunctionConfig(FunctionConfig fc);
    void addFunctionConfig(FunctionConfig fc);

protected:
    virtual void drawGridLines(QPainter& painter) = 0;
    virtual void drawGridLabel(QPainter& painter) = 0;
    virtual void drawR1Graphic(QPainter& painter) = 0;

    void calcBounds();

private:
    int m_scaleX;
    int m_scaleY;

    int m_offsetX;
    int m_offsetY;

    double mcenterX;
    double mcenterY;

    double mxmin;
    double mxmax;
    double mymin;
    double mymax;

protected:
    bool leftButtonPressed;
    bool rightButtonPressed;
    QPoint last;

    QList<FunctionConfig> fcs;
signals:
    void centerChanged(double centerX, double centerY);
    void scaleChanged(int scaleX, int scaleY);
    void offsetChanged(int offsetX, int offsetY);

public slots:

};

#endif // CARTESIANWIDGET_H
