#include "surfacegraph.h"

SurfaceGraph::SurfaceGraph(Q3DSurface* surface) : m_graph(surface)
{
    sampleCountX = 50;
    sampleCountZ = 50;

    sampleMin = +0.0;
    sampleMax = +1.0;

    k = 0;

    m_graph->setAxisX(new QValue3DAxis);
    m_graph->setAxisY(new QValue3DAxis);
    m_graph->setAxisZ(new QValue3DAxis);

    m_sqrtSinProxy = new QSurfaceDataProxy();
    m_sqrtSinSeries = new QSurface3DSeries(m_sqrtSinProxy);

    m_sqrtSinSeries->setDrawMode(QSurface3DSeries::DrawSurface);
    m_sqrtSinSeries->setFlatShadingEnabled(true);

    m_graph->axisX()->setLabelFormat("%.2f");
    m_graph->axisZ()->setLabelFormat("%.2f");
    m_graph->axisX()->setRange(sampleMin, sampleMax);
    m_graph->axisY()->setRange(-1.0f, +1.0f);
    m_graph->axisZ()->setRange(sampleMin, sampleMax);
    m_graph->axisX()->setLabelAutoRotation(30);
    m_graph->axisY()->setLabelAutoRotation(90);
    m_graph->axisZ()->setLabelAutoRotation(30);

    m_graph->addSeries(m_sqrtSinSeries);

    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);

    fillSqrtSinProxy();

    //    m_rangeMinX = sampleMin;
    //    m_rangeMinZ = sampleMin;
    //    m_stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    //    m_stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    //    m_axisMinSliderX->setMaximum(sampleCountX - 2);
    //    m_axisMinSliderX->setValue(0);
    //    m_axisMaxSliderX->setMaximum(sampleCountX - 1);
    //    m_axisMaxSliderX->setValue(sampleCountX - 1);
    //    m_axisMinSliderZ->setMaximum(sampleCountZ - 2);
    //    m_axisMinSliderZ->setValue(0);
    //    m_axisMaxSliderZ->setMaximum(sampleCountZ - 1);
    //    m_axisMaxSliderZ->setValue(sampleCountZ - 1);

    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::darkBlue);
    gr.setColorAt(0.1, Qt::blue);
    gr.setColorAt(0.2, Qt::darkGreen);
    gr.setColorAt(0.3, Qt::green);
    gr.setColorAt(0.4, Qt::yellow);
    gr.setColorAt(0.5, Qt::darkYellow);
    gr.setColorAt(0.6, Qt::red);
    gr.setColorAt(1.0, Qt::darkRed);

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

    m_graph->setReflection(false);
    m_graph->setSelectionMode(QAbstract3DGraph::SelectionNone);
    //    m_graph->setPolar(true);

    m_graph->axisX()->setTitleVisible(false);

    Q3DCamera *camera = m_graph->scene()->activeCamera();
    camera->setXRotation(45.0f+90.0f);
    //    camera->setYRotation(30.0);

    m_graph->activeTheme()->setGridEnabled(false);
    m_graph->activeTheme()->setBackgroundEnabled(false);
    m_graph->activeTheme()->setLabelBorderEnabled(false);
    m_graph->activeTheme()->setLabelBackgroundEnabled(false);
    m_graph->activeTheme()->setLabelTextColor(Qt::white);
    m_graph->activeTheme()->setLabelBackgroundColor(Qt::white);


    timer = new QTimer;
    timer->setInterval(100);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start();
}

SurfaceGraph::~SurfaceGraph()
{
    delete m_graph;
}

void SurfaceGraph::fillSqrtSinProxy()
{
    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;

    dataArray->reserve(sampleCountZ);
    for (int i = 0 ; i < sampleCountZ ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
        // Keep values within range bounds, since just adding step can cause minor drift due
        // to the rounding errors.
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            //float R = qSqrt(z * z + x * x) + 0.01f;
            float y = (1.0f-x)*(1.0f-x)+100.0f*(z-x*x)*(z-x*x);//(qSin(R) / R + 0.24f) * 1.61f;
            (*newRow)[index++].setPosition(QVector3D(x, y*0.2, z));
        }
        *dataArray << newRow;
    }

    m_sqrtSinProxy->resetArray(dataArray);
}

void SurfaceGraph::timeout()
{
    DoubleMatrix m;
    loadMatrix(m, k, 201, 201);
    k+=10;

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(201);
    for (int i = 0 ; i < 201 ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(201);
        float z = qMin(1.0, (i * 0.005));
        int index = 0;
        for (int j = 0; j < 201; j++) {
            float x = qMin(1.0, (j * 0.005));
            float y = m[i][j];
            (*newRow)[index++].setPosition(QVector3D(x, y*3, z));
        }
        *dataArray << newRow;
    }
    m_sqrtSinProxy->resetArray(dataArray);

    //Q3DCamera *camera = m_graph->scene()->activeCamera();
    //float rotateX = camera->xRotation();
    //camera->setXRotation(++rotateX);
    //camera->setYRotation(30.0);
}

void SurfaceGraph::loadMatrix(DoubleMatrix &m, unsigned k, unsigned int height, unsigned int width)
{
    QString inFile;
    if (k < 10000) inFile = QString("0000%1").arg(k);
    if (k < 1000) inFile = QString("00000%1").arg(k);
    if (k < 100) inFile = QString("000000%1").arg(k);
    if (k < 10) inFile = QString("0000000%1").arg(k);

    QFile file("E:/project/hvugar/num_methods/trunk/optimal/bin/data/"+inFile+".txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    double maximum = -9999.9;
    double minimum = +9999.9;

    m.resize(height, width);

    unsigned int j=0;
    QString line = in.readLine();
    while (!line.isNull() && !line.isEmpty())
    {
        unsigned int i=0;
        QStringList list = line.split(" ");
        for (int k=0; k<list.size(); k++)
        {
            QString str = list[k];
            if (!str.isNull() && !str.isEmpty())
            {
                double u = str.toDouble();
                m[j][i] = u;
                if (u<=minimum) minimum = u;
                if (u>=maximum) maximum = u;
                i++;
            }
        }
        line = in.readLine();
        j++;
    }
    file.close();
}

