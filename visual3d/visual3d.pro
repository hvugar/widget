#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T16:02:13
#
#-------------------------------------------------

QT += core gui widgets datavisualization

TARGET = visual3d
TEMPLATE = app

win32-g++ {
    CONFIG(release, debug|release) {
        OBJECTS_DIR = release/.obj/win32-gcc
        MOC_DIR     = release/.moc/win32-gcc

        INCLUDEPATH += ../../../num_methods/trunk/optimal/minimum
        LIBS += -L../../../num_methods/trunk/optimal/bin -lminimum
    }
    CONFIG(debug, debug|release) {
        OBJECTS_DIR = debug/.obj/win32-gcc
        MOC_DIR     = debug/.moc/win32-gcc
    }
}

win32-msvc* {
    CONFIG(release, debug|release) {
        OBJECTS_DIR = release/.obj/win32-msvc
        MOC_DIR     = release/.moc/win32-msvc

        INCLUDEPATH += ../../../num_methods/trunk/optimal/minimum
        LIBS += ../../../num_methods/trunk/optimal/bin/minimum.lib
    }
    CONFIG(debug, debug|release) {
        OBJECTS_DIR = debug/.obj/win32-msvc
        MOC_DIR     = debug/.moc/win32-msvc
    }
}


SOURCES += main.cpp\
        widget.cpp \
#    surfacegraph.cpp \
#    rosenbrocksurface.cpp \
#    bealesurface.cpp \
#    boothsurface.cpp \
    matrixsurface.cpp

HEADERS  += widget.h \
#    surfacegraph.h \
#    rosenbrocksurface.h \
#    bealesurface.h \
#    boothsurface.h \
    matrixsurface.h
