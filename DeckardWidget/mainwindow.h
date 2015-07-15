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
#include <QTimer>

#include "cartesianwidget2d.h"
#include "cartesianwidget2d_1.h"
#include "settingwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static MainWindow* mw;
    void initFunction();

    Cartesian2DWidget* cartesianWidget;
private:
    SettingWidget* settingWidget;

    QToolBar* toolBar;
    QToolButton* toolButton1;
    QToolButton* toolButton2;
    QToolButton* toolButton3;

    QStatusBar* statusBar;
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QLabel* label4;

    void createMenus();
    void createToolBars();
    void createDockWidgets();
    void createStatusBar();

    static void info(RnFunction f, double *x, int n, int iteration, double *grad, double *s, R1Function min, double alpha, double a, double b);

    void info2(double *x, int n, int iteration, double *grad, double *s, double alpha, double a, double b);
    void conjugate_gradient_method1(RnFunction f, double *x, int n, double line_step, double gold_step, double grad_step, double epsilon);
    void printer(RnFunction f, double *x, int n);

    double func2(double);

public slots:
    void cwCenterChanged(double, double);
    void cwOffsetChanged(int, int);
    void cwScaleChanged(int, int);
    void cwZoomChanged(double);
    void cwBoundsChanged(double,double,double,double);
    void cwZoomIn();
    void cwZoomOut();

    void showSettingDialog();
    void func1();
};

#endif // MAINWINDOW_H
