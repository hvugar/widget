#ifndef BOOTHSURFACE_H
#define BOOTHSURFACE_H

/** QWidget **/
#include <QWidget>
#include <QHBoxLayout>

#include <QLinearGradient>

/** QtDataVisualization **/
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtDataVisualization/Q3DCamera>

using namespace QtDataVisualization;

class BoothSurface : public Q3DSurface
{
public:
    BoothSurface();
    virtual ~BoothSurface();

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

#endif // BOOTHSURFACE_H
