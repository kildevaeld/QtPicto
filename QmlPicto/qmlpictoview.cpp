#include "qmlpictoview.h"
#include <QColor>
#include <QtPicto/QtPicto>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QPixmap>
#include <QPainter>
using picto::awesome;
using picto::material;

QmlPictoView::QmlPictoView(QQuickItem *parent): QQuickPaintedItem(parent), m_color(QColor("black")) {

}


void QmlPictoView::paint(QPainter *painter) {

    if (m_name.isEmpty()) {
        return;
    }

    QString name = m_name;
    if (m_name.startsWith("image:/")) {
        name = m_name.mid(8);
    }

    QVector<QStringRef> split = name.splitRef("/");
    qDebug() << split;
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

    painter->drawPixmap(0,0,w,h, img);

}
