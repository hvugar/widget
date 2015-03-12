#ifndef CARTESIANWIDGET_H
#define CARTESIANWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QFontMetrics>
#include <QFontMetricsF>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QMouseEvent>

#include <math.h>
#include "functionconfig.h"

typedef enum { Level1, Level2, Level3 } Levels;

class CartesianWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CartesianWidget(QWidget *parent = 0);
    virtual ~CartesianWidget();

    // scale
    int scaleX() const;
    void setScaleX(int scaleX);
    int scaleY() const;
    void setScaleY(int scaleY);
    virtual void setScale(int scaleX, int scaleY);

    // offset
    int offsetX() const;
    void setOffsetX(int offsetX);
    int offsetY() const;
    void setOffsetY(int offsetY);
    virtual void setOffset(int offsetX, int offsetY);

    // center
    double centerX() const;
    void setCenterX(double centerX);
    double centerY() const;
    void setCenterY(double centerY);
    virtual void setCenter(double x, double y);

    // bounds
    double xmin() const;
    double xmax() const;
    double ymin() const;
    double ymax() const;

    // zoom
    double zoom() const;
    void setZoom(double zoom);

    // functions
    void setFunctionConfig(FunctionConfig fc);
    void addFunctionConfig(FunctionConfig fc);

protected:
    virtual void drawGridLines(QPainter& painter) = 0;
    virtual void drawGridLabel(QPainter& painter) = 0;
    virtual void drawR1Graphic(QPainter& painter) = 0;

    QString axisNumber(double) const;

    void calcBounds();

    double mxmin;
    double mxmax;
    double mymin;
    double mymax;
    double mzoom;

    bool leftButtonPressed;
    bool rightButtonPressed;
    QPoint last;

    QList<FunctionConfig> fcs;
    Levels level;


private:
    int m_scaleX;
    int m_scaleY;

    int m_offsetX;
    int m_offsetY;

    double mcenterX;
    double mcenterY;

signals:
    void centerChanged(double centerX, double centerY);
    void scaleChanged(int scaleX, int scaleY);
    void offsetChanged(int offsetX, int offsetY);
    void zoomChanged(double zoom);

public slots:
    void reset();
};

#endif // CARTESIANWIDGET_H
