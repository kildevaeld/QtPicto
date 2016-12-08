#include "pictoimageprovider.h"
#include <QtPicto/QtPicto>
#include <QDebug>
#include <QStringRef>
#include <QUrlQuery>

PictoImageProvider::PictoImageProvider(picto::PictoGenerator *generator, QQmlImageProviderBase::ImageType imageType, QQmlImageProviderBase::Flags flags): QQuickImageProvider(imageType, flags), m_gen(generator) {


}


QImage PictoImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {

    static int wh = 100;

    if (!size) {
        *size = QSize(wh,wh);
    }

    QSize s(requestedSize.width() > 0 ? requestedSize.width() : size->width(), requestedSize.height() > 0 ? requestedSize.height() : size->height());


    qDebug() << id;


    return QImage();

}

QPixmap PictoImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {

    static int wh = 100;

    QString name = id;

    if (id.startsWith("icons")) {
        wh = 24;
        name = id.mid(6);
    }

    qDebug() << name;

    if (size) {
        *size = QSize(wh,wh);
    }

    QSize s(requestedSize.width() > 0 ? requestedSize.width() : size->width(), requestedSize.height() > 0 ? requestedSize.height() : size->height());


    QColor color;

    if (id.contains("?")) {
        auto index = id.indexOf("?");

        QUrlQuery qs(id.right(id.length() - 1 - index));
        name = id.left(index);
        auto items = qs.queryItems();

        this->get_options(items, &color, &s);

        size->setHeight(s.height());
        size->setWidth(s.width());
        /*for (auto pair: items) {
            if (pair.first == "color") {
                color = QColor(pair.second);
            } else if (pair.first == "width") {
                s.setWidth(pair.second.toInt());
                size->setWidth(s.width());
            } else if (pair.first == "height") {
                s.setHeight(pair.second.toInt());
                size->setHeight(s.height());
            }
        }*/

    }


    return m_gen->pixmap(name, s, color);


}

void PictoImageProvider::get_options(QList<QPair<QString, QString> > &list, QColor *color, QSize *size) {
    for (auto pair: list) {
        if (pair.first == "color") {
            *color = QColor(pair.second);
        } else if (pair.first == "width") {
            bool ok;
            auto i = pair.second.toInt(&ok);
            if (ok && i > 0) {
                size->setWidth(i);
            } else {
                auto d = pair.second.toDouble(&ok);
                if (ok && d > 0) {
                    size->setWidth((int)d);
                }
            }

        } else if (pair.first == "height") {
            bool ok;
            auto i = pair.second.toInt(&ok);
            if (ok && i > 0) {
                size->setHeight(i);
            } else {
                auto d = pair.second.toDouble(&ok);
                if (ok && d > 0) {
                    size->setHeight((int)d);
                }
            }
        }
    }
}
