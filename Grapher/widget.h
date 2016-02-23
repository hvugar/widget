#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

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

    bool ok;
};

#endif // WIDGET_H
