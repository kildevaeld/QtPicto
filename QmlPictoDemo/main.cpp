#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QmlPicto/QmlPicto>

int main(int argc, char *argv[])
{

	picto::init();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //engine.addImportPath("../");
    engine.addImportPath("qrc:/");
    //engine.addImageProvider("awesome", picto::imageProvider<picto::awesome>());

    picto::imageProvider<picto::awesome>(&engine);
    picto::imageProvider<picto::material>(&engine);

   engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
