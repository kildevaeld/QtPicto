#include "qmlpictoview.h"
#include <QColor>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QVector>
#include <QtPicto/QtPicto>
using picto::awesome;
using picto::material;

PictoResolver::PictoResolver(QObject *parent) : QObject(parent) {}

QString PictoResolver::icon(const QString &name, const QColor &color,
                            const int size) {

  QStringList split = name.split("/");
  if (split.length() != 2) {
    return "";
  }

  split.insert(1, "icon");
  QString w = QString::number(size);
  return "image://picto-" + split.join("/") + "?color=" + color.name() +
         "&width=" + w + "&height=" + w;
}

QString PictoResolver::image(const QString &name, const QColor &color) {
  return "image://picto-" + name + "?color=" + color.name();
}

QmlPictoView::QmlPictoView(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_color(QColor("black")) {}

void QmlPictoView::paint(QPainter *painter) {

  if (m_name.isEmpty()) {
    return;
  }

  QString name = m_name;
  if (m_name.startsWith("image:/")) {
    name = m_name.mid(8);
  }

  QVector<QStringRef> split = name.splitRef("/");

  if (split.length() < 2) {
    return;
  }

  auto gen = picto::Picto::instance().provider(split[0].toString());

  if (gen == nullptr) {
    return;
  }

  qreal w = boundingRect().width();
  qreal h = boundingRect().height();

  QPixmap img = gen->pixmap(split[1].toString(), QSize(w, h), m_color);

  if (img.isNull()) {
    return;
  }

  painter->drawPixmap(0, 0, w, h, img);
}
