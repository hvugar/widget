#include "mainwindow.h"
#include <math.h>
#include <string.h>
#include <QDebug>

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
    initFunction();
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
    toolBar->addAction("f1", this, SLOT(func1()));
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

void MainWindow::initFunction()
{
//    FunctionConfig fc1;
//    fc1.f = argmin;
//    fc1.a = -10.0;
//    fc1.b = +10.0;
//    fc1.penColor = 0xff0000;
//    cartesianWidget->functions().append(fc1);

    //    FunctionConfig fc2;
    //    fc2.f = sin;
    //    fc2.a = -2000.5;
    //    fc2.b = +2000.5;
    //    fc2.penColor = 0x0000ff;
    //    cartesianWidget->functions().append(fc2);

    //    FunctionConfig fc3;
    //    fc3.f = f2;
    //    fc3.a = -1.5;
    //    fc3.b = +2.5;
    //    fc3.penColor = 0x0000ff;
    //    cartesianWidget->functions().append(fc3);

    //    QLineF line(0.5, 1.4, 2.3, 2.0);
    //    cartesianWidget->lines().append(line);
    //    cartesianWidget->points().append(QPointF(0.2, 0.2));

    //    gradient();
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

double f_rosenbrock(double *x, int n)
{
    double x1 = x[0];
    double x2 = x[1];
    return ((1-x1)*(1-x1)) + 100*(x2-x1*x1)*(x2-x1*x1);
}

void MainWindow::func1()
{
    double epsilon	= 0.0001;		//dovrun sona catma meyari
    double grad_eps	= 0.005;		//gradient
    double line_eps	= 0.1;			//parcani bolme
    double gold_eps	= 0.0001;		//qizil qayda ucun

    int n = 2;
    double* x  = (double*) malloc( sizeof(double) * n );

    x[0]    = -1.2;
    x[1]    = +1.0;
    conjugate_gradient_method1(f_rosenbrock, x, n, line_eps, gold_eps, grad_eps, epsilon);

    free(x);
}

void MainWindow::printer(RnFunction f, double *x, int n)
{}

struct T {
    static int n;
    static double *x;
    static double *x2;
    static double *s;
    static RnFunction f;
    static double argmin(double alpha)
    {
        for (int i=0; i<n; i++) x2[i] = x[i] + alpha * s[i];
        return f(x2, n);
    }
};

int T::n = 0;
double* T::x = 0;
double* T::x2 = 0;
double* T::s = 0;
RnFunction T::f = 0;

void MainWindow::info(RnFunction f, double *x, int n, int iteration, double *grad, double *s, R1Function min, double alpha, double a, double b)
{
}

void MainWindow::info2(double *x, int n, int iteration, double *grad, double *s, double alpha, double a, double b)
{

}

void info1(RnFunction f, double *x, int n, int iteration, double *grad, double *s, R1Function min, double alpha, double a, double b)
{
}

double MainWindow::func2(double x)
{
    return 0;
}

void MainWindow::conjugate_gradient_method1(RnFunction f, double *x, int n, double line_step, double gold_step, double grad_step, double epsilon)
{
}
