TEMPLATE = lib
TARGET = qmlpicto
QT += qml quick
CONFIG += qt plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.softshag.qmlpicto

INCLUDEPATH += ../

# Input
SOURCES += \
    qmlpicto_plugin.cpp \
    keytable.cpp \
    pictoimageprovider.cpp \
    #../QtPicto/qtpicto.cpp \
    #../QtPicto/awesome.cpp \
    #../QtPicto/material.cpp \
    qmlpictoview.cpp



HEADERS += \
    qmlpicto_plugin.h \
    qmlpicto.h \
    keytable.h \
    pictoimageprovider.h \
    \
    #../QtPicto/qtpicto.h \
    #../QtPicto/awesome.h \
    #../QtPicto/material.h \
    #../QtPicto/QtPicto \
    qmlpictoview.h

DISTFILES = qmldir \
    qmlpicto.pri


include(../QtPicto/QtPicto.pri)


#!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
#    copy_qmldir.target = $$OUT_PWD/qmldir
#    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
#    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
#    QMAKE_EXTRA_TARGETS += copy_qmldir
#    PRE_TARGETDEPS += $$copy_qmldir.target
#}

#qmldir.files = qmldir

target.path = $$[QT_INSTALL_QML]/QmlPicto

picto.files +=  ./*.qml ./qmlpicto.qmltypes
picto.path = $$[QT_INSTALL_QML]/QmlPicto

qmldir.target = $$OUT_PWD/out/qmldir
qmldir.commands = mkdir -p $$OUT_PWD/out;
qmldir.commands += sed \"s/$$LITERAL_HASH plugin qmlpicto/plugin qmlpicto/\" $$PWD/qmldir > $$qmldir.target
qmldir.depends = $$PWD/qmldir
qmldir.path = $$[QT_INSTALL_QML]/QmlPicto
qmldir.files = $$qmldir.target
qmldir.CONFIG += no_check_exist

unix {
    #installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    #qmldir.path = $$installPath
    #target.path = $$installPath
    #INSTALLS += target qmldir
}

INSTALLS += target qmldir picto

RESOURCES += \
    qmlpicto.qrc

OTHER_FILES += qmlpicto.pri
