#include "mainwindow.h"
#include <QApplication>

#include <QDockWidget>
#include <QDesktopServices>

#include <QMdiArea>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QMdiSubWindow qd;
    qd.show();

    return a.exec();
}
