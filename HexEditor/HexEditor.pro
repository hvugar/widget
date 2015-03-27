#-------------------------------------------------
#
# Project created by QtCreator 2013-05-13T09:25:29
#
#-------------------------------------------------

QT          += core gui sql network
TARGET      = HexEditor
TEMPLATE    = app

#CONFIG  += console
#CONFIG  += release
#CONFIG  += debug
CONFIG  += release_and_debug
#CONFIG  -= app_bundle

unix{
        linux-g++ | linux-g++-64 {
                CONFIG(debug, debug|release) {
                    MOC_DIR = tmp/unix/gcc/moc/debug
                    OBJECTS_DIR = tmp/unix/gcc/obj/debug
                    DESTDIR = bin/unix/gcc/debug
                } else {
                    MOC_DIR = tmp/unix/gcc/moc/release
                    OBJECTS_DIR = tmp/unix/gcc/obj/release
                    DESTDIR = bin/unix/gcc/release
                }
        }
        DEFINES += __UNIX__
}

win32{
        win32-g++ {
                CONFIG(debug, debug|release) {
                    MOC_DIR = tmp/win32/gcc/moc/debug
                    OBJECTS_DIR = tmp/win32/gcc/obj/debug
                    DESTDIR = bin/win32/gcc/debug
                } else {
                    MOC_DIR = tmp/win32/gcc/moc/release
                    OBJECTS_DIR = tmp/win32/gcc/obj/release
                    DESTDIR = bin/win32/gcc/release
                }
        }
        win32-msvc2008 {
                CONFIG(debug, debug|release) {
                    MOC_DIR = tmp/win32/msvc2008/moc/debug
                    OBJECTS_DIR = tmp/win32/msvc2008/obj/debug
                    DESTDIR = bin/win32/msvc2008/debug
                } else {
                    MOC_DIR = tmp/win32/msvc2008/moc/release
                    OBJECTS_DIR = tmp/win32/msvc2008/obj/release
                    DESTDIR = bin/win32/msvc2008/release
                }
        }
        DEFINES += __WIN32__
}


SOURCES += main.cpp \
           qhexscrollarea.cpp \
           dockmainwindow.cpp

HEADERS  += \
            qhexscrollarea.h \
            dockmainwindow.h

RESOURCES += resource.qrc
