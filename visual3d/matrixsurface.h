#ifndef MATRIXSURFACE_H
#define MATRIXSURFACE_H

/** QWidget **/
#include <QWidget>
#include <QHBoxLayout>
#include <QRgb>

#include <QLinearGradient>
#include <QTimer>

/** QtDataVisualization **/
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtDataVisualization/Q3DCamera>

#include <matrix2d.h>

using namespace QtDataVisualization;

class MatrixSurface  : public Q3DSurface
{
    Q_OBJECT
public:
    MatrixSurface();
    virtual ~MatrixSurface();

    QSurfaceDataProxy *m_Proxy;
    QSurface3DSeries  *m_Series;

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

    unsigned int counter = 0;

private:
    void fillMatrix(const QString filename = QString::null);
    QTimer timer;

public slots:
    void timeout();
};

#endif // MATRIXSURFACE_H
