#ifndef CARTESIANWIDGET_H
#define CARTESIANWIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPainter>

typedef double(*R1Function)(double x);
typedef double(*RnFunction)(double* x, int size);

class CartesianWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CartesianWidget(QWidget *parent = 0);

    void setScale(int scale);
    int scale();

protected:
    virtual void resizeEvent(QResizeEvent*);
    virtual void paintEvent(QPaintEvent*);
    virtual void wheelEvent(QWheelEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

    void drawFunction(R1Function f, QPainter& painter);

private:
    int m_scale;
    int offsetX;
    int offsetY;
    bool pressed;
    QPoint last;

signals:

public slots:

};

#endif // CARTESIANWIDGET_H
