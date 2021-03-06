//#include "surfacegraph.h"

#include <QApplication>
#include "widget.h"
#include <QtWidgets/QMessageBox>

#include "rosenbrocksurface.h"
#include "bealesurface.h"
#include "boothsurface.h"
#include "matrixsurface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    Q3DSurface *graph = new Q3DSurface();

    //    if (!graph->hasContext()) {
    //        QMessageBox msgBox;
    //        msgBox.setText("Couldn't initialize the OpenGL context.");
    //        msgBox.exec();
    //        return -1;
    //    }

    //    Widget w(graph);
    //    w.show();



    //    SurfaceGraph *modifier = new SurfaceGraph(graph);

    Q3DSurface *surface = new MatrixSurface();

    if (!surface->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return -1;
    }

    QWidget *w = QWidget::createWindowContainer(surface);
    w->setWindowState(Qt::WindowMaximized);
    w->show();


    return a.exec();
}
