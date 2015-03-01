#ifndef CARTESIANWIDGET2_H
#define CARTESIANWIDGET2_H

#include "cartesianwidget.h"

class CartesianWidget2 : public CartesianWidget
{
    Q_OBJECT
public:
    explicit CartesianWidget2(QWidget *parent = 0);
    virtual ~CartesianWidget2();

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

signals:

public slots:

};

#endif // CARTESIANWIDGET2_H
