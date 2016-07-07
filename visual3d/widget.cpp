#include "widget.h"

Widget::Widget(Q3DSurface *graph, QWidget *parent) : QWidget(parent), mgraph(graph)
{
    minX = minZ = -1.3;
    maxX = maxZ = +1.3;
    minY = 0.0;
    maxY = 400.0;

    countX = 100;
    countZ = 100;
    countY = 100;

    resize(800, 600);

    if (graph != NULL)
        container = QWidget::createWindowContainer(graph);

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(container);
    setLayout(layout1);

    graph->setAxisX(new QValue3DAxis);
    graph->setAxisY(new QValue3DAxis);
    graph->setAxisZ(new QValue3DAxis);

    graph->axisX()->setLabelFormat("%.2f");
    graph->axisZ()->setLabelFormat("%.2f");
    graph->axisX()->setRange(minX, maxX);
    graph->axisY()->setRange(minY, maxY);
    graph->axisZ()->setRange(minZ, maxZ);
    graph->axisX()->setLabelAutoRotation(30);
    graph->axisY()->setLabelAutoRotation(90);
    graph->axisZ()->setLabelAutoRotation(30);

    graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);

    fillRosenbrockData();

    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::darkBlue);
    gr.setColorAt(0.1, Qt::blue);
    gr.setColorAt(0.2, Qt::darkGreen);
    gr.setColorAt(0.3, Qt::green);
    gr.setColorAt(0.4, Qt::yellow);
    gr.setColorAt(0.5, Qt::darkYellow);
    gr.setColorAt(0.6, Qt::red);
    gr.setColorAt(1.0, Qt::darkRed);

    graph->seriesList().at(0)->setBaseGradient(gr);
    graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

    graph->setReflection(false);
    graph->setSelectionMode(QAbstract3DGraph::SelectionNone);

    graph->activeTheme()->setGridEnabled(false);
//    graph->activeTheme()->setBackgroundEnabled(false);
    graph->activeTheme()->setBackgroundColor(Qt::red);
    graph->activeTheme()->setLabelBorderEnabled(false);
    graph->activeTheme()->setLabelBackgroundEnabled(false);
    graph->activeTheme()->setLabelTextColor(Qt::white);
    graph->activeTheme()->setLabelBackgroundColor(Qt::white);
    graph->activeTheme()->setWindowColor(Qt::black);
}

Widget::~Widget()
{
    delete mgraph;
    delete container;
}

void Widget::fillRosenbrockData()
{
    m_rosenbrockProxy = new QSurfaceDataProxy();
    m_rosenbrockSeries = new QSurface3DSeries(m_rosenbrockProxy);

    m_rosenbrockSeries->setDrawMode(QSurface3DSeries::DrawSurface);
    m_rosenbrockSeries->setFlatShadingEnabled(true);

    mgraph->addSeries(m_rosenbrockSeries);

    float stepX = (maxX - minX) / float(countX);
    float stepZ = (maxZ - minZ) / float(countZ);
    //float stepY = (maxY - minY) / float(countY);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(countZ+1);

    for (int i = 0 ; i <= countZ ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(countX+1);
        float z = qMin(maxZ, (i * stepZ + minZ));
        int index = 0;
        for (int j = 0; j <= countX; j++) {
            float x = qMin(maxX, (j * stepX + minX));
            float y = rosenbrock(x, z);
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }
    m_rosenbrockProxy->resetArray(dataArray);
}

float Widget::rosenbrock(float x, float z)
{
    return (1.0f-x*x)*(1.0f-x*x)+100.0f*(z-x*x)*(z-x*x);
}
