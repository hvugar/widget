#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTextLine>
#include <QLineEdit>
#include <QLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QStatusBar>

#include "cartesianwidget0.h"
#include "cartesianwidget1.h"
#include "cartesianwidget2.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initFunction();

private:
    CartesianWidget* cartesianWidget;

    QToolBar* toolBar;
    QToolButton* toolButton1;
    QToolButton* toolButton2;
    QToolButton* toolButton3;

    QStatusBar* statusBar;
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QLabel* label4;


public slots:
    void cwCenterChanged(double, double);
    void cwOffsetChanged(int, int);
    void cwScaleChanged(int, int);
    void cwZoomChanged(double);
};

#endif // MAINWINDOW_H
