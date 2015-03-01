#ifndef CARTESIANWIDGET0_H
#define CARTESIANWIDGET0_H

#include "cartesianwidget.h"

class CartesianWidget0 : public CartesianWidget
{
    Q_OBJECT
public:
    explicit CartesianWidget0(QWidget *parent = 0);
    virtual ~CartesianWidget0();

protected:
    virtual void resizeEvent(QResizeEvent*);
    virtual void paintEvent(QPaintEvent*);
    virtual void wheelEvent(QWheelEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

    virtual void drawFunction(R1Function f, QPainter& painter);

    virtual void drawGridLines(QPainter&) {}
    virtual void drawGridLabel(QPainter&) {}
    virtual void drawR1Graphic(QPainter&) {}

    virtual void setScale(int, int);

signals:

public slots:

};

#endif // CARTESIANWIDGET0_H
