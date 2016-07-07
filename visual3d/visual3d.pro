#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T16:02:13
#
#-------------------------------------------------

QT += core gui datavisualization

INCLUDEPATH += ../../../include
LIBS += -L$$OUT_PWD/../../../lib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visual3d
TEMPLATE = app

INCLUDEPATH += ../../../num_methods/trunk/optimal/minimum
INCLUDEPATH += ../../../num_methods/trunk/optimal/cminimum
LIBS += -L../../../num_methods/trunk/optimal/bin -lminimum -lcminimum

SOURCES += main.cpp\
        widget.cpp \
    surfacegraph.cpp

HEADERS  += widget.h \
    surfacegraph.h
