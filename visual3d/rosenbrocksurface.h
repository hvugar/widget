#ifndef ROSENBROCKSURFACE_H
#define ROSENBROCKSURFACE_H

/** QWidget **/
#include <QWidget>
#include <QHBoxLayout>
#include <QRgb>

#include <QLinearGradient>

/** QtDataVisualization **/
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtDataVisualization/Q3DCamera>

using namespace QtDataVisualization;

class RosenbrockSurface : public Q3DSurface
{
public:
    RosenbrockSurface();
    virtual ~RosenbrockSurface();

    float function(float x1, float x2);

    QSurfaceDataProxy *m_Proxy;
    QSurface3DSeries *m_Series;

    float minX;
    float maxX;
    float minZ;
    float maxZ;
    float minY;
    float maxY;

    float rotationX;
    float rotationZ;
    float rotationY;

    int countX;
    int countZ;

private:
    void fillRosenbrockData();
};

#endif // ROSENBROCKSURFACE_H
