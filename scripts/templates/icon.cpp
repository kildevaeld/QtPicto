
#include "{{enum}}.h"
#include <QDebug>
#include <QFile>
#include <QFontDatabase>

namespace picto {

static const QHash<QString, int> {{provider}}Hash = {
    {{#each icons}} 
	{"{{name}}", {{../enum}}::{{name}} }, 
	{{/each}}
};

bool {{enum}}::Provider::initialize() {

  static int fontId = -1;

  if (fontId < 0) {

    QFile res(":/fonts/{{font}}");

    if (!res.open(QIODevice::ReadOnly)) {
      qDebug() << "{{font}} font could not be read";
      return false;
    }

    QByteArray fontData(res.readAll());
    res.close();

    fontId = QFontDatabase::addApplicationFontFromData(fontData);
  }

  QStringList loadedFontFamilies =
      QFontDatabase::applicationFontFamilies(fontId);

  if (!loadedFontFamilies.empty()) {
    m_fontName = loadedFontFamilies.at(0);
  } else {
    qDebug() << "Font awesome font is empty?!" << "{{font}}";
    fontId = -1; // restore the font-awesome id
    return false;
  }


  return true;
}

QFont {{enum}}::Provider::font(int size) {
	QFont font(m_fontName);
	font.setPixelSize(size);
	return font;
}

QString {{enum}}::Provider::name(int code) {
	return {{provider}}Hash.key(code);
}

int {{enum}}::Provider::code(const QString &name) {
	return {{provider}}Hash.value(name);
}

QString {{enum}}::Provider::providerName() {
	return QString("{{enum}}");
}

}