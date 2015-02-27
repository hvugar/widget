#ifndef CARTESIANWIDGET_H
#define CARTESIANWIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPainter>
#include "functionconfig.h"

class CartesianWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CartesianWidget(QWidget *parent = 0);
    virtual ~CartesianWidget();

    // scale
    int scaleX() const;
    int scaleY() const;
    void setScaleX(int scaleX);
    void setScaleY(int scaleY);
    void setScale(int scaleX, int scaleY);

    void setFunctionConfig(FunctionConfig fc);
    void addFunctionConfig(FunctionConfig fc);

protected:
    virtual void resizeEvent(QResizeEvent*);
    virtual void paintEvent(QPaintEvent*);
    virtual void wheelEvent(QWheelEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

    virtual void drawFunction(R1Function f, QPainter& painter);

private:
    int m_scaleX;
    int m_scaleY;

    int m_offsetX;
    int m_offsetY;

    bool leftButtonPressed;
    bool rightButtonPressed;
    QPoint last;

    QList<FunctionConfig> fcs;
signals:

public slots:

};

#endif // CARTESIANWIDGET_H
