#include "mainwindow.h"
#include <math.h>
#include <string.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);

    statusBar = new QStatusBar;

    label1 = new QLabel;
    label2 = new QLabel;
    label3 = new QLabel;
    label4 = new QLabel;

    statusBar->addWidget(label1);
    statusBar->addWidget(label2);
    statusBar->addWidget(label3);
    setStatusBar(statusBar);

    toolBar = new QToolBar;
    addToolBar(toolBar);

    cartesianWidget = new CartesianWidget2;
    setCentralWidget(cartesianWidget);
    setWindowState(Qt::WindowMaximized);

    initFunction();

    connect(cartesianWidget, SIGNAL(centerChanged(double,double)), this, SLOT(cwCenterChanged(double,double)));
    connect(cartesianWidget, SIGNAL(offsetChanged(int,int)), this, SLOT(cwOffsetChanged(int,int)));
    connect(cartesianWidget, SIGNAL(scaleChanged(int,int)), this, SLOT(cwScaleChanged(int,int)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::initFunction()
{
    FunctionConfig fc1;
    fc1.f = sin;
    fc1.a = -2.5;
    fc1.b = +2.5;
    fc1.penColor = 0xff0000;
    cartesianWidget->addFunctionConfig(fc1);

//    FunctionConfig fc2;
//    fc2.f = f1;
//    fc2.a = -2.5;
//    fc2.b = +2.5;
//    fc2.penColor = 0x0000ff;
//    cartesianWidget->addFunctionConfig(fc2);

//    FunctionConfig fc3;
//    fc3.f = f2;
//    fc3.a = -10.5;
//    fc3.b = +10.5;
//    fc3.penColor = 0x0000ff;
//    cartesianWidget->addFunctionConfig(fc3);
}

void MainWindow::cwCenterChanged(double centerX, double centerY)
{
    label1->setText(QString("Center: (%1 %2)")
                    .arg(centerX, 6, 'f')
                    .arg(centerY, 6, 'f'));

    label2->setText(QString("Bounds: (%1 %2 %3 %4)")
                    .arg(cartesianWidget->xmin(), 6, 'f')
                    .arg(cartesianWidget->xmax(), 6, 'f')
                    .arg(cartesianWidget->ymin(), 6, 'f')
                    .arg(cartesianWidget->ymax(), 6, 'f'));
}

void MainWindow::cwOffsetChanged(int, int)
{}

void MainWindow::cwScaleChanged(int scaleX, int scaleY)
{
    label3->setText(QString("Scale: (%1 %2)").arg(scaleX).arg(scaleY));
}
