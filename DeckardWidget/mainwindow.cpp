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
    //    fc1.f = f5;
    //    fc1.a = -10.5;
    //    fc1.b = +10.5;
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
<<<<<<< .mine
//    int i = 0;
//    int k = 0;
=======
>>>>>>> .r41

<<<<<<< .mine
//    int iteration = 0;
//    int count = 0;
=======
}
>>>>>>> .r41

<<<<<<< .mine
//    // Direction
//    double *s  = (double*) malloc(sizeof(double) * n);
//    // Saves last point coordinates
//    double *x1 = (double*) malloc(sizeof(double) * n);
//    // Used for one dimention minimization for stopring next point coordinates
//    double *x2 = (double*) malloc(sizeof(double) * n);
=======
Cartesian2DWidget cw1;
void info1(RnFunction f, double *x, int n, int iteration, double *grad, double *s, R1Function min, double alpha, double a, double b)
{
    Cartesian2DWidget *cw = new Cartesian2DWidget;
    cw->resize(800, 600);
    cw->reset();
//    Cartesian2DWidget *cw = qobject_cast<Cartesian2DWidget*>(MainWindow::mw->cartesianWidget);
    cw->functions().clear();
    FunctionConfig fc;
    fc.f = min;
    fc.a = a;
    fc.b = b;
    fc.penColor = 0x00ffff;
    cw->functions().append(fc);
    cw->setXRange(alpha-0.1, alpha+0.1);
    cw->setCenterY(min(alpha));
    qDebug() << min(alpha);
    cw->update();
    QPixmap pixmap = QPixmap::grabWidget(cw, 0, 0, cw->width(), cw->height());
    pixmap.save(QString("D:\\image%1.png").arg(iteration), "png");
    cw->functions().clear();
    delete cw;
>>>>>>> .r41

<<<<<<< .mine
//    // Gradient of x(k) point
//    double* gr1 = (double*) malloc(sizeof(double) * n);
//    // Gradinet of x(k+1) point
//    double* gr2 = (double*) malloc(sizeof(double) * n);
=======
    cw1.resize(800,600);
    cw1.points().append(QPointF(x[0], x[1]));
    QPixmap pixmap1 = QPixmap::grabWidget(&cw1, 0, 0, cw1.width(), cw1.height());
    pixmap1.save(QString("D:\\image_%1.png").arg(iteration), "png");
}
>>>>>>> .r41

