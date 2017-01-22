INCLUDEPATH += $$PWD

CONFIG += c++11
QT += qml quick

android {
    QT += androidextras svg xml
}


SOURCES += $$PWD/qmlpicto_plugin.cpp \
    $$PWD/pictoimageprovider.cpp \
    $$PWD/qmlpictoview.cpp

HEADERS += $$PWD/qmlpicto_plugin.h \
    $$PWD/pictoimageprovider.h \
    $$PWD/qmlpicto.h \
    $$PWD/qmlpictoview.h


RESOURCES += $$PWD/qmlpicto.qrc

include(../QtPicto/QtPicto.pri)
