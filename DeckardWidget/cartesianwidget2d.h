#ifndef CARTESIANWIDGET2D_H
#define CARTESIANWIDGET2D_H

#include "cartesianwidget.h"

class Cartesian2DWidget : public CartesianWidget
{
    Q_OBJECT
public:
    explicit Cartesian2DWidget(QWidget *parent = 0);
    virtual ~Cartesian2DWidget();

    QList<FunctionConfig>& functions();
    QList<QLineF>& lines();
    QList<QPointF>& points();

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
    virtual void drawLines(QPainter& painter);
    virtual void drawPoints(QPainter& painter);

    virtual QPointF toDisplayPoint(double x, double y);
    virtual QPointF fromDisplayPoint(double x, double y);

protected:
    QList<FunctionConfig> mfunctions;
    QList<QPointF> mpoints;
    QList<QLineF> mlines;


signals:

public slots:

};

#endif // CARTESIANWIDGET2D_H
