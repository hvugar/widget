#ifndef CARTESIANWIDGET2D_2_H
#define CARTESIANWIDGET2D_2_H

#include "cartesianwidget.h"

class Cartesian2DWidget2 : public CartesianWidget
{
    Q_OBJECT
public:
    explicit Cartesian2DWidget2(QWidget *parent = 0);
    virtual ~Cartesian2DWidget2();

protected:
    virtual void resizeEvent(QResizeEvent*);
    virtual void paintEvent(QPaintEvent*);
    virtual void wheelEvent(QWheelEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

    virtual void drawGridLines(QPainter& painter);
    virtual void drawGridLabel(QPainter& painter);
    virtual void drawR1Graphic(QPainter& painter);
    virtual void drawLines(QPainter& painter);
    virtual void drawPoints(QPainter& painter);

    virtual QPointF toDisplayPoint(double x, double y);
    virtual QPointF fromDisplayPoint(double x, double y);

signals:

public slots:

};

#endif // CARTESIANWIDGET2D_2_H
