#include "qmlpicto.h"
#include "qmlpictoview.h"
inline void initQmlResources() { Q_INIT_RESOURCE(qmlpicto); }


namespace picto {

	void init() {
		static bool first = true;

		if (first) {
			initQmlResources();
			qmlRegisterType<QmlPictoView>("QmlPicto", 0, 1, "PictoImage");
		    qmlRegisterSingletonType<PictoResolver>(
		        "QmlPicto", 0, 1, "Picto", &PictoResolver::qmlResolverRegister);
		    first = false;
		}
 	}

}
