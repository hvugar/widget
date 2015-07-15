#ifndef CARTESIANWIDGET2D1_H
#define CARTESIANWIDGET2D1_H

#include "cartesianwidget2d.h"

class Cartesian2DWidget1 : public Cartesian2DWidget
{
    Q_OBJECT
public:
    explicit Cartesian2DWidget1(QWidget *parent = 0);
    virtual ~Cartesian2DWidget1();

protected:
    virtual void resizeEvent(QResizeEvent*);
    virtual void paintEvent(QPaintEvent*);
    virtual void wheelEvent(QWheelEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

    virtual void drawGridLines(QPainter& painter);
    virtual void drawGridLabel(QPainter& painter);
    virtual void drawR1Function(QPainter& painter);

    virtual QPointF toDisplayPoint(double x, double y);
    virtual QPointF fromDisplayPoint(double x, double y);

signals:

public slots:

};

#endif // CARTESIANWIDGET2D1_H
