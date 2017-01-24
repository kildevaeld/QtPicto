#include "qmlpicto_plugin.h"
#include "qmlpicto.h"
#include "qmlpictoview.h"
#include <qqml.h>

class PictoRegisterHelper {

public:
  PictoRegisterHelper(const char *uri) {

    qmlRegisterType<QmlPictoView>(uri, 0, 1, "PictoImage");
    qmlRegisterSingletonType<PictoResolver>(
        uri, 0, 1, "Picto", &PictoResolver::qmlResolverRegister);
  }
};

void QmlPictoPlugin::registerTypes(const char *uri) {
  Q_ASSERT(uri == QStringLiteral("QmlPicto"));

  PictoRegisterHelper helper(uri);
}

void QmlPictoPlugin::initializeEngine(QQmlEngine *engine, const char *uri) {
  Q_UNUSED(uri);

  picto::imageProvider<picto::awesome>(engine);
  picto::imageProvider<picto::material>(engine);
}

// When using QPM, the C++ plugin is not used and the QML types must be
// registered manually
#ifdef QPM_INIT
static PictoRegisterHelper registerHelper("QmlPicto");
#endif
