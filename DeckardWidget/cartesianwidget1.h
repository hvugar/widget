#ifndef CARTESIANWIDGET1_H
#define CARTESIANWIDGET1_H

#include "cartesianwidget.h"

class CartesianWidget1 : public CartesianWidget
{
    Q_OBJECT
public:
    explicit CartesianWidget1(QWidget *parent = 0);
    virtual ~CartesianWidget1();

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

private:
    double zoom;

signals:

public slots:

};

#endif // CARTESIANWIDGET1_H
