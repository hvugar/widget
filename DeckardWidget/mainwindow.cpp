#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);

    cartesianWidget = new CartesianWidget;
    setCentralWidget(cartesianWidget);
}

MainWindow::~MainWindow()
{

}
