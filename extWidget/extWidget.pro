#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T11:43:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = extWidget
TEMPLATE = lib

DEFINES += EXT_WIDGET_LIBRARY

SOURCES += cartesianwidget.cpp functionconfig.cpp cartesianwidget2d.cpp

HEADERS += extwidget_global.h cartesianwidget.h functionconfig.h cartesianwidget2d.h

RESOURCES += resource.qrc
