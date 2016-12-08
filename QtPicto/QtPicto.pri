INCLUDEPATH += $$PWD $$PWD/patternscpp

DEFINES += QTPICTO_LIBRARY

SOURCES += $$PWD/qtpicto.cpp \
    $$PWD/awesome.cpp \
    $$PWD/material.cpp

HEADERS += $$PWD/qtpicto.h \
    $$PWD/awesome.h \
    $$PWD/material.h \
    $$PWD/QtPicto \
    $$PWD/patternscpp/singleton.h

RESOURCES += \
    $$PWD/qtpicto.qrc
