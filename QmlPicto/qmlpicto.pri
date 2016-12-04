INCLUDEPATH += $$PWD

CONFIG += c++11
QT += qml quick

android {
    QT += androidextras svg xml
}


SOURCES += $$PWD/qmlpicto_plugin.cpp \
    $$PWD/keytable.cpp \
    $$PWD/pictoimageprovider.cpp

HEADERS += $$PWD/qmlpicto_plugin.h \
    $$PWD/keytable.h \
    $$PWD/pictoimageprovider.h \
    $$PWD/qmlpicto.h


RESOURCES += $$PWD/qmlpicto.qrc

include(../QtPicto/QtPicto.pri)
