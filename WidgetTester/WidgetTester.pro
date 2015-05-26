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
        settingwidget.cpp

HEADERS  += mainwindow.h settingwidget.h

INCLUDEPATH += ../extWidget
LIBS += -L../extWidget/debug -lextWidget
