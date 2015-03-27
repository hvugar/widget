#include <QtGui/QApplication>
#include "dockmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(resource);

    DockMainWindow w;
    w.show();
    
    return a.exec();
}
