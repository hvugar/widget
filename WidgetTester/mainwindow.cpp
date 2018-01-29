#include "mainwindow.h"
#include <math.h>
#include <string.h>
#include <QDebug>
#include <QDockWidget>

MainWindow* MainWindow::mw = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    MainWindow::mw = this;

    //resize(800, 600);
    cartesianWidget = new Cartesian2DWidget;
    cartesianWidget->resize(800, 600);
    cartesianWidget->setMinimumSize(800, 600);
    setCentralWidget(cartesianWidget);
    setWindowState(Qt::WindowMaximized);

    createMenus();
    createToolBars();
    createDockWidgets();
    createStatusBar();

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

void MainWindow::createMenus()
{}

void MainWindow::createToolBars()
{
    toolButton1 = new QToolButton;
    toolButton2 = new QToolButton;
    toolButton3 = new QToolButton;
    toolBar = new QToolBar;
    addToolBar(toolBar);
    toolBar->addAction("R", cartesianWidget, SLOT(reset()));
    toolBar->addAction("+", this, SLOT(cwZoomIn()));
    toolBar->addAction("-", this, SLOT(cwZoomOut()));
    toolBar->addAction("S", this, SLOT(showSettingDialog()));
    toolBar->addAction("gr", this, SLOT(gradient()));
}

void MainWindow::createDockWidgets()
{}

void MainWindow::createStatusBar()
{
    label1 = new QLabel;
    label2 = new QLabel;
    label3 = new QLabel;
    label4 = new QLabel;

    statusBar = new QStatusBar;
    setStatusBar(statusBar);
    statusBar->addWidget(label1);
    statusBar->addWidget(label2);
    statusBar->addWidget(label3);
    statusBar->addWidget(label4);
}

void MainWindow::cwCenterChanged(double centerX, double centerY)
{
    label1->setText(QString("Center: (%1 %2)").arg(centerX, 6, 'f').arg(centerY, 6, 'f'));
}

void MainWindow::cwOffsetChanged(int, int)
{}

void MainWindow::cwScaleChanged(int scaleX, int scaleY)
{
    label3->setText(QString("Scale: (%1 %2)").arg(scaleX).arg(scaleY));
}

void MainWindow::cwZoomChanged(double zoom)
{
    label4->setText(QString("Zoom: %1").arg(zoom, 12, 'f'));
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

    if (sw->radioButton1->isChecked())
    {
        cartesianWidget->setCenter(c.x(), c.y());
    }
    if (sw->radioButton2->isChecked())
    {
        cartesianWidget->setXRange(r.x(), r.y());
    }
    cartesianWidget->update();
}

double f(double *x, int n) { return 4*x[0] - x[1]*x[1] - 12.0; }
double h1(double *x, int n) { return 25.0 - x[0]*x[0] - x[1]*x[1]; }
double g1(double *x, int n) { return 10*x[0] - x[0]*x[0] + 10*x[1] - x[1]*x[1]- 34.0; }
double g2(double *x, int n) { return x[0]; }
double g3(double *x, int n) { return x[1]; }

void MainWindow::gradient()
{
    DoubleVector x;
    x << -1.0 << +1.2;

    SampleGradient gm;
    connect(&gm, SIGNAL(showCoordinares(const DoubleVector &)), this, SLOT(showCoordinares(const DoubleVector &)));
    gm.setEpsilon1(0.00001);
    gm.setEpsilon2(0.00001);
    gm.setEpsilon3(0.00001);
    gm.setR1MinimizeEpsilon(0.01, 0.00001);
    gm.calculate(x);
}

void MainWindow::showCoordinares(const DoubleVector& x)
{

    cartesianWidget->points().append(QPointF(x[0], x[1]));
    cartesianWidget->update();
}
