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

    QSize s(requestedSize.width() > 0 ? requestedSize.width() : wh, requestedSize.height() > 0 ? requestedSize.height() : wh);


    qDebug() << id;


    return QImage();

}

QPixmap PictoImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {

    static int wh = 100;

    if (!size) {
        *size = QSize(wh,wh);
    }



    QSize s(requestedSize.width() > 0 ? requestedSize.width() : size->width(), requestedSize.height() > 0 ? requestedSize.height() : size->height());

    QString name = id;
    QColor color;

    if (id.contains("?")) {
        auto index = id.indexOf("?");

        QUrlQuery qs(id.right(id.length() - 1 - index));
        name = id.left(index);
        auto items = qs.queryItems();

        for (auto pair: items) {
            if (pair.first == "color") {
                color = QColor(pair.second);
            } else if (pair.first == "width") {
                s.setWidth(pair.second.toInt());
                size->setWidth(s.width());
            } else if (pair.first == "height") {
                s.setHeight(pair.second.toInt());
                size->setHeight(s.height());
            }
        }

    }


    return m_gen->pixmap(name, s, color);


}
