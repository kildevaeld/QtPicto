#include "pictoimageprovider.h"
#include <QtPicto/QtPicto>
#include <QDebug>


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

    QSize s(requestedSize.width() > 0 ? requestedSize.width() : wh, requestedSize.height() > 0 ? requestedSize.height() : wh);


    return m_gen->pixmap(id, s);


}