<<<<<<< .mine
//    double gr1_mod = 0.0;
//    double gr2_mod = 0.0;
//    do
//    {
//        // First iteration
//        if (k == 0)
//        {
//            // Gradient of objectiv function in current point
//            gradient(f, x, n, grad_step, gr1);
=======
void MainWindow::conjugate_gradient_method1(RnFunction f, double *x, int n, double line_step, double gold_step, double grad_step, double epsilon)
{
    conjugate_gradient_method(f, x, n, line_step, gold_step, grad_step, epsilon, NULL, info1);
    //    int i = 0;
    //    int k = 0;
>>>>>>> .r41

<<<<<<< .mine
//            // First direction is antigradient
//            for (i=0; i<n; i++) s[i] = -gr1[i];
=======
    //    int iteration = 0;
    //    int count = 0;
>>>>>>> .r41

<<<<<<< .mine
//            // Module of gradient
//            gr1_mod = 0.0;
//            for (i=0; i<n; i++) gr1_mod += gr1[i]*gr1[i];
//        }
//        else
//        {
//            /// Gradient of objectiv function in next point
//            gradient(f, x, n, grad_step, gr2);
=======
    //    // Direction
    //    double *s  = (double*) malloc(sizeof(double) * n);
    //    // Saves last point coordinates
    //    double *x1 = (double*) malloc(sizeof(double) * n);
    //    // Used for one dimention minimization for stopring next point coordinates
    //    double *x2 = (double*) malloc(sizeof(double) * n);
>>>>>>> .r41

<<<<<<< .mine
//            // Module of next gradient
//            gr2_mod = 0.0;
//            for (i=0; i<n; i++) gr2_mod = gr2_mod + gr2[i]*gr2[i];
=======
    //    // Gradient of x(k) point
    //    double* gr1 = (double*) malloc(sizeof(double) * n);
    //    // Gradinet of x(k+1) point
    //    double* gr2 = (double*) malloc(sizeof(double) * n);
>>>>>>> .r41

<<<<<<< .mine
//            double w = gr2_mod / gr1_mod;
//            gr1_mod = gr2_mod;
=======
    //    double gr1_mod = 0.0;
    //    double gr2_mod = 0.0;
    //    do
    //    {
    //        // First iteration
    //        if (k == 0)
    //        {
    //            // Gradient of objectiv function in current point
    //            gradient(f, x, n, grad_step, gr1);
>>>>>>> .r41

<<<<<<< .mine
//            // Direction in next (k+1) iteration
//            for (i=0; i<n; i++) s[i] = -gr2[i] + s[i] * w;
//        }
=======
    //            // First direction is antigradient
    //            for (i=0; i<n; i++) s[i] = -gr1[i];
>>>>>>> .r41

<<<<<<< .mine
//        iteration++;
=======
    //            // Module of gradient
    //            gr1_mod = 0.0;
    //            for (i=0; i<n; i++) gr1_mod += gr1[i]*gr1[i];
    //        }
    //        else
    //        {
    //            /// Gradient of objectiv function in next point
    //            gradient(f, x, n, grad_step, gr2);
>>>>>>> .r41

<<<<<<< .mine
//        // Minimization in one dimensional direction
//        T::n = n;
//        T::x = x;
//        T::f = f;
//        T::s = s;
//        T::x2 = x2;
//        R1Function g = T::argmin;
=======
    //            // Module of next gradient
    //            gr2_mod = 0.0;
    //            for (i=0; i<n; i++) gr2_mod = gr2_mod + gr2[i]*gr2[i];
>>>>>>> .r41

<<<<<<< .mine
//        double a,b;
//        double alpha0 = 0.0;
//        straight_line_search_metod(g, alpha0, line_step, &a, &b);
//        double alpha = golden_section_search_min(g, a, b, gold_step);
=======
    //            double w = gr2_mod / gr1_mod;
    //            gr1_mod = gr2_mod;
>>>>>>> .r41

<<<<<<< .mine
//        //
//        if (g(alpha)>g(alpha0)) alpha = alpha0;
=======
    //            // Direction in next (k+1) iteration
    //            for (i=0; i<n; i++) s[i] = -gr2[i] + s[i] * w;
    //        }
>>>>>>> .r41

<<<<<<< .mine
//        FunctionConfig fc;
//        fc.a = a;
//        fc.b = b;
//        fc.f = g;
//        cartesianWidget->functions().clear();
//        cartesianWidget->functions().append(fc);
//        cartesianWidget->setXRange(alpha-line_step, alpha+line_step);
//        cartesianWidget->setCenterY(g(alpha));
//        cartesianWidget->update();
//        qDebug() << iteration << alpha << g(alpha);
=======
    //        iteration++;
>>>>>>> .r41

<<<<<<< .mine
//        QPixmap pixmap = QPixmap::grabWidget(cartesianWidget, 0, 0, cartesianWidget->width(), cartesianWidget->height());
//        pixmap.save(QString("D:\\image%1.png").arg(iteration), "png");
//        cartesianWidget->functions().clear();
=======
    //        // Minimization in one dimensional direction
    //        T::n = n;
    //        T::x = x;
    //        T::f = f;
    //        T::s = s;
    //        T::x2 = x2;
    //        R1Function g = T::argmin;
>>>>>>> .r41

<<<<<<< .mine
//        // Saving last point coordinates
//        memcpy(x1, x, sizeof(double) * n);
=======
    //        double a,b;
    //        double alpha0 = 0.0;
    //        straight_line_search_metod(g, alpha0, line_step, &a, &b);
    //        double alpha = golden_section_search_min(g, a, b, gold_step);
>>>>>>> .r41

<<<<<<< .mine
//        cartesianWidget->points().append(QPointF(x[0], x[1]));
=======
    //        //
    //        if (g(alpha)>g(alpha0)) alpha = alpha0;
>>>>>>> .r41

<<<<<<< .mine
//        // Calculating next point coordinates
//        for (i=0; i<n; i++)
//        {
//            x[i] = x[i] + alpha * s[i];
//        }
=======
    //        FunctionConfig fc;
    //        fc.a = a;
    //        fc.b = b;
    //        fc.f = g;
    //        cartesianWidget->functions().clear();
    //        cartesianWidget->functions().append(fc);
    //        cartesianWidget->setXRange(alpha-line_step, alpha+line_step);
    //        cartesianWidget->setCenterY(g(alpha));
    //        cartesianWidget->update();
    //        qDebug() << iteration << alpha << g(alpha);
>>>>>>> .r41

<<<<<<< .mine
//        cartesianWidget->lines().append(QLineF(x[0], x[1], x1[0], x1[1]));
=======
    //        QPixmap pixmap = QPixmap::grabWidget(cartesianWidget, 0, 0, cartesianWidget->width(), cartesianWidget->height());
    //        pixmap.save(QString("D:\\image%1.png").arg(iteration), "png");
    //        cartesianWidget->functions().clear();
>>>>>>> .r41

<<<<<<< .mine
//        //mod_s = 0.0;
//        //for (i=0; i<n; i++) mod_s = mod_s + s[i]*s[i];
//        //mod_s = vertor_norm(s, n);
//        //dist = distance(x1, x, n);
=======
    //        // Saving last point coordinates
    //        memcpy(x1, x, sizeof(double) * n);
>>>>>>> .r41

<<<<<<< .mine
//        if ( k == n ) { k = 0; } else { k++; }
=======
    //        cartesianWidget->points().append(QPointF(x[0], x[1]));
>>>>>>> .r41

<<<<<<< .mine
//    } while ( vertor_norm(s, n) > epsilon && distance(x1, x, n) > epsilon );
=======
    //        // Calculating next point coordinates
    //        for (i=0; i<n; i++)
    //        {
    //            x[i] = x[i] + alpha * s[i];
    //        }
>>>>>>> .r41

<<<<<<< .mine
//    free(gr1);
//    free(gr2);
//    free(s);
//    free(x1);
//    free(x2);
=======
    //        cartesianWidget->lines().append(QLineF(x[0], x[1], x1[0], x1[1]));
>>>>>>> .r41

<<<<<<< .mine
//    gr1 = gr2 = s = x1 = x2 = NULL;
=======
    //        //mod_s = 0.0;
    //        //for (i=0; i<n; i++) mod_s = mod_s + s[i]*s[i];
    //        //mod_s = vertor_norm(s, n);
    //        //dist = distance(x1, x, n);

    //        if ( k == n ) { k = 0; } else { k++; }

    //    } while ( vertor_norm(s, n) > epsilon && distance(x1, x, n) > epsilon );

    //    free(gr1);
    //    free(gr2);
    //    free(s);
    //    free(x1);
    //    free(x2);

    //    gr1 = gr2 = s = x1 = x2 = NULL;
>>>>>>> .r41
}
