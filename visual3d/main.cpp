//#include "surfacegraph.h"

#include <QApplication>
#include "widget.h"
#include <QtWidgets/QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q3DSurface *graph = new Q3DSurface();

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return -1;
    }

    Widget w(graph);
    w.show();

//    SurfaceGraph *modifier = new SurfaceGraph(graph);

    return a.exec();
}
