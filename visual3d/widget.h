#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>

#include <QtDataVisualization>

using namespace QtDataVisualization;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(Q3DSurface *graph, QWidget *parent = 0);
    ~Widget();

private:
    Q3DSurface *mgraph;
    Q3DCamera  *mcamera;

    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;
    QWidget *container;

    int countX;
    int countZ;
    int countY;

    void fillRosenbrockData();

    QSurfaceDataProxy *m_rosenbrockProxy;
    QSurface3DSeries *m_rosenbrockSeries;

    float rosenbrock(float x, float z);
};

#endif // WIDGET_H
