#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <math.h>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    virtual void paintEvent(QPaintEvent *evt);

    void image1(QPaintEvent *evt);
    void image2(QPaintEvent *evt);
    void image3(QPaintEvent *evt);
    void image4(QPaintEvent *evt);
    void image5(QPaintEvent *evt);

    void drawGraph11(QPainter &painter);
    void drawGraph12(QPainter &painter);
    void drawGraph13(QPainter &painter);
    void drawGraph14(QPainter &painter);
    void drawGraph15(QPainter &painter);
    void drawGraph16(QPainter &painter);
    void drawGraph17(QPainter &painter);
    void drawGraph18(QPainter &painter);
    void drawGraph19(QPainter &painter);

    QPixmap pixmap;
};

#endif // WIDGET_H
