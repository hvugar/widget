#include "bealesurface.h"

BealeSurface::BealeSurface() : Q3DSurface()
{
    minX = -5.0f;
    maxX = +5.0f;
    minZ = -5.0f;
    maxZ = +5.0f;
    minY = 0.0f;
    maxY = 410000.0f;

    rotationX = 0.0;
    rotationY = 0.0;
    rotationZ = 0.0;

    countX = 100;
    countZ = 100;

    setAxisX(new QValue3DAxis);
    setAxisY(new QValue3DAxis);
    setAxisZ(new QValue3DAxis);

    m_Proxy = new QSurfaceDataProxy();

    m_Series = new QSurface3DSeries(m_Proxy);
    m_Series->setDrawMode(QSurface3DSeries::DrawSurface);
    m_Series->setFlatShadingEnabled(true);
    addSeries(m_Series);

    axisX()->setLabelFormat("X: %.2f");
    axisZ()->setLabelFormat("Z: %.2f");
    axisY()->setLabelFormat("Y: %.2f");

    axisX()->setRange(minX, maxX);
    axisY()->setRange(minY, maxY);
    axisZ()->setRange(minZ, maxZ);

    axisX()->setLabelAutoRotation(rotationX);
    axisY()->setLabelAutoRotation(rotationY);
    axisZ()->setLabelAutoRotation(rotationZ);

    QLinearGradient gr;
//    gr.setColorAt(0.0, Qt::darkBlue);
//    gr.setColorAt(0.1, Qt::blue);
//    gr.setColorAt(0.2, Qt::darkGreen);
//    gr.setColorAt(0.3, Qt::green);
//    gr.setColorAt(0.4, Qt::yellow);
//    gr.setColorAt(0.5, Qt::darkYellow);
//    gr.setColorAt(0.6, Qt::red);
//    gr.setColorAt(1.0, Qt::darkRed);

    QImage pixmap("spectra.png", "PNG");
    int w = pixmap.width();
    double h = 1.0 / (double)w;

    for (int i=0; i<w; i++)    {
        QRgb rgb = pixmap.pixel(w-i,1);
        gr.setColorAt(i*h, rgb);
    }

    m_Series->setBaseGradient(gr);
    m_Series->setColorStyle(Q3DTheme::ColorStyleRangeGradient);


    setReflection(false);
    setSelectionMode(QAbstract3DGraph::SelectionNone);
    setShadowQuality(QAbstract3DGraph::ShadowQualityNone);

    //activeTheme()->setGridEnabled(false);
    //activeTheme()->setBackgroundEnabled(false);
    //activeTheme()->setBackgroundColor(Qt::red);
    //activeTheme()->setLabelBorderEnabled(false);
    //activeTheme()->setLabelBackgroundEnabled(false);
    //activeTheme()->setLabelTextColor(Qt::white);
    //activeTheme()->setLabelBackgroundColor(Qt::white);
    //activeTheme()->setWindowColor(Qt::black);

    fillRosenbrockData();
}

BealeSurface::~BealeSurface()
{}

float BealeSurface::function(float x1, float x2)
{
    return  (1.5f - x1 + x1*x2)*(1.5f - x1 + x1*x2)
            + (2.25f - x1 + x1*x2*x2)*(2.25f-x1 + x1*x2*x2)
            + (2.625f - x1 + x1*x2*x2*x2)*(2.625f - x1 + x1*x2*x2*x2);
}

void BealeSurface::fillRosenbrockData()
{
    float stepX = (maxX - minX) / float(countX);
    float stepZ = (maxZ - minZ) / float(countZ);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(countZ+1);

    for (int i = 0 ; i <= countZ ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(countX+1);
        float z = qMin(maxZ, (i * stepZ + minZ));
        int index = 0;
        for (int j = 0; j <= countX; j++) {
            float x = qMin(maxX, (j * stepX + minX));
            float y = function(x, z);
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }
    m_Proxy->resetArray(dataArray);
}
