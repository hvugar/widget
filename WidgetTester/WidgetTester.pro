#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T11:50:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WidgetTester
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    settingwidget.cpp \
    samplegradient.cpp

HEADERS  += mainwindow.h settingwidget.h samplegradient.h

INCLUDEPATH += ../extWidget
LIBS += -L../extWidget/release -lextWidget

INCLUDEPATH += ../../../num_methods/trunk/optimal/minimum
LIBS += -L../../../num_methods/trunk/optimal/bin -lminimum
