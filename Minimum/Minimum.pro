#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T15:48:50
#
#-------------------------------------------------

QT       -= core gui

TARGET = Minimum
TEMPLATE = lib

DEFINES += MINIMUM_LIBRARY

SOURCES += minimum.cpp

HEADERS += minimum.h\
        minimum_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
