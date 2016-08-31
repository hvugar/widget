#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QFile>
#include <QtGui/QLinearGradient>

/** QtDataVisualization **/
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtDataVisualization/Q3DCamera>

#include <vector2d.h>
#include <matrix2d.h>

using namespace QtDataVisualization;

class SurfaceGraph : public QObject
{
    Q_OBJECT
public:
    explicit SurfaceGraph(Q3DSurface *surface);
    virtual ~SurfaceGraph();

    void fillSqrtSinProxy();

    void loadMatrix(DoubleMatrix &m, unsigned k, unsigned int height, unsigned int width);

signals:

public slots:
    void timeout();

private:
    Q3DSurface *m_graph;
    QSurfaceDataProxy *m_sqrtSinProxy;
    QSurface3DSeries *m_sqrtSinSeries;

    double sampleMax;
    double sampleMin;

    int sampleCountX;
    int sampleCountZ;

    QTimer *timer;

    unsigned int k;


};

#endif // SURFACEGRAPH_H
