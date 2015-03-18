#ifndef CARTESIANWIDGET2_H
#define CARTESIANWIDGET2_H

#include "cartesianwidget.h"

class Cartesian2DWidget : public CartesianWidget
{
    Q_OBJECT
public:
    explicit Cartesian2DWidget(QWidget *parent = 0);
    virtual ~Cartesian2DWidget();

    virtual void setXRange(double a, double b);

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

    virtual QPoint toDisplayPoint(double x, double y);
    virtual QPointF fromDisplayPoint(int x, int y);

signals:

public slots:

};

#endif // CARTESIANWIDGET2_H
