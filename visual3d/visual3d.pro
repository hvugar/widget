#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T16:02:13
#
#-------------------------------------------------

QT += core gui widgets datavisualization

TARGET = visual3d
TEMPLATE = app

INCLUDEPATH += ../../../num_methods/trunk/optimal/minimum
LIBS += -L../../../num_methods/trunk/optimal/bin -lminimum

SOURCES += main.cpp\
        widget.cpp \
#    surfacegraph.cpp \
#    rosenbrocksurface.cpp bealesurface.cpp \
#    boothsurface.cpp \
    matrixsurface.cpp

HEADERS  += widget.h \
#    surfacegraph.h \
#    rosenbrocksurface.h bealesurface.h \
#    boothsurface.h \
    matrixsurface.h
