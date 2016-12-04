#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qmlpicto.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //engine.addImportPath("qrc:/");
    QPM_INIT(engine)
    //engine.addImageProvider("awesome", picto::imageProvider<picto::awesome>());

    picto::imageProvider<picto::awesome>(&engine);
    picto::imageProvider<picto::material>(&engine);

   engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
