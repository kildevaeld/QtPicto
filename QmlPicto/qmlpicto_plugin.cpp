#include "qmlpicto_plugin.h"
#include "qmlpicto.h"
#include "keytable.h"
#include "qmlpictoview.h"
#include <qqml.h>

class PictoRegisterHelper {

public:
    PictoRegisterHelper(const char *uri) {
        qmlRegisterType<QFKeyTable>(uri, 0, 1, "KeyTable");
        qmlRegisterType<QmlPictoView>(uri, 0, 1, "Picto");
        //qmlRegisterSingletonType<Device>(uri, 0, 1, "Device", Device::qmlSingleton);
        //qmlRegisterUncreatableType<Units>(uri, 0, 3, "Units", QStringLiteral("Units can only be used via the attached property."));
    }
};

void QmlPictoPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QStringLiteral("QmlPicto"));

    PictoRegisterHelper helper(uri);
}






void QmlPictoPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);

    picto::imageProvider<picto::awesome>(engine);
    picto::imageProvider<picto::material>(engine);

}




// When using QPM, the C++ plugin is not used and the QML types must be registered manually
#ifdef QPM_INIT
static PictoRegisterHelper registerHelper("QmlPicto");
#endif
