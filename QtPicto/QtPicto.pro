#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T01:39:18
#
#-------------------------------------------------

QT       += gui

TARGET = QtPicto
TEMPLATE = lib

DEFINES += QTPICTO_LIBRARY

SOURCES += qtpicto.cpp \
    awesome.cpp \
    material.cpp

HEADERS += qtpicto.h \
    awesome.h \
    material.h \
    QtPicto

unix {
    target.path = /usr/lib
    headers.files = $$HEADERS
    headers.path  = /usr/include/QtPicto


    INSTALLS += target headers
}

RESOURCES += \
    qtpicto.qrc



include(../patternscpp/patterns.pri)
