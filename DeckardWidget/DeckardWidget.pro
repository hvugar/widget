#-------------------------------------------------
#
# Project created by QtCreator 2014-12-30T10:58:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeckardWidget
TEMPLATE = app

#INCLUDEPATH = ../../../num_methods/trunk/minimum
#LIBS += -L../../../num_methods/trunk/minimum -lminimum.dll

SOURCES += main.cpp\
    mainwindow.cpp \
    functionconfig.cpp \
    cartesianwidget.cpp \
    settingwidget.cpp \
    cartesianwidget2d_1.cpp \
    cartesianwidget2d.cpp

HEADERS  += mainwindow.h \
    functionconfig.h \
    cartesianwidget.h \
    settingwidget.h \
    cartesianwidget2d_1.h \
    cartesianwidget2d.h

RESOURCES += \
    resource.qrc
