#include "rosenbrocksurface.h"

RosenbrockSurface::RosenbrockSurface() : Q3DSurface()
{
    minX = -1.5f;
    maxX = +1.5f;
    minZ = -1.5f;
    maxZ = +1.5f;
    minY = 0.0f;
    maxY = 1400.0f;

    rotationX = 30.0f;
    rotationY = 90.0f;
    rotationZ = 30.0f;

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

    axisX()->setLabelFormat("x: %.2f");
    axisZ()->setLabelFormat("z: %.2f");
    axisY()->setLabelFormat("y: %.2f");
    axisX()->setRange(minX, maxX);
    axisY()->setRange(minY, maxY);
    axisZ()->setRange(minZ, maxZ);

    axisX()->setLabelAutoRotation(rotationX);
    axisY()->setLabelAutoRotation(rotationY);
    axisZ()->setLabelAutoRotation(rotationZ);

    QLinearGradient gr;
//    gr.setColorAt(0.0, 0x0000FF);
//    gr.setColorAt(0.1, 0x0064FF);
//    gr.setColorAt(0.2, 0x009FFF);
//    gr.setColorAt(0.3, 0x00D1FF);
//    gr.setColorAt(0.4, 0x01FFFF);
//    gr.setColorAt(0.5, 0x01FF00);
//    gr.setColorAt(0.6, 0xFFFF00);
//    gr.setColorAt(0.7, 0xFFC700);
//    gr.setColorAt(0.8, 0xFF7700);
//    gr.setColorAt(0.9, 0xFF0000);
//    gr.setColorAt(1.0, Qt::darkRed);

//    gr.setColorAt(0.0, Qt::darkBlue);
//    gr.setColorAt(0.1, Qt::blue);
//    gr.setColorAt(0.2, Qt::darkGreen);
//    gr.setColorAt(0.3, Qt::green);
//    gr.setColorAt(0.4, Qt::yellow);
//    gr.setColorAt(0.5, Qt::darkYellow);
//    gr.setColorAt(0.6, 0xFFC700);
//    gr.setColorAt(0.7, 0xFF7700);
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

RosenbrockSurface::~RosenbrockSurface()
{}

float RosenbrockSurface::function(float x, float z)
{
    return (1.0f-x*x)*(1.0f-x*x)+100.0f*(z-x*x)*(z-x*x);
}

void RosenbrockSurface::fillRosenbrockData()
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
