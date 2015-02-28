#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cartesianwidget.h"
#include "cartesianwidget1.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    CartesianWidget2* cartesianWidget;
};

#endif // MAINWINDOW_H
