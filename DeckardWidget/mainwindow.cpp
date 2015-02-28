#include "mainwindow.h"
#include <math.h>
#include <string.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);

    cartesianWidget = new CartesianWidget;
    setCentralWidget(cartesianWidget);
//    setWindowState(Qt::WindowMaximized);

    FunctionConfig fc1;
    fc1.f = sin;
    fc1.a = -2.5;
    fc1.b = +2.5;
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
    fc3.a = -10.5;
    fc3.b = +10.5;
    fc3.penColor = 0x0000ff;
    cartesianWidget->addFunctionConfig(fc3);
}

MainWindow::~MainWindow()
{

}
