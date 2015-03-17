#include "mainwindow.h"
#include <math.h>
#include <string.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //resize(800, 600);

    statusBar = new QStatusBar;

    label1 = new QLabel;
    label2 = new QLabel;
    label3 = new QLabel;
    label4 = new QLabel;

    toolButton1 = new QToolButton;
    toolButton2 = new QToolButton;
    toolButton3 = new QToolButton;
    toolBar = new QToolBar;
    addToolBar(toolBar);

    statusBar->addWidget(label1);
    statusBar->addWidget(label2);
    statusBar->addWidget(label3);
    statusBar->addWidget(label4);

    setStatusBar(statusBar);

    cartesianWidget = new Cartesian2DWidget1;
    cartesianWidget->resize(800, 600);
    cartesianWidget->setMinimumSize(800, 600);
    setCentralWidget(cartesianWidget);
    //setWindowState(Qt::WindowMaximized);

    toolBar->addAction("R", cartesianWidget, SLOT(reset()));
    toolBar->addAction("+", this, SLOT(cwZoomIn()));
    toolBar->addAction("-", this, SLOT(cwZoomOut()));
    toolBar->addAction("S", this, SLOT(showSettingDialog()));


    initFunction();

    connect(cartesianWidget, SIGNAL(centerChanged(double,double)), this, SLOT(cwCenterChanged(double,double)));
    connect(cartesianWidget, SIGNAL(offsetChanged(int,int)), this, SLOT(cwOffsetChanged(int,int)));
    connect(cartesianWidget, SIGNAL(scaleChanged(int,int)), this, SLOT(cwScaleChanged(int,int)));
    connect(cartesianWidget, SIGNAL(zoomChanged(double)), this, SLOT(cwZoomChanged(double)));
    connect(cartesianWidget, SIGNAL(boundsChanged(double,double,double,double)), this, SLOT(cwBoundsChanged(double,double,double,double)));

    cartesianWidget->reset();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initFunction()
{
    FunctionConfig fc1;
    fc1.f = f5;
    fc1.a = -10.5;
    fc1.b = +10.5;
    fc1.penColor = 0xff0000;
    cartesianWidget->addFunctionConfig(fc1);

    FunctionConfig fc2;
    fc2.f = f1;
    fc2.a = -2.5;
    fc2.b = +2.5;
    fc2.penColor = 0x0000ff;
    cartesianWidget->addFunctionConfig(fc2);

    FunctionConfig fc3;
    fc3.f = f2;
    fc3.a = -1.5;
    fc3.b = +2.5;
    fc3.penColor = 0x0000ff;
    cartesianWidget->addFunctionConfig(fc3);
}

void MainWindow::cwCenterChanged(double centerX, double centerY)
{
    label1->setText(QString("Center: (%1 %2)")
                    .arg(centerX, 6, 'f')
                    .arg(centerY, 6, 'f'));
}

void MainWindow::cwOffsetChanged(int, int)
{}

void MainWindow::cwScaleChanged(int scaleX, int scaleY)
{
    label3->setText(QString("Scale: (%1 %2)").arg(scaleX).arg(scaleY));
}

void MainWindow::cwZoomChanged(double zoom)
{
    label4->setText(QString("Zoom: %1").arg(zoom, 8, 'f'));
}

void MainWindow::cwBoundsChanged(double xmin, double ymin, double xmax, double ymax)
{
    label2->setText(QString("Bounds: (%1 %2 %3 %4)").arg(xmin, 6, 'f').arg(xmax, 6, 'f').arg(ymin, 6, 'f').arg(ymax, 6, 'f'));
}

void MainWindow::cwZoomIn()
{
    for (int i=0; i<8; i++)
    {
        QTimer* timer = new QTimer();
        connect(timer, SIGNAL(timeout()), cartesianWidget, SLOT(zoomIn()));
        //connect(timer, SIGNAL(timeout()), this, SLOT(deleteLater()));
        timer->setInterval(20*(8-i));
        timer->setSingleShot(true);
        timer->start();
    }
}

void MainWindow::cwZoomOut()
{
    for (int i=0; i<8; i++)
    {
        QTimer* timer = new QTimer();
        connect(timer, SIGNAL(timeout()), cartesianWidget, SLOT(zoomOut()));
        //connect(timer, SIGNAL(timeout()), this, SLOT(deleteLater()));
        timer->setInterval(20*(8-i));
        timer->setSingleShot(true);
        timer->start();
    }
}

void MainWindow::showSettingDialog()
{
    SettingWidget* sw = new SettingWidget(this);
    sw->setCenter(cartesianWidget->centerX(), cartesianWidget->centerY());
    sw->setXRange(cartesianWidget->xmin(), cartesianWidget->xmax());

    sw->exec();

    QPointF c = sw->center();
    QPointF r = sw->xrange();

    cartesianWidget->setCenter(c.x(), c.y());
    //cartesianWidget->setXRange(r.x(), r.y());
    cartesianWidget->update();
}
