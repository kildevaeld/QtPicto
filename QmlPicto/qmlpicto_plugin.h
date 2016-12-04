#pragma once

#include <QQmlExtensionPlugin>




class QmlPictoPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.softshag.QmlPicto")

public:
    void registerTypes(const char *uri);

    // QQmlExtensionInterface interface
public:
    virtual void initializeEngine(QQmlEngine *engine, const char *uri);
};
