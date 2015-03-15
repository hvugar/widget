#ifndef CARTESIANWIDGET2_H
#define CARTESIANWIDGET2_H

#include "cartesianwidget.h"

class Cartesian2DWidget : public CartesianWidget
{
    Q_OBJECT
public:
    explicit Cartesian2DWidget(QWidget *parent = 0);
    virtual ~Cartesian2DWidget();

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
