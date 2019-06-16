#include "matrixsurface.h"

MatrixSurface::MatrixSurface()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));

    minX = +0.0f;
    maxX = +100.0f;
    minZ = +0.0f;
    maxZ = +100.0f;
    minY = -5.0f;
    maxY = +5.0;

    rotationX = 30.0f;
    rotationY = 90.0f;
    rotationZ = 30.0f;

    countX = 100;
    countZ = 100;

    setAxisX(new QValue3DAxis());
    setAxisY(new QValue3DAxis());
    setAxisZ(new QValue3DAxis());

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

    axisX()->setLabelAutoRotation(30.0f);
    axisY()->setLabelAutoRotation(90.0f);
    axisZ()->setLabelAutoRotation(30.0f);



    QLinearGradient gr;
    gr.setColorAt(0.0, 0x0000FF);
    gr.setColorAt(0.1, 0x0064FF);
    gr.setColorAt(0.2, 0x009FFF);
    gr.setColorAt(0.3, 0x00D1FF);
    gr.setColorAt(0.4, 0x01FFFF);
    gr.setColorAt(0.5, 0x01FF00);
    gr.setColorAt(0.6, 0xFFFF00);
    gr.setColorAt(0.7, 0xFFC700);
    gr.setColorAt(0.8, 0xFF7700);
    gr.setColorAt(0.9, 0xFF0000);
    gr.setColorAt(1.0, Qt::darkRed);

//    gr.setColorAt(0.0, Qt::darkBlue);
//    gr.setColorAt(0.1, Qt::blue);
//    gr.setColorAt(0.2, Qt::darkGreen);
//    gr.setColorAt(0.3, Qt::green);
//    gr.setColorAt(0.4, Qt::yellow);
//    gr.setColorAt(0.5, Qt::darkYellow);
//    gr.setColorAt(0.6, 0xFFC700);
//    gr.setColorAt(0.7, 0xFF7700);
//    gr.setColorAt(1.0, Qt::darkRed);

    //QImage pixmap("heat_spectra.JPG", "JPG");
    //int w = pixmap.width();
    //double h = 1.0 / (double)w;

    //for (int i=0; i<w; i++)
    //{
    //    QColor c = pixmap.pixelColor(i,1);
    //    gr.setColorAt(i*h, c);
    //}

    m_Series->setBaseGradient(gr);
    m_Series->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

    setReflection(true);
    setSelectionMode(QAbstract3DGraph::SelectionNone);
    setShadowQuality(QAbstract3DGraph::ShadowQualityNone);

    scene()->activeCamera()->setXRotation(45.0f);
    scene()->activeCamera()->setYRotation(15.0f);
    scene()->activeCamera()->setZoomLevel(75.0f);

    //activeTheme()->setGridEnabled(false);
    //activeTheme()->setBackgroundEnabled(false);
    //activeTheme()->setBackgroundColor(Qt::red);
    //activeTheme()->setLabelBorderEnabled(false);
    //activeTheme()->setLabelBackgroundEnabled(false);
    //activeTheme()->setLabelTextColor(Qt::white);
    //activeTheme()->setLabelBackgroundColor(Qt::white);
    //activeTheme()->setWindowColor(Qt::black);

    QString filename = "d:/data.txt";
    //fillMatrix(filename);
    timer.setInterval( 10 );
    timer.start();
}

MatrixSurface::~MatrixSurface() {}

void MatrixSurface::fillMatrix(const QString filename)
{
    DoubleMatrix m(101, 101);

    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

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
//                if (u<=minimum) minimum = u;
//                if (u>=maximum) maximum = u;
                i++;
            }
        }
        line = in.readLine();
        j++;
    }
    file.close();


    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(countZ+1);

    for (int i = 0 ; i <= countZ ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(countX+1);
        float z = i;
        int index = 0;
        for (int j = 0; j <= countX; j++) {
            float x = static_cast<float>(j);
            float y = static_cast<float>(m.at(static_cast<unsigned int>(i), static_cast<unsigned int>(j)));
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }
    m_Proxy->resetArray(dataArray);

    qDebug() << counter;
}

void MatrixSurface::timeout()
{
    QString filename = QString("E:/project/hvugar/num_methods/trunk/"
                               "optimal/bin/data/problem0H/f/txt/f_%1.txt").arg(counter, 4, 10, QChar('0'));
    fillMatrix(filename);
    counter++;
}
